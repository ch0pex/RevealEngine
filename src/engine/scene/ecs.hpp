/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file scene.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief ECS
 *
 * Entity component system main header file.
 * - In rflect3d components classes are proxy classes that has an scene pointer and the id to the real data in a
 * pool_impl
 * - Components are proxy classes to access data stored in an aos pool_impl
 * - Real data is compacted to avoid cache misses, this logic is handled by components pools.
 * - Each component has a proxy class (Component class it self) and a pool_impl class with data
 *
 * ************************************************** Components pool_impl
 * **************************************************
 * ************************** IDs **************************************************** data ****************************
 *                                                          *                                                          *
 * Entity IDs        |  00   | 01    |  02   |  03  | ...   * Entity IDs        |  00   | 01    |  02   |  03  | ...   *
 *                                                          *                                                          *
 * --------------------- Components IDs-------------------- * ------------------- Components data -------------------- *
 *                  ------- ------- ------- ------          *                  ------- ------- -------                 *
 * Transform IDs   |   00  |  01   |  FF   |  02  |  ...    * Transforms      |       |       |       |  ...           *
 *                  ------- ------- ------- ------          *                  ------- ------- -------                 *
 *                  ------- ------- ------- ------          *                  ------- ------- -------                 *
 * Geometry IDs    |  00   |  FF   |  01   |  02  |  ...    * Geometries      |       |       |       |  ...           *
 *                  ------- ------- ------- ------          *                  ------- ------- -------                 *
 *                  ------- ------- ------- ------          *                  ------- -------                         *
 * Script IDs      |  00   |  FF   |  FF   |  01   |  ...   * Scripts         |       |       |  ...                   *
 *                  ------- ------- ------- ------          *                  ------- -------                         *
 * *********************************************************************************************************************
 */

#pragma once

#include "engine/core/data_types/id.hpp"
#include "systems.hpp"


namespace rflect3d {

namespace detail {

template<typename... Systems>
struct SystemMap {
public:
  template<typename SystemType>
  SystemType& get() {
    return std::get<SystemType>(data);
  }

private:
  std::tuple<Systems...> data;
};

} // namespace detail


template<typename Entity, typename... Systems>
class EntityComponentSystem {
public:
  using systems_type = detail::SystemMap<Systems...>;

  template<typename Component>
  auto system() -> typename Component::system_type& {
    return systems.template get<typename Component::system_type>();
  }

  Entity newEntity() { }

  Entity childEntity(Entity const parent) { }

  Entity changeParent(Entity const entity, Entity const newParent) { }

  void removeEntity(Entity const entity) { }

private:
  // EntityManager entities;
  systems_type systems;
};


// clang-format off
template<typename Entity> 
using Ecs = EntityComponentSystem<Entity, 
    ecs::systems::Metadata,
    ecs::systems::Transform
>;
// clang-format on

} // namespace rflect3d
