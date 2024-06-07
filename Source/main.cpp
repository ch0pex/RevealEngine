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
    core::Entity human = core::scene.AddEntityFromObj(L"D:/Universidad/tfm/RevealEngine/Assets/human.obj");
//    core::Entity human2 = core::scene.AddEntityFromObj(L"D:/Universidad/tfm/RevealEngine/Assets/human.obj");
//    human2.SetPosition(3.0f, 0.0f, 0.0f);

    for (u32 i = 1; i < 3; ++i) {
        for (u32 j = 0; j < 3; ++j) {
            for (u32 k = 0; k < 3; ++k) {
                core::EntityInfo info = {
                        core::Transform({i * 1.5f, j * 1.5f, 1.5f * k}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}),
                        human.GetGeometry()};
                core::Entity entity = core::scene.AddEntity(info);
                entity.AddScript<HumanScript>();

            }
        }
    }

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
            core::scene.Update(viewport.timer.DeltaTime());
            viewport.renderer.Update();
            viewport.window.Update();
            editor.Draw();
            viewport.window.ClipMouse(viewport.renderer);
            viewport.renderer.Render();
        }
        viewport.renderer.Destroy();
    } catch(std::exception &e) {
        viewport.renderer.Destroy();
        log(logERROR) << e.what();
    }
}
