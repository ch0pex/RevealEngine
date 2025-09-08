/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_scene_graph.hpp
 * @version 1.0
 * @date 8/17/2025
 * @brief Short description
 *
 * Longer description
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/core/data_types/id.hpp"
#include "engine/scene/scene_graph.hpp"


DOCTEST_TEST_SUITE_BEGIN("SceneGraph");


DOCTEST_TEST_CASE("Create Node") {
  rflect3d::SceneGraph graph;

  DOCTEST_CHECK(graph.empty());

  auto node = graph.insert();
  DOCTEST_CHECK(node == rflect3d::id_t {0});
  DOCTEST_CHECK(graph.contains(node));
  DOCTEST_CHECK(graph.node(node).parent == rflect3d::id::invalid);
}

DOCTEST_TEST_CASE("Create child node") {
  rflect3d::SceneGraph graph;

  auto root_id = graph.insert();
  DOCTEST_CHECK(graph.contains(root_id));
  auto child_id = graph.insertChild(root_id);

  auto root  = graph.node(root_id);
  auto child = graph.node(child_id);

  DOCTEST_CHECK(graph.contains(child_id));
  DOCTEST_CHECK(child.parent == root_id);

  DOCTEST_SUBCASE("Remove lonely child") {
    graph.erase(child_id);
    DOCTEST_CHECK(not graph.contains(child_id));
  }

  DOCTEST_SUBCASE("Remove parent") {
    graph.erase(root_id);
    DOCTEST_CHECK(not graph.contains(child_id));
    DOCTEST_CHECK(not graph.contains(root_id));
  }

  DOCTEST_SUBCASE("Multiple children removed") {
    for (std::size_t i = 0; i < 10; ++i) {
      graph.insertChild(root_id);
    }
    auto& parent = graph.node(root_id);
    DOCTEST_CHECK_EQ(parent.children.size(), 11);
    DOCTEST_CHECK_EQ(graph.size(), 12);

    auto sibling_id = graph.insert();
    for (std::size_t i = 0; i < 5; ++i) {
      graph.insertChild(sibling_id);
    }
    auto& sibling = graph.node(sibling_id);
    DOCTEST_CHECK_EQ(sibling.children.size(), 5);
    DOCTEST_CHECK_EQ(graph.size(), 18);

    auto first_child = *sibling.children.begin();
  }
}

DOCTEST_TEST_SUITE_END();
