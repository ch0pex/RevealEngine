/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file profiler.hpp
 * @version 1.0
 * @date 04/11/2024
 * @brief Profiling component
 *
 * This component offeers statistics of the system such as performance or
 * geometry statistics.
 *
 */

#pragma once

#include "IMGUI/imgui.h"
#include "common/common.hpp"
#include "common/timer.hpp"

#include <fmt/core.h>
#include <fmt/printf.h>
#include <map>
#include <string>

namespace reveal3d::ui::profiler {

namespace detail {

struct PlotVarData {
  ImGuiID ID {0};
  std::vector<f32> data;
  i32 index {0};
  i32 lastFrame {-1};
};

using PlotVarsMap = std::map<ImGuiID, PlotVarData>;
static PlotVarsMap g_PlotVarsMap;

inline void plotVar(char const* label, f32 value, f32 scale_min = 0, f32 scale_max = 100, size_t buffer_size = 2024) {
  if (buffer_size == 0)
    buffer_size = 120;

  ImGui::PushID(label);
  ImGuiID const id = ImGui::GetID("");

  // Lookup O(log N)
  PlotVarData& pvd = g_PlotVarsMap[id];

  // Setup
  if (pvd.data.capacity() != buffer_size) {
    pvd.data.resize(buffer_size);
    std::memset(pvd.data.data(), 0, sizeof(float) * buffer_size);
    pvd.index     = 0;
    pvd.lastFrame = -1;
  }

  // Insert (avoid unnecessary modulo operator)
  if (pvd.index == buffer_size)
    pvd.index = 0;
  i32 const display_idx = pvd.index;
  if (value != FLT_MAX)
    pvd.data.at(pvd.index++) = value;

  f32 mean = std::accumulate(pvd.data.begin(), pvd.data.end(), 0.f) / static_cast<f32>(pvd.data.size());

  // Draw
  i32 const current_frame = ImGui::GetFrameCount();
  if (pvd.lastFrame != current_frame) {
    ImGui::Text("%s: ", label);
    ImGui::PlotLines("##plot", pvd.data.data(), buffer_size, pvd.index, NULL, scale_min, scale_max, ImVec2(0, 40));
    ImGui::SameLine();
    ImGui::Text("\n%-3.2f ms", mean);
    pvd.lastFrame = current_frame;
  }

  ImGui::PopID();
}

} // namespace detail

inline void draw(core::Scene& scene, Timer const& timer) {
  ImGui::Begin("Statistics");

  if (ImGui::CollapsingHeader("Performance")) {
    ImGui::Indent(10.0F);
    ImGui::TableNextColumn();
    ImGui::Text("FPS: %llu", timer.averageFps());
    ImGui::TableNextColumn();
    ImGui::Text("Deltatime: %.2f ms", timer.deltaTime() * 1000.0F);
    ImGui::TableNextColumn();
    detail::plotVar("Frametime", timer.frameTime() * 1000.0F);
    ImGui::Unindent(10.0F);
  }

  if (ImGui::CollapsingHeader("Geometry")) {
    ImGui::Indent(10.0F);
    ImGui::TableNextColumn();
    ImGui::Text("Geometries: %u", scene.pool<core::Geometry>().count());
    ImGui::TableNextColumn();
    ImGui::Text("Triangles: %llu", scene.pool<core::Geometry>().vertices());
    ImGui::TableNextColumn();
    ImGui::Text("Vertices: %llu", scene.pool<core::Geometry>().triangles());
    ImGui::Unindent(10.0F);
  }

  ImGui::End();
}

} // namespace reveal3d::ui::profiler
