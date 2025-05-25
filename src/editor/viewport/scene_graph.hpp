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


#include "core/entity.hpp"
#include "core/scene.hpp"

#include <imgui.h>
#include <string>
#include <vector>

namespace reveal3d::ui {

class SceneGraph {
public:
  SceneGraph(core::Scene& scene);
  void draw();
  core::Entity selected() const { return selected_; }

private:
  bool drawTreeNode(core::Entity node);
  void drawSceneGraph();

  core::Entity selected_;
  core::Scene* scene_;
};

} // namespace reveal3d::ui
