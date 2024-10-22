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
#include "core/components/transform.hpp"

namespace reveal3d::ui::utl {

bool draw_vec3(std::string label, math::xvec3 &values, f32 reset_value = 0.0f, f32 column_width = 100.0,
               f32 rate = 0.1f, f32 min = 0.0f);
void draw_transform(core::Transform transform, bool world = false);
void set_style();
std::string open_file_dialog();

}

