/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file EnityProperties.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "imgui/imgui.h"

#include "core/scene.hpp"

namespace reveal3d::ui {

class EntityProperties {
public:
  EntityProperties();
  void draw(u32 entity_id);

private:
  void drawMetadata() const;
  void drawTransform() const;
  void drawGeometry();

  core::Entity entity_;
};

} // namespace reveal3d::ui
