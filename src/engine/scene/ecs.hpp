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

#include "components.hpp"
#include "scene_graph.hpp"
#include "systems/system_map.hpp"

#include <ranges>

namespace rflect3d {


/**
 * @tparam Entity Entity type for the ECS
 * @tparam Components Possible components for every entity
 */
template<typename Entity, typename... Components>
class EntityComponentSystem {
public:
  using systems_type        = ecs::SystemMap<typename Components::system_type...>;
  using entity_manager_type = SceneGraph<Entity>;

  template<typename Component>
  auto system() -> Component::system_type& {
    return systems.template get<typename Component::system_type>();
  }

  // *** Entity management ***
  [[nodiscard]] Entity newEntity() {
    auto id = scene_graph.createNode();
    systems.newComponents(id);
    return entity(id);
  }

  void destroyNode(Entity const entity) {
    scene_graph.destroyNode(entity.id());
    systems.removeComponents(entity.id());
  }

  Entity newChild(Entity const parent) {
    auto id = scene_graph.createChildNode(parent.id());
    systems.newComponents(id);
    return entity(id);
  }

  auto children(Entity const entity) {
    return scene_graph.getChildren(entity) | std::views::transform([this](id_t const entity_id) { // clang-format off
             return Entity {*this, entity_id};
    }); // clang-format on
  }

  std::optional<Entity> parent(Entity const entity) { }

  Entity changeParent(Entity const entity, Entity const newParent) { }

  template<typename Component>
  Entity entity(Component const component) {
    return {*this, component.entityId()};
  }

private:
  Entity entity(id_t const id) { return {*this, id}; }

  entity_manager_type scene_graph;
  systems_type systems;
};

// /************************************************
//  * Rflect3d entity component system definition  *
//  ************************************************/
template<typename Entity> //
using Ecs = EntityComponentSystem< //
    Entity, //
    ecs::Metadata, //
    ecs::Transform //
    >;

} // namespace rflect3d
