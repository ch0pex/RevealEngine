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

#include <limits>
#include "data_types.hpp"
#include "engine/core/core.hpp"
#include "rflect/concepts/proxy_concepts.hpp"

#include <vector>

namespace rflect3d::ecs {


/**
 * Container for component data. Stores data in SoA layout and
 * maps entities ids to the corresponding data
 * @tparam Component Component type
 */
template<rflect::has_proxy Component>
class ComponentContainer {
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
  ComponentContainer() = default;

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

  [[nodiscard]] id_t entityId(index_t const index) const { return id_index_map.at(index); }

  [[nodiscard]] index_t entityIndex(id_t const id) const { return id_index_map.at(id); }

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

  void swap(index_t lh_index, index_t rh_index) {
    auto const rh_id = id_index_map.at(rh_index);
    auto const lh_id = id_index_map.at(rh_index);
  }

private:
  core::BiMap<id_t, index_t> id_index_map;
  container_type components {};
};

template<rflect::has_proxy Component>
class GpuComponentContainer {
public:
  using container_type = ComponentContainer<Component>;
  using data_type      = container_type::data_type;

  void add(id_t const entity_id, data_type const& component = {}) {
    dirtness[components.size()] = 3; // register dirtness
    components.add(entity_id, component);
  }

  void remove(id_t const entity_id) {
    //
    components.remove(entity_id);
  }

  [[nodiscard]] id_t entityId(index_t const index) const { return components.entity_id(index); }

  [[nodiscard]] u32 count() const { return components.size(); }

  auto at(id_t const entity_id) {
    setDirty(entity_id);
    return components.at(entity_id);
  }

  auto at(id_t const entity_id) const { return components.at(entity_id); }

  auto at(index_t const index) {
    setDirty(index);
    return components.at(index);
  }

  auto at(index_t const index) const { return components.at(static_cast<u64>(index)); }

  // auto dirties() { return std::ranges::subrange(components.begin() + dirty_count, components.end()); }
  //

  template<typename Func>
  void updateDirties(Func&& func) {
    auto dirties = std::ranges::subrange(components.begin() + first_dirty, components.end());

    std::ranges::for_each(dirties, std::forward<Func>(func));
    std::ranges::transform(dirtness.values(), [](u8 value) { //
      return --value;
    });
  }

  void cleanDirtySection() {
    std::vector<u32> clean_components;
    clean_components.reserve(count() - first_dirty);

    auto is_clean = [](u32 const value) { return value <= 0; };

    // Check index that are clean
    for (auto [index, value]: dirtness) {
      if (value <= 0) {
        clean_components.push_back(static_cast<u32>(index));
      }
    }

    // Swaping and restoring algorithm
    for (auto index: clean_components) {
      if (index == first_dirty) {
        // Remove dirtness and increment first_dirty
        dirtness.erase(index_t {first_dirty});
        ++first_dirty;
        continue;
      }

      // Swap dirntess
      dirtness[index_t {index}] = dirtness[index_t {first_dirty}];
      dirtness.erase(index_t {first_dirty});

      // Swap data
      components.swap(first_dirty, index);
      ++first_dirty;
    }
  }

  template<typename Self>
  auto begin(this Self&& self) {
    return std::forward<Self>(self).components.begin();
  }

  template<typename Self>
  auto end(this Self&& self) {
    return std::forward<Self>(self).components.end();
  }

  void setDirty(index_t const index) {
    auto idx = static_cast<u32>(index);
    if (idx >= first_dirty) {
      dirtness[index] = 3;
      return;
    }
    --first_dirty;

    if (idx == first_dirty - 1) {
      dirtness[index] = 3;
      return;
    }

    dirtness[index_t {first_dirty}] = 3;
    components.swap(index, index_t {first_dirty});
  }

  void setDirty(id_t const id) { }

private:
  ComponentContainer<Component> components;
  u32 first_dirty {0};
  std::flat_map<index_t, u8> dirtness {};
};

template<rflect::has_proxy T>
using System = ComponentContainer<T>;

} // namespace rflect3d::ecs
