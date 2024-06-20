/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file main.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */


#include "Editor/editor.hpp"
#include "Samples/common/scripts.hpp"
#include "core/entity.hpp"
#include "core/scene.hpp"
#include "render/viewport.hpp"


using namespace reveal3d;
using namespace reveal3d::graphics;

LogLevel loglevel = logDEBUG;

i32 main() {

    ui::Editor editor;
    window::InitInfo windowInitInfo(L"Reveal3d", 1920, 1080);
    render::Viewport<dx::Graphics, window::Win32> viewport(windowInitInfo);
    core::Entity human = core::scene.AddEntityFromObj(L"C:\\Alvaro\\Universidad\\tfm\\Assets\\human.obj");

    auto geos = core::scene.Geometries();
    core::scene.Init();
    viewport.window.Create(viewport.renderer);
    viewport.renderer.Init(viewport.window.GetHandle());
    editor.Init(viewport.window.GetHandle(), viewport.renderer.Graphics());

    viewport.window.Show();
    log(logDEBUG) << "Initialized";

    try {
        viewport.timer.Reset();
        while(!viewport.window.ShouldClose()) {
            viewport.timer.Tick();
            viewport.window.Update();
            core::scene.Update(viewport.timer.DeltaTime());
            editor.Draw();
            viewport.renderer.Update();
            viewport.window.ClipMouse(viewport.renderer);
            viewport.renderer.Render();
        }
        viewport.renderer.Destroy();
    } catch(std::exception &e) {
        viewport.renderer.Destroy();
        log(logERROR) << e.what();
    }
}
