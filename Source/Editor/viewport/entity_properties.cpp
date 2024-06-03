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

namespace reveal3d::ui {

EntityProperties::EntityProperties() {}

void EntityProperties::Draw(u32 entityId) {
    ImGui::Begin("Entity Properties");
    if (entityId != UINT_MAX) {
        entity_ = core::scene.GetEntity(entityId);
        char * name = entity_.GetName().data();
        ImGui::InputText("##EntityName", name, 15);
        ImGui::Separator();
        ImGui::Text("Tranform");
        math::xvec3 pos = entity_.GetTransform().Position();
        math::xvec3 scale = entity_.GetTransform().Scale();
        math::xvec3 rot = entity_.GetTransform().Rotation();
//        ImGui::Text("Position");
//        ImGui::SameLine();
        ImGui::DragFloat3("Position", (f32*)&pos, 0.01f);
        entity_.SetPosition(pos);
//        ImGui::Text("Rotation");
//        ImGui::SameLine();
        if (ImGui::DragFloat3("Rotation", (f32*)&rot, 1.0f))
            entity_.SetRotation(rot);
//        ImGui::Text("Scale   ");
//        ImGui::SameLine();
        if (ImGui::DragFloat3("Scale", (f32*)&scale, 0.01f))
            entity_.SetScale(scale);
    }
    ImGui::End();
}

}
