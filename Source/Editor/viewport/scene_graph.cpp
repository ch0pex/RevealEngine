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
    ImGui::Indent(depth * 3.0f);
//    ImGuiTreeNodeFlags TreeNodeEx_flags = ImGuiTreeNodeFlags_None;
    const char * name = node.entity.Component<core::Metadata>().Name().data();

    if (node.firstChild.IsAlive() ) { // NOTE: All this invalid in a future will need to be IsAlive
        ImGuiTreeNodeFlags nodeFlags = (node.entity.Id() == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx(name, nodeFlags);

        if (ImGui::IsItemClicked())
            selected_ = node.entity.Id();
        if (opened) {
            DrawSceneGraph(core::scene.GetNode(node.firstChild.Id()), depth + 1);
            ImGui::TreePop();
        }

    } else {
        if (ImGui::Selectable(name, selected_ == node.entity.Id())) {
            selected_ = node.entity.Id();
        }
        if (node.next.IsAlive()) {
            ImGui::Unindent( depth * 3.0f);
            DrawSceneGraph(core::scene.GetNode(node.next.Id()), depth);
        }
    }

    ImGui::Unindent(depth * 3.0f);
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

