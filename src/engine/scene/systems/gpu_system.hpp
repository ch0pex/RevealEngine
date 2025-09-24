/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file gpu_system.hpp
 * @version 1.0
 * @date 8/15/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include <ranges>
#include "system.hpp"

namespace rflect3d::ecs {

/**
 * System for components that are stored in GPU
 *
 * @tparam Component Component type
 * @tparam Core Indicates if the system must be mandatory for all entities
 */
template<rflect::has_proxy Component, typename Core = std::false_type>
class GPUSystem {
public:
  using container_type = System<Component>;
  using data_type      = container_type::data_type;
  using is_core        = Core;

  void add(id_t const entity_id, data_type const& component = {}) {
    dirtness[index_t {components.count()}] = 3; // register dirtiness
    components.add(entity_id, component);
  }

  void remove(id_t const entity_id) {
    //
    components.remove(entity_id);
  }

  [[nodiscard]] id_t entityId(index_t const index) const { return components.entityId(index); }

  [[nodiscard]] u32 count() const { return components.count(); }

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

  template<typename Func>
  void updateDirties(Func&& func) {

    // auto dirties = std::ranges::subrange(components.begin() + first_dirty, components.end());
    //
    // std::ranges::for_each(dirties, std::forward<Func>(func));
    // std::ranges::for_each(dirtness.values(), [](u8& value) { //
    //   --value;
    // });
  }

  template<typename Self>
  auto begin(this Self&& self) {
    return std::forward<Self>(self).components.begin();
  }

  template<typename Self>
  auto end(this Self&& self) {
    return std::forward<Self>(self).components.end();
  }

  void setDirty(id_t const id) { }

private:
  container_type components;
  std::flat_map<index_t, u8> dirtness {};
};

/// --- Implementation with dirty elements ordering ---
// /**
//  * System for components that are stored in GPU
//  *
//  * @tparam Component Component type
//  * @tparam Core Indicates if the system must be mandatory for all entities
//  */
// template<rflect::has_proxy Component, typename Core = std::false_type>
// class GPUSystem {
// public:
//   using container_type = System<Component>;
//   using data_type      = container_type::data_type;
//   using is_core        = Core;
//
//   void add(id_t const entity_id, data_type const& component = {}) {
//     dirtness[index_t {components.count()}] = 3; // register dirtiness
//     components.add(entity_id, component);
//   }
//
//   void remove(id_t const entity_id) {
//     //
//     components.remove(entity_id);
//   }
//
//   [[nodiscard]] id_t entityId(index_t const index) const { return components.entityId(index); }
//
//   [[nodiscard]] u32 count() const { return components.count(); }
//
//   auto at(id_t const entity_id) {
//     setDirty(entity_id);
//     return components.at(entity_id);
//   }
//
//   auto at(id_t const entity_id) const { return components.at(entity_id); }
//
//   auto at(index_t const index) {
//     setDirty(index);
//     return components.at(index);
//   }
//
//   auto at(index_t const index) const { return components.at(static_cast<u64>(index)); }
//
//   template<typename Func>
//   void updateDirties(Func&& func) {
//     auto dirties = std::ranges::subrange(components.begin() + first_dirty, components.end());
//
//     std::ranges::for_each(dirties, std::forward<Func>(func));
//     std::ranges::for_each(dirtness.values(), [](u8& value) { //
//       --value;
//     });
//   }
//
//   void cleanDirtySection() {
//     std::vector<u32> clean_components;
//     clean_components.reserve(count() - first_dirty);
//
//     auto is_clean = [](u32 const value) { return value <= 0; };
//
//     // Check index that are clean
//     for (auto [index, value]: dirtness) {
//       if (value <= 0) {
//         clean_components.push_back(static_cast<u32>(index));
//       }
//     }
//
//     // Swaping and restoring algorithm
//     for (auto index: clean_components) {
//       if (index == first_dirty) {
//         // Remove dirtness and increment first_dirty
//         dirtness.erase(index_t {first_dirty});
//         ++first_dirty;
//         continue;
//       }
//
//       // Swap dirntess
//       dirtness[index_t {index}] = dirtness[index_t {first_dirty}];
//       dirtness.erase(index_t {first_dirty});
//
//       // Swap data
//       components.swap(first_dirty, index);
//       ++first_dirty;
//     }
//   }
//
//   template<typename Self>
//   auto begin(this Self&& self) {
//     return std::forward<Self>(self).components.begin();
//   }
//
//   template<typename Self>
//   auto end(this Self&& self) {
//     return std::forward<Self>(self).components.end();
//   }
//
//   void setDirty(index_t const index) {
//     auto idx = static_cast<u32>(index);
//     if (idx >= first_dirty) {
//       dirtness[index] = 3;
//       return;
//     }
//     --first_dirty;
//
//     if (idx == first_dirty - 1) {
//       dirtness[index] = 3;
//       return;
//     }
//
//     dirtness[index_t {first_dirty}] = 3;
//     components.swap(index, index_t {first_dirty});
//   }
//
//   void setDirty(id_t const id) { }
//
// private:
//   container_type components;
//   u32 first_dirty {0};
//   std::flat_map<index_t, u8> dirtness {};
// };
} // namespace rflect3d::ecs
