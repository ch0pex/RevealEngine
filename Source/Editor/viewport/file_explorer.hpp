/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file file_explorer.hpp
 * @version 1.0
 * @date 03/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "common/common.hpp"

#include <string>
#include <vector>
#include <filesystem>

namespace reveal3d::ui {

struct FileNode {
    FileNode(const std::filesystem::path& path);
    std::string name;
    std::vector<FileNode> children;
    bool is_dir;

};

class FileExplorer {
public:
    FileExplorer(std::string_view root_path);
    void draw();
    void drawFileTree(const FileNode &node, u32 depth = 0);
private:
    FileNode root_;
    std::string current_path_;
};

}

