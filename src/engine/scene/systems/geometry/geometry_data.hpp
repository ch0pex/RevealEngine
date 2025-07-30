/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file geometry_data.hpp
 * @version 1.0
 * @date 01/07/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/core/core.hpp"
#include "engine/render/material.hpp"
#include "engine/render/mesh.hpp"
#include "rflect/containers/proxy.hpp"

namespace rflect3d::ecs::data {

struct Geometry {

  DEFINE_PROXY(material, sub_mesh, mesh);

  render::Material material {};
  render::SubMesh sub_mesh {};
  render::Mesh mesh {};
};

} // namespace rflect3d::ecs::data
