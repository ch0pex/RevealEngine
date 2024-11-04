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

#include "core/components/transform.hpp"
#include "math/math.hpp"

namespace reveal3d::ui::utl {

bool draw_vec3(
    std::string_view label, math::xvec3& values, f32 reset_value = 0.0F, f32 column_width = 100.0, f32 rate = 0.1F,
    f32 min = 0.0F
);
void draw_transform(core::Transform transform, bool world = false);
void set_style();
std::string open_file_dialog();

} // namespace reveal3d::ui::utl
