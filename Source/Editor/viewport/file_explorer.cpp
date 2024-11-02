/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file file_explorer.cpp
 * @version 1.0
 * @date 03/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "file_explorer.hpp"
#include "imgui.h"

namespace fs = std::filesystem;

namespace reveal3d::ui {

FileNode::FileNode(const fs::path& path) : name(path.filename().string()), is_dir(fs::is_directory(path) ) {
    if (is_dir) {
        for (const auto& entry: fs::directory_iterator(path)) {
            if (const fs::path& file_name = entry.path();
                file_name.filename().c_str()[0] != '.' && fs::is_directory(entry.path())) {
                children.emplace_back(entry.path());
            }
        }
        for (const auto& entry: fs::directory_iterator(path)) {
            if (const fs::path& file_name = entry.path();
                file_name.filename().c_str()[0] != '.' && !fs::is_directory(entry.path())) {
                children.emplace_back(entry.path());
            }
        }
    }
}

FileExplorer::FileExplorer(const std::string_view root_path) : root_(root_path) {

}

void FileExplorer::draw() const {
    ImGui::Begin("File Explorer");
    if (!root_.name.empty()) {
        drawFileTree(root_);
    }
    ImGui::End();
}

void FileExplorer::drawFileTree(const FileNode &node, const u32 depth) {
    ImGui::Indent(depth * 5.0F);

    if (node.is_dir) {
        if (ImGui::TreeNode(node.name.c_str())) {
            for (const auto& child : node.children) {
                drawFileTree(child, depth + 1);
            }
            ImGui::TreePop();
        }
    } else {
        ImGui::Selectable(node.name.c_str());
    }

    ImGui::Unindent(depth * 5.0F);
}

}