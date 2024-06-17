/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file utils.hpp
 * @version 1.0
 * @date 06/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "math/math.hpp"
#include "core/transform.hpp"

namespace reveal3d::ui {

bool DrawVec3(std::string label, math::xvec3& values, f32 resetValue = 0.0f, f32 columnWidth = 100.0, f32 rate = 0.1f, f32 min = 0.0f);
void DrawTransform(core::Transform& transform);
void SetStyle();
std::wstring OpenFileDialog();

}

