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
        math::vec3 color = {0.0f, 0.0f,0.0f};
        bool isVisible = entity_.IsVisible();
        char * name = entity_.GetName().data();

        ImGui::NewLine();
        ImGui::InputText("##EntityName", name, 15);
        ImGui::NewLine();
        ImGui::Separator();
        ImGui::Text("Tranform");
        ImGui::NewLine();

//        ImGui::AlignTextToFramePadding();
//        ImGui::Text("##Translation");



        DrawTransform(entity_.GetTransform());


    }
    ImGui::End();
}

}
