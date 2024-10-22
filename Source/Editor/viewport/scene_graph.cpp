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
    ImGui::Begin("Scene graph");
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
            drawSceneGraph();
            ImGui::TreePop();
        }
    } else {
        ImGui::Selectable("Scene");
    }
    ImGui::EndChild();
    ImGui::End();
}

bool SceneGraph::drawTreeNode(const core::Scene::Node *const node) {
    //    ImGuiTreeNodeFlags TreeNodeEx_flags = ImGuiTreeNodeFlags_None;
    const char * name = node->entity.component<core::Metadata>().name().data();

    ImGuiTreeNodeFlags node_flags = (node->entity.id() == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
    if (node->first_child.isAlive()) {
        node_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
    } else {
        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }
    const bool open = ImGui::TreeNodeEx(name, node_flags);

    if (ImGui::IsItemClicked()) {
        selected_ = node->entity.id();
    }

    if (open and node->first_child.isAlive()) {
        ImGui::Indent(0.2);
        auto children = node->getChildren();
        for (const auto &child : children) {
            drawTreeNode(&core::scene.getNode(child));
        }
        ImGui::TreePop();
        ImGui::Unindent(0.2);
    }
    return open;

}

void SceneGraph::drawSceneGraph() {
    const ImVec2 last_item = ImGui::GetItemRectMax();
    const ImVec2 item_size = ImGui::GetItemRectSize();
    const ImVec2 window_pos = ImGui::GetWindowPos();
    const ImVec2 window_size = ImGui::GetWindowSize();

    //measure the number of node to draw
    const int n_leaf_start = max(i32((window_pos.y - last_item.y) / item_size.y), 0);
    const int n_leaf_can_draw = min(i32(window_size.y / item_size.y), (i32)core::scene.count() - n_leaf_start);

    //blank rect for those node beyond window
    if (n_leaf_start > 0 && n_leaf_can_draw > 0) {
        ImGui::Dummy(ImVec2(10.0f, f32(n_leaf_start) * item_size.y));
    }

    //all the node we could see
    u32 draw_leaf = n_leaf_start;
    u32 index = draw_leaf;
    while (draw_leaf < n_leaf_can_draw + n_leaf_start && draw_leaf < core::scene.count() && index < core::scene.graph().size()) {
        const auto &cur_node = core::scene.getNode(index);
        if (cur_node.entity.isAlive() and not cur_node.parent.isAlive()) {
            drawTreeNode(&cur_node);
            draw_leaf++;
        }
        index++;
    }
    if (draw_leaf < core::scene.count()) {
        ImGui::Dummy(ImVec2(10.0f, f32(core::scene.count() - draw_leaf) * item_size.y));
    }
}

}

