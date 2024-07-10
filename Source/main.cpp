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
#include "render/viewport.hpp"


using namespace reveal3d;

LogLevel loglevel = logDEBUG;

i32 main() {

    window::InitInfo windowInitInfo(L"Reveal3d", 1920, 1080);
    render::Viewport<graphics::Dx12, window::Win32> viewport(windowInitInfo);
    ui::Editor<graphics::Dx12, window::Win32> editor(viewport);
    core::Entity entity(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
    core::Entity entity2(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
    core::Entity entity3(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
    core::Entity entity4(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");

    core::scene.AddEntity(entity);
    core::scene.AddEntity(entity2);
    core::scene.AddEntity(entity3);
    core::scene.AddChild(entity4, entity3);


    auto geos = core::scene.Geometries(); // Just for debugging porpoises
    core::scene.Init();
    viewport.window.Create(viewport.renderer);
    viewport.renderer.Init(viewport.window.GetHandle());
    editor.Init(viewport.window.GetHandle(), viewport.renderer.Graphics());

    viewport.window.Show();
    log(logDEBUG) << "Initialized";

    viewport.timer.Reset();
    while(!viewport.window.ShouldClose()) {
        viewport.timer.Tick();
        viewport.window.Update();
        viewport.window.ClipMouse(viewport.renderer);
        core::scene.Update(viewport.timer.DeltaTime());
        viewport.renderer.Update();
        editor.Draw();
        viewport.renderer.Render();
    }
    viewport.renderer.Destroy();
}
