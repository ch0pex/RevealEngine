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
        for (const auto& entry : fs::directory_iterator(path)) {
            fs::path file_name = entry.path();
            if (file_name.filename().c_str()[0] != '.' && fs::is_directory(entry.path())) {
                children.push_back(FileNode(entry.path()));
            }
        }
        for (const auto& entry : fs::directory_iterator(path)) {
            fs::path file_name = entry.path();
            if (file_name.filename().c_str()[0] != '.' && !fs::is_directory(entry.path())) {
                children.push_back(FileNode(entry.path()));
            }
        }
    }
}

FileExplorer::FileExplorer(std::string_view root_path) : root_(root_path) {

}

void FileExplorer::draw() {
    ImGui::Begin("File Explorer");
    drawFileTree(root_);
    ImGui::End();
}

void FileExplorer::drawFileTree(const FileNode &node, u32 depth) {
    ImGui::Indent(depth * 5.0f);

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

    ImGui::Unindent(depth * 5.0f);
}

}