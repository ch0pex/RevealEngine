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
#include "metadata_data.hpp"

namespace rflect3d::ecs {

struct Metadata : Component<data::Metadata> {
  using Component::Component;

  [[nodiscard]] id_t id() const { return data().entity_id(); }

  std::string_view name() const { return data().name(); }

  std::string_view comment() const { return data().comment(); }

  std::string_view date() const { return data().date(); }
};

} // namespace rflect3d::ecs
