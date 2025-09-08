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
#include <set>

namespace rflect3d {
struct SceneGraphException final : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class SceneGraph {
public:
  struct Node {
    id_t id {id::invalid};
    id_t parent {id::invalid};
    std::set<id_t> children {};
  };

  SceneGraph() = default;

  id_t insert() {
    id_t const id = id_factory.create();
    nodes[id]     = Node {id};
    return id;
  }

  id_t insertChild(id_t const parent_id) {

    if (not nodes.contains(parent_id)) {
      throw SceneGraphException {"Parent node specified don't exist"};
    }
    Node& child  = node(insert());
    Node& parent = node(parent_id);

    child.parent = parent_id;
    parent.children.insert(child.id);

    return child.id;
  }

  void erase(id_t const id) {
    if (not nodes.contains(id)) {
      throw SceneGraphException {"Node does not exist, cannot be removed"};
    }
    // Remove child
    Node& curr_node = node(id);
    for (auto const child: std::exchange(curr_node.children, {})) {
      erase(child);
    }

    // Remove from parent list
    if (curr_node.parent != id::invalid) {
      node(curr_node.parent).children.erase(id);
    }

    // Remove node and id
    id_factory.remove(id);
    nodes.erase(id);
  }

  template<typename Self>
  auto node(this Self&& self, id_t const id) -> Node& {
    return std::forward<Self>(self).nodes.at(id);
  }

  // auto begin() { return nodes.begin(); }
  //
  // auto end() { return nodes.end(); }
  //
  // auto begin() const { return nodes.begin(); }
  //
  // auto end() const { return nodes.end(); }

  u32 size() const { return nodes.size(); }

  bool empty() const { return nodes.empty(); }

  bool contains(id_t const id) const { return nodes.contains(id); }

private:
  id::Factory<id_t, u32> id_factory;
  std::flat_map<id_t, Node> nodes {};
};

} // namespace rflect3d
