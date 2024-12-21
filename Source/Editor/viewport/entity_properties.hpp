/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file EnityProperties.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include <fmt/printf.h>
#include "../utils/components.hpp"
#include "content/formats/obj/obj_parser.hpp"
#include "core/components/geometry.hpp"
#include "core/components/light.hpp"
#include "core/components/metadata.hpp"
#include "core/components/rigidbody.hpp"
#include "core/components/script.hpp"
#include "core/components/transform.hpp"
#include "entity_properties.hpp"

namespace reveal3d::ui::entity_properties {

namespace detail {

template<class T>
void addComponent(core::Entity entity, char const* name) {
  if (!entity.component<T>().isAlive() && ImGui::Selectable(name)) {
    entity.addComponent<T>();
  }
}

template<>
inline void addComponent<core::Geometry>(core::Entity entity, char const* name) {
  if (!entity.component<core::Geometry>().isAlive() && ImGui::Selectable(name)) {
    if (auto const file {utl::open_file_dialog()}; file.has_value()) {
      if (auto mesh = content::import_obj(file.value()); mesh.has_value())
        entity.addComponent<core::Geometry>(std::move(mesh.value()));
    }
  }
}

template<core::component T>
void drawComponent(core::Entity entity) { }

template<>
inline void drawComponent<core::Metadata>(core::Entity const entity) {
  auto const metadata = entity.component<core::Metadata>();

  if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0F);
    if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("name", 0, 0.23F);
      ImGui::TableSetupColumn("set", 0, 0.77F);

      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Name:");
        ImGui::TableNextColumn();
        ImGui::InputText("##name", metadata.name().data(), 15);
      }

      ImGui::EndTable();
    }

    if (ImGui::CollapsingHeader("More info")) {
      ImGui::TableNextColumn();
      {
        std::string const id = fmt::sprintf("0x%08X", entity.id());
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Entity ID: ");
        ImGui::SameLine();
        ImGui::Text(id.c_str());
      }
      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Date:");
        ImGui::SameLine();
        ImGui::InputText("##date", metadata.date().data(), 15);
      }

      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Comment:");
        ImGui::TableNextColumn();
        ImGui::InputTextMultiline("##comment", metadata.comment().data(), 1024);
        ImGui::TableNextColumn();
      }
    }
    ImGui::Unindent(10.0F);
  }
}

template<>
inline void drawComponent<core::Transform>(core::Entity const entity) {
  if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0F);
    if (ImGui::CollapsingHeader("Local", ImGuiTreeNodeFlags_DefaultOpen)) {
      utl::draw_transform(entity.component<core::Transform>());
    }
    if (ImGui::CollapsingHeader("world")) {
      utl::draw_transform(entity.component<core::Transform>(), true);
    }
    ImGui::Unindent(10.0F);
  }
}

template<>
inline void drawComponent<core::Geometry>(core::Entity entity) {
  auto const geometry = entity.component<core::Geometry>();

  if (not entity.component<core::Geometry>().isAlive()) {
    return;
  }

  if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::PushItemWidth(-5);
    ImGui::Indent();
    if (ImGui::Button("Remove")) {
      entity.removeComponent<core::Geometry>();
    }

    if (ImGui::CollapsingHeader("Surface", ImGuiTreeNodeFlags_DefaultOpen)) {
      if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("property", 0, 0.23f);
        ImGui::TableSetupColumn("set", 0, 0.77f);

        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Base color");
          ImGui::TableNextColumn();
          if (ImGui::ColorEdit4("##basecolor", std::bit_cast<f32*>(&geometry.material().base_color))) {
            entity.component<core::Geometry>().diffuseColor(geometry.material().base_color);
          }
        }
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Roughness");
          ImGui::TableNextColumn();
          if (ImGui::DragFloat("##roughness", std::bit_cast<f32*>(&geometry.material().roughness), 0.01f, 0.0f, 1.0f)) {
            entity.component<core::Geometry>().roughness(geometry.material().roughness);
          }
        }
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Fresnel");
          ImGui::TableNextColumn();
          if (ImGui::DragFloat3("##fresnel", std::bit_cast<f32*>(&geometry.material().fresnel), 0.01f, 0.0f, 1.0f)) {
            entity.component<core::Geometry>().fresnel(geometry.material().fresnel);
          }
        }
        ImGui::EndTable();
      }
    }

    if (ImGui::CollapsingHeader("Visibility", ImGuiTreeNodeFlags_DefaultOpen)) {
      if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("property", 0, 0.23f);
        ImGui::TableSetupColumn("set", 0, 0.77f);
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Is visible: ");
          ImGui::TableNextColumn();
          if (ImGui::Checkbox("##visibility", &geometry.subMeshes()[0].visible)) {
            entity.component<core::Geometry>().visibility(geometry.subMeshes()[0].visible);
          }
          ImGui::TableNextColumn();
        }
        ImGui::EndTable();
      }
    }
    ImGui::Unindent();
  }
}

} // namespace detail

inline void draw(core::Entity const entity_id) {
  ImGui::Begin("Entity");

  if (entity_id.isAlive()) {
    // List of components that can be added
    if (ImGui::BeginCombo("##addcomp", "Add component")) {
      detail::addComponent<core::Geometry>(entity_id, "Geometry");
      detail::addComponent<core::Light>(entity_id, "Light");
      detail::addComponent<core::Rigidbody>(entity_id, "Rigidbody");
      detail::addComponent<core::Script>(entity_id, "Script");
      ImGui::EndCombo();
    }
    // Drawing components properties of this entity
    detail::drawComponent<core::Metadata>(entity_id);
    detail::drawComponent<core::Transform>(entity_id);
    detail::drawComponent<core::Geometry>(entity_id);
    detail::drawComponent<core::Light>(entity_id);
    detail::drawComponent<core::Rigidbody>(entity_id);
    detail::drawComponent<core::Script>(entity_id);
  }

  ImGui::End();
}

} // namespace reveal3d::ui::entity_properties
