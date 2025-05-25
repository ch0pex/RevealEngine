/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file file_explorer.cpp
 * @version 1.0
 * @date 03/06/2024
 * @brief File explorer UI component
 *
 */

#include "file_explorer.hpp"
#include <imgui.h>

namespace fs = std::filesystem;

namespace reveal3d::ui {

FileNode::FileNode(fs::path const& path) : name(path.filename().string()), is_dir(fs::is_directory(path)) {
  if (is_dir) {
    for (auto const& entry: fs::directory_iterator(path)) {
      if (fs::path const& file_name = entry.path();
          file_name.filename().c_str()[0] != '.' && fs::is_directory(entry.path())) {
        children.emplace_back(entry.path());
      }
    }
    for (auto const& entry: fs::directory_iterator(path)) {
      if (fs::path const& file_name = entry.path();
          file_name.filename().c_str()[0] != '.' && !fs::is_directory(entry.path())) {
        children.emplace_back(entry.path());
      }
    }
  }
}

FileExplorer::FileExplorer(std::string_view const root_path) : root_(root_path) { }

void FileExplorer::draw() const {
  ImGui::Begin("File Explorer");
  if (!root_.name.empty()) {
    drawFileTree(root_);
  }
  ImGui::End();
}

void FileExplorer::drawFileTree(FileNode const& node, u32 const depth) {
  ImGui::Indent(depth * 5.0F);

  if (node.is_dir) {
    if (ImGui::TreeNode(node.name.c_str())) {
      for (auto const& child: node.children) {
        drawFileTree(child, depth + 1);
      }
      ImGui::TreePop();
    }
  }
  else {
    ImGui::Selectable(node.name.c_str());
  }

  ImGui::Unindent(depth * 5.0F);
}

} // namespace reveal3d::ui
