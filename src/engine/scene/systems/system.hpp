/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file base_system.hpp
 * @version 1.0
 * @date 6/23/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include "data_types.hpp"
#include "engine/core/core.hpp"
#include "rflect/concepts/proxy_concepts.hpp"

namespace rflect3d::ecs {

/**
 * Container for component data. Stores data in SoA layout and
 * maps entities ids to the corresponding data
 *
 * @tparam Component Component type
 * @tparam Core Indicates if the system must be mandatory for all entities
 */
template<rflect::has_proxy Component, typename Core = std::false_type>
class System {
public:
  /**********************************
   *          Member types          *
   **********************************/
  using data_type      = Component;
  using container_type = container_type<data_type>;
  using proxy_type     = proxy_data<data_type>;
  using is_core        = Core;
  using size_type      = container_type::size_type;

  /**********************************
   *        Member functions        *
   **********************************/

  // ********* Constructors *********
  System() = default;

  void add(id_t const entity_id, data_type const& component = {}) {
    auto const index = static_cast<index_t>(components.size());
    components.push_back(component);
    id_index_map.insert(entity_id, index);
  }

  void remove(id_t const entity_id) {
    // Get the index of the entity component
    auto const index = index_t {id_index_map.at(entity_id)};

    // Get id and index of the back element
    auto const back_index = index_t {static_cast<u32>(components.size()) - 1};
    auto const back_id    = id_index_map.at(back_index);

    // Copy back to index and remove back
    components.at(static_cast<size_type>(index)) = components.back();
    components.pop_back();

    // Update id and index map
    id_index_map.erase(entity_id);
    id_index_map.insert(back_id, index);
  }

  [[nodiscard]] id_t entityId(index_t const index) const { return id_index_map.at(index); }

  [[nodiscard]] index_t entityIndex(id_t const id) const { return id_index_map.at(id); }

  [[nodiscard]] u32 size() const { return components.size(); }

  template<typename Self>
  auto at(this Self&& self, id_t const entity_id) {
    index_t const index = self.id_index_map.at(entity_id);
    return std::forward<Self>(self).components.at(static_cast<size_type>(index));
  }

  template<typename Self>
  auto at(this Self&& self, index_t const index) {
    return std::forward<Self>(self).components.at(static_cast<size_type>(index));
  }
  template<typename Self>
  auto begin(this Self&& self) {
    return std::ranges::begin(std::forward<Self>(self).components);
  }

  template<typename Self>
  auto end(this Self&& self) {
    return std::ranges::end(std::forward<Self>(self).components);
  }

  void swap(index_t const lh_index, index_t const rh_index) {
    auto const rh_id = id_index_map.at(rh_index);
    auto const lh_id = id_index_map.at(rh_index);
  }

private:
  core::BiMap<id_t, index_t> id_index_map;
  container_type components {};
};


} // namespace rflect3d::ecs
