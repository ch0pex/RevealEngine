/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "scene_graph.hpp"
#include "../fonts/IconsFontAwesome5.h"


using namespace std::literals::string_literals;

namespace reveal3d::ui {

SceneGraph::SceneGraph() : selected_(UINT_MAX) {

}

void SceneGraph::Draw() {
    ImGui::Begin("Scene Graph");
    if (ImGui::Button("Add Entity")) {
        if (id::isValid(selected_)){
            selected_ = core::scene.NewChildEntity(selected_).Id();
        } else {
            selected_ = core::scene.NewEntity().Id();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Entity")) {
        core::scene.RemoveEntity(selected_);
        selected_ = id::invalid;
    }

    if (core::scene.NumEntities()) {
        ImGuiTreeNodeFlags nodeFlags = (id::invalid == selected_ ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx("Scene", nodeFlags);

        if (ImGui::IsItemClicked())
            selected_ = id::invalid;
        if (opened) {
            DrawSceneGraph(core::scene.Root());
            ImGui::TreePop();
        }
    } else {
        ImGui::Selectable("Scene");
    }
    ImGui::End();
}

void SceneGraph::DrawSceneGraph(core::Scene::Node &node, f32 depth) {
    ImGui::Indent(0.2);
//    ImGuiTreeNodeFlags TreeNodeEx_flags = ImGuiTreeNodeFlags_None;
    const char * name = node.entity.Component<core::Metadata>().Name().data();

    ImGuiTreeNodeFlags nodeFlags = (node.entity.Id() == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
    if (node.firstChild.IsAlive()) {
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    } else {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    const bool open = ImGui::TreeNodeEx(name, nodeFlags);

    if (ImGui::IsItemClicked()) {
        selected_ = node.entity.Id();
    }

    if (open and node.firstChild.IsAlive()) {
        DrawSceneGraph(core::scene.GetNode(node.firstChild.Id()), 0.2);
        ImGui::TreePop();
    }
    if (node.next.IsAlive()) {
        ImGui::Unindent(0.2);
        DrawSceneGraph(core::scene.GetNode(node.next.Id()), depth);
    }
    ImGui::Unindent(0.2);
}

//void SceneGraph::DrawSceneGraph() {
//
//    for (size_t i = 0; i < core::scene.NumEntities(); ++i) {
//
//        std::string name = core::scene.GetEntity(i).Name();
//        if (name[0] != '\0') {
//            if (ImGui::Selectable(name.c_str(), selected_ == i)) {
//                ImGui::SameLine();
//                ImGui::Button(ICON_FA_EYE);
//                selected_ = i;
//            }
//        } else {
//            if (ImGui::Selectable("##SelectedEntity", selected_ == i)) {
//                selected_ = i;
//            }
//        }
//    }

//}

}

