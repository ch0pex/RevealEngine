/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file EnityProperties.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "IMGUI/imgui.h"
#include "IMGUI/backends/imgui_impl_win32.h"
#include "IMGUI/backends/imgui_impl_dx12.h"

#include "core/scene.hpp"

namespace reveal3d::ui {

class EntityProperties {
public:
    EntityProperties();
    void draw(u32 entity_id);

private:

    void drawMetadata();
    void drawTransform();
    void drawGeometry();

    core::Entity entity_;
};

}

