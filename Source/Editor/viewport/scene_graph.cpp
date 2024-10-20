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
        selected_ = core::scene.RemoveEntity(selected_).Id();
    }

    ImGui::BeginChild("SceneArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    if (core::scene.Count() != 0u) {
        ImGuiTreeNodeFlags nodeFlags = (id::invalid == selected_ ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
        const bool open = ImGui::TreeNodeEx("Scene", nodeFlags);

        if (ImGui::IsItemClicked())
            selected_ = id::invalid;
        if (open) {
            DrawSceneGraph();
            ImGui::TreePop();
        }
    } else {
        ImGui::Selectable("Scene");
    }
    ImGui::EndChild();
    ImGui::End();
}

bool SceneGraph::DrawTreeNode(const core::Scene::Node * const node) {
    //    ImGuiTreeNodeFlags TreeNodeEx_flags = ImGuiTreeNodeFlags_None;
    const char * name = node->entity.Component<core::Metadata>().Name().data();

    ImGuiTreeNodeFlags nodeFlags = (node->entity.Id() == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
    if (node->firstChild.IsAlive()) {
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    } else {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    const bool open = ImGui::TreeNodeEx(name, nodeFlags);

    if (ImGui::IsItemClicked()) {
        selected_ = node->entity.Id();
    }

    if (open and node->firstChild.IsAlive()) {
        ImGui::Indent(0.2);
        auto children = node->GetChildren();
        for (const auto &child : children) {
            DrawTreeNode(&core::scene.GetNode(child));
        }
        ImGui::TreePop();
        ImGui::Unindent(0.2);
    }
    return open;

}

void SceneGraph::DrawSceneGraph() {
    ImVec2  vLastItem = ImGui::GetItemRectMax();
    ImVec2  vItemSize = ImGui::GetItemRectSize();
    ImVec2  vWindowPos = ImGui::GetWindowPos();
    ImVec2  vWindowSize = ImGui::GetWindowSize();

    //measure the number of node to draw
    int nLeafStart = max(i32((vWindowPos.y - vLastItem.y) / vItemSize.y), 0);
    int nLeafCanDraw = min(i32(vWindowSize.y / vItemSize.y), (i32)core::scene.Count() - nLeafStart);

    //blank rect for those node beyond window
    if (nLeafStart > 0 && nLeafCanDraw > 0) {
        ImGui::Dummy(ImVec2(10.0f, f32(nLeafStart) * vItemSize.y));
    }

    //all the node we could see
    u32 nDrawLeaf = nLeafStart;
    u32 index = nDrawLeaf;
    while (nDrawLeaf < nLeafCanDraw + nLeafStart && nDrawLeaf < core::scene.Count()) {
        const auto &cur_node = core::scene.GetNode(index);
        if (cur_node.entity.IsAlive() and not cur_node.parent.IsAlive()) {
            DrawTreeNode(&cur_node);
            nDrawLeaf++;
        }
        index++;
    }
    if (nDrawLeaf < core::scene.Count()) {
        ImGui::Dummy(ImVec2(10.0f, f32(core::scene.Count() - nDrawLeaf) * vItemSize.y));
    }
}

}

