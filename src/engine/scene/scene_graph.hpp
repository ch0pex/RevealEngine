/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file scene_graph.hpp
 * @version 1.0
 * @date 14/02/2025
 * @brief Scene graph class
 *
 */

#pragma once

#include <flat_map>

namespace rflect3d {


template<typename Entity>
class SceneGraph {
public:
  struct Node {
    id_t entity {id::invalid};
    id_t parent {id::invalid};
    std::vector<id_t> children {};
  };

  id_t createNode() {
    id_t const id = id_factory.create();
    nodes[id]     = Node {id};
    return id;
  }

  id_t createChildNode(id_t const parent) {
    id_t const id = createNode();
    at(id).entity = parent;
    at(parent).children.push_back(id);
    return id;
  }

  void destroyNode(id_t const id) {
    for (auto& child: at(id).children) {
      destroyNode(child);
    }
    id_factory.remove(id);
    nodes.erase(id);
  }

  template<typename Self>
  auto at(this Self&& self, id_t const id) -> Node& {
    return std::forward<Self>(self).nodes.at(id::index(id));
  }

  auto begin() { return nodes.begin(); }

  auto end() { return nodes.end(); }

  auto begin() const { return nodes.begin(); }

  auto end() const { return nodes.end(); }

  u32 count() const { return nodes.size(); }

  // u32 size() const { return nodes.size(); }

  bool empty() const { return nodes.empty(); }

  bool contains(id_t const id) const { return true; } // TODO

  // auto freeNodes() const { return free_ids.size(); }

private:
  id::Factory<id_t, u32> id_factory;
  std::flat_map<id_t, Node> nodes {};
};

} // namespace rflect3d
