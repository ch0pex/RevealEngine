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

namespace reveal3d::ui {

EntityProperties::EntityProperties() {}

void EntityProperties::Draw(u32 entityId) {
    ImGui::Begin("Entity Properties");
    if (entityId != UINT_MAX) {
        entity_ = core::scene.GetEntity(entityId);
        math::vec4 &color = entity_.GetGeometry().Color();
        bool isVisible = entity_.IsVisible();
        char * name = entity_.GetName().data();

        if (ImGui::CollapsingHeader("Naming", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Indent();
            if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp))
            {
                ImGui::TableSetupColumn("name", 0, 0.23f);
                ImGui::TableSetupColumn("set", 0, 0.77f);

                ImGui::TableNextColumn();
                {
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text("Name");
                    ImGui::TableNextColumn();
                    ImGui::InputText("##name", name, 15);
                    ImGui::TableNextColumn();
                }
                ImGui::EndTable();
            }
            ImGui::Unindent();
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Tranform", ImGuiTreeNodeFlags_DefaultOpen))
            DrawTransform(entity_.GetTransform());

        ImGui::Separator();

        if (ImGui::CollapsingHeader("Shading", ImGuiTreeNodeFlags_DefaultOpen))
        {
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
                    ImGui::ColorEdit4("##meshcolor", (f32*)&color);
                    ImGui::TableNextColumn();
                }
                ImGui::EndTable();
            }
            ImGui::Unindent();
        }
    }
    ImGui::End();
}

}
