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
    auto const id = insert();
    Node& child   = nodes[id];
    Node& parent  = nodes[parent_id];

    child.parent = parent_id;
    parent.children.insert(child.id);

    return child.id;
  }
  void eraseChildren(id_t const parent) {
    if (not nodes.contains(parent)) {
      throw SceneGraphException {"Node does not exist, cannot be removed"};
    }
    // Remove child
    for (Node& curr_node = nodes[parent]; auto const child: std::exchange(curr_node.children, {})) {
      erase(child);
    }
  }

  void erase(id_t const id) {
    eraseChildren(id);

    // Remove from parent list
    if (auto const& curr_node = nodes[id]; curr_node.parent != id::invalid) {
      nodes[curr_node.parent].children.erase(id);
    }

    // Remove node and id
    id_factory.remove(id);
    nodes.erase(id);
  }

  [[nodiscard]] Node const& node(id_t const id) const { return nodes.at(id); }

  [[nodiscard]] u32 size() const { return nodes.size(); }

  [[nodiscard]] bool empty() const { return nodes.empty(); }

  [[nodiscard]] bool contains(id_t const id) const { return nodes.contains(id); }

private:
  id::Factory<id_t, u32> id_factory;
  std::flat_map<id_t, Node> nodes {};
};

} // namespace rflect3d
