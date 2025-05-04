/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file table_components.hpp
 * @version 1.0
 * @date 3/16/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include "imgui.hpp"

namespace reveal3d::ui::utl::table {

struct DragProperties {
  f32 step {1.F};
  f32 min {0.F};
  f32 max {0.F};
  f32 resetValue {0.F};
};

template<typename... Args>
void element(char const* name, auto value, auto setter, auto imgui_component, Args... args) {
  ImGui::TableNextColumn();
  ImGui::AlignTextToFramePadding();
  ImGui::Text("%s", name);
  ImGui::TableNextColumn();
  if (imgui_component(name, value, args...)) {
    setter(value);
  }
}

constexpr auto reset_button = [](char const* id, auto& val, ImVec4 const color, f32 const reset_val) {
  ImGui::PushStyleColor(ImGuiCol_Button, color);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {color.x + 0.1F, color.y + 0.1F, color.z + 0.1F, 1.0F});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
  bool clicked = ImGui::Button(id, {5.0F, 15.0F});
  if (clicked) {
    val = reset_val;
  }
  ImGui::PopStyleColor(3);
  return clicked;
};

void drag_float(char const* name, auto getter, auto setter, DragProperties const thresholds = {}) {
  auto drag_float = [](char const* n, auto& val, f32 const s = 1.F, f32 const mn = 0, f32 const mx = 0) {
    return ImGui::DragFloat(fmt::format("##{}", n).c_str(), &val, s, mn, mx);
  };
  element(name, getter, setter, drag_float, thresholds.step, thresholds.min, thresholds.max);
}

void drag_float3(char const* name, math::vec3 value, auto setter, DragProperties const thresholds = {}) {
  auto drag_float = [](char const* n, auto& val, f32 const s = 1.F, f32 const mn = 0, f32 const mx = 0) {
    return ImGui::DragFloat3(fmt::format("##{}", n).c_str(), std::bit_cast<f32*>(&val), s, mn, mx);
  };
  element(name, value, setter, drag_float, thresholds.step, thresholds.min, thresholds.max);
}

void color_edit4(char const* name, math::vec4 value, auto setter) {
  auto color_edit = [](char const* n, auto& val) {
    return ImGui::ColorEdit4(fmt::format("##{}", n).c_str(), std::bit_cast<f32*>(&val));
  };
  element(name, value, setter, color_edit);
}

void draw_vec3(
    char const* label, math::vec3 value, auto setter, math::vec3 const reset_vec = {},
    DragProperties const properties = {}
) {
  auto vec3_component = [setter, reset_vec](char const* name, auto& val, DragProperties const prop) {
    bool changes = false;
    ImGui::PushID(name);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {0, 0});
    f32 const avail_width = (ImGui::GetContentRegionAvail().x / 3.0F) - 9.0F;

    changes |= reset_button("###X", val.x, ImVec4 {0.8F, 0.1F, 0.15F, 1.0F}, prop.resetValue);
    ImGui::SameLine();
    ImGui::PushItemWidth(avail_width);
    changes |= ImGui::DragFloat("##X", &val.x, prop.step, prop.min);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    changes |= reset_button("Y", val.y, ImVec4 {0.2F, 0.7F, 0.2F, 1.0F}, prop.resetValue);
    ImGui::SameLine();
    ImGui::PushItemWidth(avail_width);
    changes |= ImGui::DragFloat("##Y", &val.y, prop.step, prop.min);
    ImGui::PopItemWidth();
    ImGui::SameLine();

    changes |= reset_button("Z", val.z, ImVec4 {0.1F, 0.25F, 0.8F, 1.0F}, prop.resetValue);
    ImGui::SameLine();
    ImGui::PushItemWidth(avail_width);
    changes |= ImGui::DragFloat("##Z", &val.z, prop.step, prop.min);
    ImGui::PopItemWidth();

    ImGui::PopStyleVar();
    ImGui::PopID();

    // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
    // if (ImGui::Button(std::format("reset##{}", name).c_str()))
    //   setter(reset_vec);
    // ImGui::PopStyleColor();
    //
    return changes;
  };
  element(label, value, setter, vec3_component, properties);
}

} // namespace reveal3d::ui::utl::table
