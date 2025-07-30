/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file primitives.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/scene/components/geometry.hpp"
#include "engine/scene/systems/geometry/geometry_data.hpp"

namespace rflect3d::content {


template<ecs::Geometry::Primitive primitive>
ecs::data::Geometry import_primitive();

template<>
inline ecs::data::Geometry import_primitive<ecs::Geometry::Cube>() {
  ecs::data::Geometry geometry {};

  std::vector<render::Vertex> v {
    {{-1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, 0.0F, 0.0F}}, // 0
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F, 0.0F}}, // 1
    {{1.0F, 1.0F, -1.0F}, {1.0F, 1.0F, 0.0F, 0.0F}}, // 2
    {{1.0F, -1.0F, -1.0F}, {1.0F, 0.0F, 0.0F, 0.0F}}, // 3
    {{-1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F, 0.0F}}, // 4
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 1.0F, 0.0F}}, // 5
    {{1.0F, 1.0F, 1.0F}, {1.0F, 1.0F, 1.0F, 0.0F}}, // 6
    {{1.0F, -1.0F, 1.0F}, {1.0F, 0.0F, 1.0F, 0.0F}} // 7
  };

  std::vector<u16> ind = {0, 1, 2, 0, 2, 3, 4, 6, 5, 4, 7, 6, 4, 5, 1, 4, 1, 0,
                          3, 2, 6, 3, 6, 7, 1, 5, 6, 1, 6, 2, 4, 0, 3, 4, 3, 7};

  std::ranges::copy(v.begin(), v.end(), std::back_inserter(geometry.mesh.vertices));
  std::ranges::copy(ind.begin(), ind.end(), std::back_inserter(geometry.mesh.indices));
  return geometry;
}

template<>
inline ecs::data::Geometry import_primitive<ecs::Geometry::Plane>() {
  ecs::data::Geometry geometry {};
  std::vector<render::Vertex> v {
    {{-1.0F, -1.0F, 0.0F}, {0.2F, 0.2F, 0.2F, 0.0F}},
    {{-1.0F, 1.0F, 0.0F}, {0.2F, 0.2F, 0.2F, 0.0F}},
    {{1.0F, 1.0F, 0.0F}, {0.2F, 0.2F, 0.2F, 0.0F}},
    {{1.0F, -1.0F, 0.0F}, {0.0F, 0.0F, 1.0F, 0.0F}}
  };

  std::vector<u16> ind = {0, 1, 2, 0, 2, 3};

  std::ranges::copy(v.begin(), v.end(), std::back_inserter(geometry.mesh.vertices));
  std::ranges::copy(ind.begin(), ind.end(), std::back_inserter(geometry.mesh.indices));

  return geometry;
}

} // namespace rflect3d::content
