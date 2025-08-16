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
#include "engine/scene/systems/data_types.hpp"
#include "engine/scene/systems/system.hpp"


#include <string>

namespace rflect3d::ecs {

namespace data {

struct Metadata {
  DEFINE_COMPONENT_PROXY(entity_id, name, comment, date);
  id_t entity_id {};
  std::string name {};
  std::string comment {};
  std::string date {};
};

} // namespace data

using Metadata = core_component<data::Metadata, System>;

} // namespace rflect3d::ecs
