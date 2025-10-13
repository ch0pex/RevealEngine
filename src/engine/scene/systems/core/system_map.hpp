/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file system_map.hpp
 * @version 1.0
 * @date 8/15/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include <rflect/converters/struct_to_tuple.hpp>
#include <tuple>

namespace rflect3d::ecs {

template<typename... Systems>
class SystemMap {
public:
  SystemMap() { }

  template<typename SystemType>
  SystemType& get() {
    return std::get<SystemType>(systems);
  }

  void newComponents(id_t const entity_id) {
    template for (auto& system: systems) {
      using system_type = std::remove_reference_t<decltype(system)>;
      if constexpr (system_type::is_core::value) {
        system.add(entity_id);
      }
    }
  }

  void removeComponents(id_t const entity_id) {
    template for (auto& system: systems) { system.remove(entity_id); }
  }

private:
  std::tuple<Systems...> systems;
};

} // namespace rflect3d::ecs
