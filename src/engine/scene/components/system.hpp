/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file system.hpp
 * @version 1.0
 * @date 6/23/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include "engine/core/core.hpp"
#include "engine/scene/components/data_types.hpp"


namespace rflect3d::ecs {

class DirtyTracker {
public:
};

/**
 * A system is a component container
 * @tparam Component Component type
 */
template<class Component>
class System {
public:
  /**********************************
   *          Member types          *
   **********************************/
  using data_type      = Component;
  using container_type = container_type<data_type>;
  using proxy_type     = proxy_component<data_type>;

  /**********************************
   *        Member functions        *
   **********************************/

  // ********* Constructors *********
  System() = default;

  void add(id_t const entity_id, data_type const& component = {}) {
    components.push_back(component);
    id_index_map.insert(entity_id, components.size());
  }

  void remove(id_t const entity_id) {
    // Get the index of the entity component
    auto const index = index_t {id_index_map.at(entity_id)};

    // Get id and index of the back element
    auto const back_index = index_t {components.size() - 1};
    auto const back_id    = id_index_map.at(back_index);

    // Copy back to index and remove back
    components.at(index) = components.back();
    components.pop_back();

    // Update id and index map
    id_index_map.erase(entity_id);
    id_index_map.insert(back_id, index);
  }

  [[nodiscard]] id_t entity_id(index_t const index) const { return id_index_map.at(index); }

  [[nodiscard]] u32 count() const { return components.size(); }

  template<typename Self>
  auto at(this Self&& self, id_t const entity_id) {
    index_t const index = self.id_index_map.at(entity_id);
    return std::forward<Self>(self).components.at(static_cast<u64>(index));
  }

  template<typename Self>
  auto at(this Self&& self, index_t const index) {
    return std::forward<Self>(self).components.at(static_cast<u64>(index));
  }

  template<typename Self>
  auto begin(this Self&& self) {
    return std::forward<Self>(self).components.begin();
  }

  template<typename Self>
  auto end(this Self&& self) {
    return std::forward<Self>(self).components.end();
  }

private:
  core::BiMap<id_t, index_t> id_index_map;
  container_type components {};
};

} // namespace rflect3d::ecs
