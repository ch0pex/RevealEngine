/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file profiler.hpp
 * @version 1.0
 * @date 04/11/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "IMGUI/imgui.h"
#include "common/timer.hpp"

#include <fmt/core.h>
#include <fmt/printf.h>
#include <string>

namespace reveal3d::ui::profiler {

inline void draw(const Timer& timer) {
  ImGui::Begin("Statistics");
  ImGui::Text("FPS: %u", timer.averageFps());
  ImGui::Text("Frametime: %.2f ms", timer.frameTime() * 1000.0F);
  ImGui::Text("Deltatime: %.2f ms", timer.deltaTime() * 1000.0F);
  ImGui::End();
}

} // namespace reveal3d::ui::profiler
