/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file file_explorer.hpp
 * @version 1.0
 * @date 03/06/2024
 * @brief File explorer UI component
 *
 */

#pragma once

#include "common/common.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace rflect3d::ui {

struct FileNode {
  explicit FileNode(std::filesystem::path const& path);
  std::string name {};
  std::vector<FileNode> children;
  bool is_dir;
};

class FileExplorer {
public:
  explicit FileExplorer(std::string_view root_path);
  void draw() const;
  static void drawFileTree(FileNode const& node, u32 depth = 0);

private:
  FileNode root_;
  std::string current_path_;
};

} // namespace rflect3d::ui
