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


using namespace reveal3d;

LogLevel loglevel = logDEBUG;

i32 main() {

    Project project("C:\\Alvaro\\Universidad\\tfm");
    window::InitInfo windowInitInfo(L"Reveal3d", 1920, 1080);
    ui::Editor<graphics::Dx12, window::Win32> editor(project, windowInitInfo);

//    core::Entity entity(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
//    core::Entity entity2(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
//    core::Entity entity3(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
//    core::Entity entity4(L"C:\\Alvaro\\Universidad\\RevealEngine\\Assets\\human.obj");
//
//    core::scene.AddEntity(entity);
//    core::scene.AddEntity(entity2);
//    core::scene.AddEntity(entity3);
//    core::scene.AddChild(entity4, entity3);

    editor.Init();
    editor.Run();
    editor.Terminate();
}
