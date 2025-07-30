/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file metadata_proxy.hpp
 * @version 1.0
 * @date 01/07/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/scene/components/component.hpp"
#include "engine/scene/systems/metadata/metadata_system.hpp"

namespace rflect3d::ecs {

struct Metadata : Component<systems::Metadata> {
  using Component<systems::Metadata>::Component;

  [[nodiscard]] id_t id() const { return data().entity_id(); }

  [[nodiscard]] std::string_view name() const { return data().name(); }

  [[nodiscard]] std::string_view comment() const { return data().comment(); }

  [[nodiscard]] std::string_view date() const { return data().date(); }
};

} // namespace rflect3d::ecs
