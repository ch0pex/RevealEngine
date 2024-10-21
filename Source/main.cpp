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
#include "content/formats/obj/obj_parser.hpp"
// #include "content/content.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

LogLevel loglevel = logDEBUG;

void AddEntities1000() {
    render::Mesh human = content::importObj("C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\models\\human.obj");
    for (u32 i = 0; i < 1'000; ++i) {
        auto human_copy = human;
        Entity entity = core::scene.newEntity();
        render::Mesh copy = human;
        entity.addComponent<Geometry>(std::move(human_copy));
        entity.component<Transform>().position({static_cast<f32>(i), 0, 0});
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
    window::Config windowInitInfo(L"Reveal3d", 1920, 1080);
    ui::Editor<graphics::Dx12, window::Win32> editor(project, windowInitInfo);

//    AddEntities1000();
//    addChild();


    editor.init();
//    editor.benchMark(30);
    editor.run();
    editor.terminate();

    return 0;
}
