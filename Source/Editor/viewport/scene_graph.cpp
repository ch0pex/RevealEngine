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
            selected_ = core::scene.newChildEntity(selected_).id();
        } else {
            selected_ = core::scene.newEntity().id();
        }
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Entity")) {
        selected_ = core::scene.removeEntity(selected_).id();
    }

    ImGui::BeginChild("SceneArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
    if (core::scene.count() != 0u) {
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
    const char * name = node->entity.component<core::Metadata>().name().data();

    ImGuiTreeNodeFlags nodeFlags = (node->entity.id() == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
    if (node->first_child.isAlive()) {
        nodeFlags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    } else {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    const bool open = ImGui::TreeNodeEx(name, nodeFlags);

    if (ImGui::IsItemClicked()) {
        selected_ = node->entity.id();
    }

    if (open and node->first_child.isAlive()) {
        ImGui::Indent(0.2);
        auto children = node->getChildren();
        for (const auto &child : children) {
            DrawTreeNode(&core::scene.getNode(child));
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
    int nLeafCanDraw = min(i32(vWindowSize.y / vItemSize.y), (i32)core::scene.count() - nLeafStart);

    //blank rect for those node beyond window
    if (nLeafStart > 0 && nLeafCanDraw > 0) {
        ImGui::Dummy(ImVec2(10.0f, f32(nLeafStart) * vItemSize.y));
    }

    //all the node we could see
    u32 nDrawLeaf = nLeafStart;
    u32 index = nDrawLeaf;
    while (nDrawLeaf < nLeafCanDraw + nLeafStart && nDrawLeaf < core::scene.count()) {
        const auto &cur_node = core::scene.getNode(index);
        if (cur_node.entity.isAlive() and not cur_node.parent.isAlive()) {
            DrawTreeNode(&cur_node);
            nDrawLeaf++;
        }
        index++;
    }
    if (nDrawLeaf < core::scene.count()) {
        ImGui::Dummy(ImVec2(10.0f, f32(core::scene.count() - nDrawLeaf) * vItemSize.y));
    }
}

}

