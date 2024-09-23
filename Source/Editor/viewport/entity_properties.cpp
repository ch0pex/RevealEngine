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

namespace reveal3d::ui {

EntityProperties::EntityProperties() {}

void EntityProperties::Draw(u32 entityId) {
    ImGui::Begin("Entity Properties");

    if (id::isValid(entityId)) {
        entity_ = core::scene.GetEntity(entityId);

        if (ImGui::BeginCombo("##addcomp", "Add component")) {
            if (!entity_.Component<core::Geometry>().IsAlive() && ImGui::Selectable("Geometry")) {
                std::wstring file = utl::OpenFileDialog();
                entity_.AddComponent<core::Geometry>(content::ImportObj(file.c_str()));
            }
            ImGui::EndCombo();
        }
        DrawMetadata();
        ImGui::Separator();
        DrawTransform();
        ImGui::Separator();
        if (entity_.Component<core::Geometry>().IsAlive()) {
            DrawGeometry();
        }
    }
    ImGui::End();
}

void EntityProperties::DrawMetadata() {
    char * name = entity_.Component<core::Metadata>().Name().data();
    char * date = entity_.Component<core::Metadata>().Date().data();
    char * comment = entity_.Component<core::Metadata>().Comment().data();

    if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent(10.0f);
        if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("name", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Name");
                ImGui::TableNextColumn();
                ImGui::InputText("##name", name, 15);
            }

            ImGui::EndTable();
        }

        if (ImGui::CollapsingHeader("More Info")) {
            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Date");
                ImGui::TableNextColumn();
                ImGui::InputText("##date", date, 15);
            }

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Comment");
                ImGui::TableNextColumn();
                ImGui::InputTextMultiline("##comment", comment, 1024);
                ImGui::TableNextColumn();
            }
        }
        ImGui::Unindent(10.0f);
    }

}

void EntityProperties::DrawTransform() {
    if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Indent(10.0f);
        if (ImGui::CollapsingHeader("Local", ImGuiTreeNodeFlags_DefaultOpen)) {
            utl::DrawTransform(entity_.Component<core::Transform>());
        }
        if (ImGui::CollapsingHeader("World")) {
            utl::DrawTransform(entity_.Component<core::Transform>(), true);
        }
        ImGui::Unindent(10.0f);
    }
}

void EntityProperties::DrawGeometry() {
    math::vec4 color = entity_.Component<core::Geometry>().Material().baseColor;
    bool isVisible = entity_.Component<core::Geometry>().IsVisible();

    if (ImGui::CollapsingHeader("Shading", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushItemWidth(-5);
        if (ImGui::Button("Remove")) {
            entity_.RemoveComponent<core::Geometry>();
        }
        ImGui::Indent();
        if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp))
        {
            ImGui::TableSetupColumn("property", 0, 0.23f);
            ImGui::TableSetupColumn("set", 0, 0.77f);

            ImGui::TableNextColumn();
            {
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Mesh color");
                ImGui::TableNextColumn();
                if(ImGui::ColorEdit4("##meshcolor", (f32*)&color)) {
                    entity_.Component<core::Geometry>().SetDiffuseColor(color);
                }
                ImGui::TableNextColumn();
            }
            ImGui::EndTable();
        }
        ImGui::Unindent();
    }

}

}
