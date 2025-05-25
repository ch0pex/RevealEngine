/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Scene graph UI component
 *
 */

#include "scene_graph.hpp"

#include "core/components/metadata.hpp"
#include "core/entity.hpp"


using namespace std::literals::string_literals;

namespace reveal3d::ui {

SceneGraph::SceneGraph(core::Scene& scene) : selected_(&scene, std::numeric_limits<u32>::max()), scene_(&scene) { }

void SceneGraph::draw() {
  ImGui::Begin("Scene graph");
  if (ImGui::Button("Add Entity")) {
    if (selected_.isAlive()) {
      selected_ = {scene_, scene_->newChildEntity(selected_.id())};
    }
    else {
      selected_ = {scene_, scene_->newEntity()};
    }
  }
  ImGui::SameLine();
  if (ImGui::Button("Remove Entity")) {
    selected_ = {scene_, scene_->removeEntity(selected_.id())};
  }

  ImGui::BeginChild("SceneArea", ImVec2(0, 0), 1, ImGuiWindowFlags_HorizontalScrollbar);
  if (scene_->count() != 0U) {
    ImGuiTreeNodeFlags nodeFlags =
        (id::invalid == selected_.id() ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
    bool const open = ImGui::TreeNodeEx("Scene", nodeFlags);

    if (ImGui::IsItemClicked())
      selected_ = {scene_, id::invalid};
    if (open) {
      drawSceneGraph();
      ImGui::TreePop();
    }
  }
  else {
    ImGui::Selectable("Scene");
  }
  ImGui::EndChild();
  ImGui::End();
}

bool SceneGraph::drawTreeNode(core::Entity const entity) {
  //    ImGuiTreeNodeFlags TreeNodeEx_flags = ImGuiTreeNodeFlags_None;
  char const* name = entity.component<core::Metadata>().name().data();

  ImGuiTreeNodeFlags node_flags = (entity == selected_ ? ImGuiTreeNodeFlags_Selected : 0);
  if (entity.firstChild().isAlive()) {
    node_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;
  }
  else {
    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
  }
  bool const open = ImGui::TreeNodeEx(name, node_flags);

  if (ImGui::IsItemClicked()) {
    selected_ = entity;
  }

  if (open and entity.firstChild().isAlive()) {
    ImGui::Indent(0.2);
    for (auto const children = entity.children(); auto const& child: children) {
      drawTreeNode(child);
    }
    ImGui::TreePop();
    ImGui::Unindent(0.2);
  }
  return open;
}

void SceneGraph::drawSceneGraph() {
  ImVec2 const last_item   = ImGui::GetItemRectMax();
  ImVec2 const item_size   = ImGui::GetItemRectSize();
  ImVec2 const window_pos  = ImGui::GetWindowPos();
  ImVec2 const window_size = ImGui::GetWindowSize();

  // measure the number of node to draw
  int const n_leaf_start = std::max(static_cast<i32>((window_pos.y - last_item.y) / item_size.y), 0);
  int const n_leaf_can_draw =
      std::min(static_cast<i32>(window_size.y / item_size.y), static_cast<i32>(scene_->count()) - n_leaf_start);

  // blank rect for those node beyond window
  if (n_leaf_start > 0 && n_leaf_can_draw > 0) {
    ImGui::Dummy(ImVec2(10.0f, static_cast<f32>(n_leaf_start) * item_size.y));
  }

  // all the node we could see
  u32 draw_leaf = n_leaf_start;
  u32 index     = draw_leaf;
  while (draw_leaf < n_leaf_can_draw + n_leaf_start && draw_leaf < scene_->count() && index < scene_->graph().size()) {
    core::Entity const cur_node = {scene_, scene_->entity(index)};
    if (cur_node.isAlive() and not cur_node.parent().isAlive()) {
      drawTreeNode(cur_node);
      draw_leaf++;
    }
    index++;
  }
  if (draw_leaf < scene_->count()) {
    ImGui::Dummy(ImVec2(10.0F, static_cast<f32>(scene_->count() - draw_leaf) * item_size.y));
  }
}

} // namespace reveal3d::ui
