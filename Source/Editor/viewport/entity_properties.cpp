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
                const std::string file {utl::openFileDialog() };
                entity_.addComponent<Geometry>(content::importObj(file));
            }
            ImGui::EndCombo();
        }
        DrawMetadata();
        ImGui::Separator();
        drawTransform();
        ImGui::Separator();
        if (entity_.component<core::Geometry>().isAlive()) {
            drawGeometry();
        }
    }
    ImGui::End();
}

void EntityProperties::DrawMetadata() {
    char * name {entity_.component<core::Metadata>().name().data() };
    char * date {entity_.component<core::Metadata>().date().data() };
    char * comment {entity_.component<core::Metadata>().comment().data() };

    if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent(10.0F);
        if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("name", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("name");
                ImGui::TableNextColumn();
                ImGui::InputText("##name", name, 15);
            }

            ImGui::EndTable();
        }

        if (ImGui::CollapsingHeader("More info")) {
            ImGui::TableNextColumn();
            {
                std::ostringstream id;
                id << "Entity ID: 0x" << std::hex << std::setfill('0') << std::setw(8) << entity_.id();
                ImGui::AlignTextToFramePadding();
                ImGui::Text("%s", id.str().data());
            }
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("date:");
                ImGui::SameLine();
                ImGui::InputText("##date", date, 15);
            }

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("comment:");
                ImGui::TableNextColumn();
                ImGui::InputTextMultiline("##comment", comment, 1024);
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
            utl::drawTransform(entity_.component<core::Transform>());
        }
        if (ImGui::CollapsingHeader("World")) {
            utl::drawTransform(entity_.component<core::Transform>(), true);
        }
        ImGui::Unindent(10.0f);
    }
}

void EntityProperties::drawGeometry() {
    math::vec4 color = entity_.component<core::Geometry>().material().base_color;
    bool is_visible = entity_.component<core::Geometry>().isVisible();

    if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(-5);
        if (ImGui::Button("remove")) {
            entity_.removeComponent<core::Geometry>();
        }
        ImGui::Indent();
        if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("property", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("mesh color");
                ImGui::TableNextColumn();
                if(ImGui::ColorEdit4("##meshcolor", (f32*)&color)) {
                    entity_.component<core::Geometry>().diffuseColor(color);
                }
                ImGui::TableNextColumn();
            }
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Visibility: ");
                ImGui::TableNextColumn();
                if(ImGui::ColorEdit4("##visibility", (f32*)&is_visible)) {
                    entity_.component<core::Geometry>().visibility(is_visible);
                }
                ImGui::TableNextColumn();
            }
            ImGui::EndTable();
        }
        ImGui::Unindent();
    }
}

}
