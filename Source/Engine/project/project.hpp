/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file project.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include <string>
#include "common/platform.hpp"

namespace reveal3d {

class Project {
public:
  Project() = default;
  explicit Project(std::string_view path);
  const std::string& rootPath() { return root_path_; }

private:
  std::string root_path_;
};

inline Project load_project(const std::span<char*> args) {
  if (args.size() != 2) {
    logger(LogWarning) << "No project file was provided, using default settings";
    return {};
  }

  try {
  }
  catch (const std::exception& e) {
  }
}

} // namespace reveal3d
