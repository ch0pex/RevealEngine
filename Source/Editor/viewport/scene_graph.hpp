/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Scene Graph UI component
 *
 */

#pragma once

#include "imgui/imgui.h"

#include "core/scene.hpp"

#include <string>
#include <vector>

#include "core/entity.hpp"

namespace reveal3d::ui {

class SceneGraph {
public:
  SceneGraph();
  void Draw();
  core::Entity selected() const { return selected_; }

private:
  bool drawTreeNode(core::Entity node);
  void drawSceneGraph();

  core::Entity selected_;
};

} // namespace reveal3d::ui
