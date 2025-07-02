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

#include "components/system.hpp"

// Components data includes
#include "components/behaviour/behaviour_data.hpp"
#include "components/collider/collider_data.hpp"
#include "components/light/light_data.hpp"
#include "components/metadata/metadata_data.hpp"
#include "components/rigidbody/rigidbody_data.hpp"
#include "components/transform/transform_data.hpp"
#include "core/data_types/id.hpp"


namespace rflect3d {

class EntityManager {
public:
private:
  rflect3d::id::Factory id_factory;
  // std::vector<ecs::Entity> entities;
};

template<typename... DataTypes>
struct SystemMap {
  template<typename DataType>
  decltype(auto) get() {
    return std::get<ecs::System<DataType>>(data);
  }

  std::tuple<ecs::System<DataTypes>...> data;
};


template<typename Entity>
class Ecs {
public:
  using systems_type = SystemMap<ecs::data::Transform>;

  template<typename Component>
  auto system() -> ecs::System<typename Component::data_type>& {
    return systems.get<typename Component::data_type>();
  }

  Entity newEntity() { }

  Entity childEntity(Entity const parent) { }

  void removeEntity(Entity const entity) { }

private:
  EntityManager entities;
  systems_type systems;
};


} // namespace rflect3d
