/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file EnityProperties.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "entity_properties.hpp"
#include <fmt/printf.h>
#include "../utils.hpp"
#include "content/formats/obj/obj_parser.hpp"
#include "core/components/geometry.hpp"
#include "core/components/metadata.hpp"
#include "core/components/script.hpp"
#include "core/components/transform.hpp"

#include <iomanip>


namespace reveal3d::ui {

using namespace core;

EntityProperties::EntityProperties() { }

void EntityProperties::draw(u32 entity_id) {
  ImGui::Begin("Entity Properties");

  if (id::is_valid(entity_id)) {
    entity_ = core::scene.getEntity(entity_id);

    if (ImGui::BeginCombo("##addcomp", "Add component")) {
      if (!entity_.component<Geometry>().isAlive() && ImGui::Selectable("Geometry")) {
        std::string const file {utl::open_file_dialog()};
        if (!file.empty()) {
          if (auto mesh = content::import_obj(file); mesh.has_value())
            entity_.addComponent<Geometry>(std::move(mesh.value()));
          else
            logger(LogError) << "Failed to load geometry from file: " << file;
        }
      }
      ImGui::EndCombo();
    }
    drawMetadata();
    ImGui::Separator();
    drawTransform();
    ImGui::Separator();
    if (entity_.component<core::Geometry>().isAlive()) {
      drawGeometry();
    }
  }
  ImGui::End();
}

void EntityProperties::drawMetadata() const {
  auto const metadata = entity_.component<Metadata>();

  if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0F);
    if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("name", 0, 0.23f);
      ImGui::TableSetupColumn("set", 0, 0.77f);

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
        std::string const id = fmt::sprintf("0x%08X", entity_.id());
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Entity ID: ");
        ImGui::SameLine();
        ImGui::Text("%s", id.c_str());
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
    ImGui::Unindent(10.0f);
  }
}

void EntityProperties::drawTransform() const {
  if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0f);
    if (ImGui::CollapsingHeader("Local", ImGuiTreeNodeFlags_DefaultOpen)) {
      utl::draw_transform(entity_.component<Transform>());
    }
    if (ImGui::CollapsingHeader("world")) {
      utl::draw_transform(entity_.component<Transform>(), true);
    }
    ImGui::Unindent(10.0f);
  }
}

void EntityProperties::drawGeometry() {
  auto geometry = entity_.component<Geometry>();

  if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::PushItemWidth(-5);
    if (ImGui::Button("Remove")) {
      entity_.removeComponent<Geometry>();
    }
    ImGui::Indent();
    if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23f);
      ImGui::TableSetupColumn("set", 0, 0.77f);

      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Mesh color:");
        ImGui::TableNextColumn();
        if (ImGui::ColorEdit4("##meshcolor", std::bit_cast<f32*>(&geometry.material().base_color))) {
          entity_.component<Geometry>().diffuseColor(geometry.material().base_color);
        }
      }
      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Visibility: ");
        ImGui::TableNextColumn();
        if (ImGui::Checkbox("##visibility", &geometry.subMeshes()[0].visible)) {
          entity_.component<Geometry>().visibility(geometry.subMeshes()[0].visible);
        }
        ImGui::TableNextColumn();
      }
      ImGui::EndTable();
    }
    ImGui::Unindent();
  }
}

} // namespace reveal3d::ui
