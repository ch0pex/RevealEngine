/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file entity_properties.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Entity properties UI drawing logic
 *
 */

#pragma once

#include "draw_geometry_component.hpp"
#include "draw_metadata_component.hpp"
#include "draw_transform_component.hpp"
#include "editor/utils/components.hpp"
#include "engine/scene/components/rigidbody.hpp"

namespace rflect3d::ui::entity_properties {

namespace detail { } // namespace detail

inline void draw(core::Entity const entity_id) {
  ImGui::Begin("Entity");

  if (entity_id.isAlive()) {
    // List of components that can be added
    if (ImGui::BeginCombo("##addcomp", "Add component")) {
      addComponent<core::Geometry>(entity_id, "Geometry");
      addComponent<core::Light>(entity_id, "Light");
      addComponent<core::Rigidbody>(entity_id, "Rigidbody");
      addComponent<core::Script>(entity_id, "Script");
      ImGui::EndCombo();
    }
    // Drawing components properties of this entity
    drawComponent<core::Metadata>(entity_id);
    drawComponent<core::Transform>(entity_id);
    drawComponent<core::Geometry>(entity_id);
    drawComponent<core::Light>(entity_id);
    drawComponent<core::Rigidbody>(entity_id);
    drawComponent<core::Script>(entity_id);
  }

  ImGui::End();
}

} // namespace rflect3d::ui::entity_properties
