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
#include "content/content.hpp"
// #include "content/content.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

LogLevel loglevel = logDEBUG;

void add_entities(u32 num) {
    render::Mesh human = content::import_obj("C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\models\\human.obj");
    for (u32 i = 0; i < num; ++i) {
        for (u32 j = 0; j < num; ++j) {
            for (u32 k = 0; k < num; ++k) {
                auto human_copy = human;
                Entity entity = core::scene.newEntity();
                entity.addComponent<Geometry>(std::move(human_copy));
                entity.component<Transform>().position({static_cast<f32>(i * 3), static_cast<f32>(j * 3), static_cast<f32>(k * 3)});
            }
        }
    }
}

void AddChild() {
    core::Entity entity = core::scene.newEntity();
    entity.addChild();
    entity.addChild();
    entity.addChild();
}

i32 main() {

    Project project(R"(C:\Alvaro\Universidad\tfm)");
    window::Config window_init_info(L"Reveal3d", 1920, 1080);
    ui::Editor<graphics::Dx12, window::Win32> editor(project, window_init_info);

    add_entities(5);
    //    addChild();


    editor.init();
//    editor.benchMark(30);
    editor.run();
    editor.terminate();

    return 0;
}
