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
#include  "../utils.hpp"
#include "content/formats/obj/obj_parser.hpp"
#include <iomanip>


namespace reveal3d::ui {

using namespace core;

EntityProperties::EntityProperties() {}

void EntityProperties::draw(u32 entity_id) {
    ImGui::Begin("Entity Properties");

    if (id::isValid(entity_id)) {
        entity_ = core::scene.getEntity(entity_id);

        if (ImGui::BeginCombo("##addcomp", "Add component")) {
            if (!entity_.component<Geometry>().isAlive() && ImGui::Selectable("Geometry")) {
                const std::string file {utl::open_file_dialog() };
                entity_.addComponent<Geometry>(content::import_obj(file));
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

void EntityProperties::drawMetadata() {
    auto metadata = entity_.component<Metadata>().data();

    if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent(10.0F);
        if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("name", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Name:");
                ImGui::TableNextColumn();
                ImGui::InputText("##name", metadata.name.data(), 15);
            }

            ImGui::EndTable();
        }

        if (ImGui::CollapsingHeader("More info")) {
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                std::ostringstream id;
                ImGui::Text("Entity ID: ");
                id << "0x" << std::hex << std::setfill('0') << std::setw(8) << entity_.id();
                ImGui::SameLine();
                ImGui::Text("%s", id.str().data());
            }
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Date:");
                ImGui::SameLine();
                ImGui::InputText("##date", metadata.date.data(), 15);
            }

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Comment:");
                ImGui::TableNextColumn();
                ImGui::InputTextMultiline("##comment", metadata.comment.data(), 1024);
                ImGui::TableNextColumn();
            }
        }
        ImGui::Unindent(10.0f);
    }

}

void EntityProperties::drawTransform() {
    if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent(10.0f);
        if (ImGui::CollapsingHeader("Local", ImGuiTreeNodeFlags_DefaultOpen)) {
            utl::draw_transform(entity_.component<Transform>());
        }
        if (ImGui::CollapsingHeader("World")) {
            utl::draw_transform(entity_.component<Transform>(), true);
        }
        ImGui::Unindent(10.0f);
    }
}

void EntityProperties::drawGeometry() {
    auto geometry = entity_.component<Geometry>().data();

    if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(-5);
        if (ImGui::Button("Remove")) {
            entity_.removeComponent<Geometry>();
        }
        ImGui::Indent();
        if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("property", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Mesh color:");
                ImGui::TableNextColumn();
                if(ImGui::ColorEdit4("##meshcolor", (f32*)&geometry.material.base_color)) {
                    entity_.component<Geometry>().diffuseColor(geometry.material.base_color);
                }
            }
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Visibility: ");
                ImGui::TableNextColumn();
                if(ImGui::Checkbox("##visibility", &geometry.sub_mesh.visible)) {
                    entity_.component<Geometry>().visibility(geometry.sub_mesh.visible);
                }
                ImGui::TableNextColumn();
            }
            ImGui::EndTable();
        }
        ImGui::Unindent();
    }
}

}
