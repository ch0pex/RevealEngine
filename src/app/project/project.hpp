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
#include "engine/core/core.hpp"

#include <span>

namespace rflect3d {

class Project {
public:
  Project() = default;
  explicit Project(std::string_view path) { }
  std::string const& rootPath() { return root_path_; }

private:
  std::string root_path_;
};

inline Project load_project(std::span<char*> const args) {
  if (args.size() != 2) {
    logger(LogWarning) << "No project file was provided, using default settings";
    return {};
  }

  try {
  }
  catch (std::exception const& e) {
  }
}

} // namespace rflect3d
