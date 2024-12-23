/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "imgui/imgui.h"

#include "core/scene.hpp"

#include <string>
#include <vector>

namespace reveal3d::ui {

class SceneGraph {
public:
  SceneGraph();
  void Draw();
  u32 selected() { return selected_; }

private:
  bool drawTreeNode(core::Scene::Node const* constnode);
  void drawSceneGraph();

  u32 selected_;
};

} // namespace reveal3d::ui
