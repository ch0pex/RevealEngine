/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file geometry_proxy.hpp
 * @version 1.0
 * @date 01/07/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/scene/components/component.hpp"
#include "engine/scene/systems/geometry/geometry_system.hpp"

namespace rflect3d::ecs {

// enum GeometryPrimitive : u8 { Cube = 0U, Plane, Cylinder, Sphere, Cone, Torus, Custom, count };
//
// struct Geometry : Component<systems::Geometry> {
//
//   using Component<systems::Geometry>::Component;
//   using Primitive = GeometryPrimitive;
//
//   [[nodiscard]] u32 triangles() const { return pool().mesh(id_).triangle_count; }
//
//   [[nodiscard]] u32 vertexCount() const { return pool().mesh(id_).vertex_count; }
//
//   [[nodiscard]] u32 indexCount() const { return pool().mesh(id_).indices.size(); }
//
//   [[nodiscard]] std::span<render::SubMesh> subMeshes() const { return pool().subMeshes(id_); }
//
//   [[nodiscard]] std::span<render::Vertex> vertices() const { return pool().mesh(id_).vertices; }
//
//   [[nodiscard]] std::span<u32> indices() const { return pool().mesh(id_).indices; }
//
//   [[nodiscard]] bool isVisible() const { return pool().subMeshes(id_)[0].visible; }
//
//   [[nodiscard]] render::Material const& material() const { return pool().material(id_); }
//
//   void visibility(bool const visibility) const { pool().subMeshes(id_)[0].visible = visibility; }
//
//   void diffuseColor(math::vec4 const color) const {
//
//     pool().material(id_).base_color = color;
//     setDirty();
//   }
//
//   void fresnel(math::vec3 const fresnel) const {
//     pool().material(id_).fresnel = fresnel;
//     setDirty();
//   }
//
//   void materialTransform(math::mat4 const& transform) const {
//     pool().material(id_).transform = transform;
//     setDirty();
//   }
//
//   void roughness(f32 const roughness) const {
//     pool().material(id_).roughness = roughness;
//     setDirty();
//   }
// };

} // namespace rflect3d::ecs
