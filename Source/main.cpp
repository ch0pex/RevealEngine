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
#include "Engine/engine_cfg.hpp"
#include "content/content.hpp"

using namespace reveal3d;
using namespace reveal3d::core;

void add_entities(u32 const num) {
  auto const human = content::import_obj(R"(D:\Universidad\tfg\RevealEngine\Assets\models\human.obj)").value();
  for (u32 i = 0; i < num; ++i) {
    for (u32 j = 0; j < num; ++j) {
      for (u32 k = 0; k < num; ++k) {
        auto human_copy = human;
        Entity entity   = scene.newEntity();
        entity.addComponent<Geometry>(std::move(human_copy));
        entity.component<Transform>().position(
            {static_cast<f32>(i * 3), static_cast<f32>(j * 3), static_cast<f32>(k * 3)}
        );
      }
    }
  }
}

void add_child() {
  Entity const entity = scene.newEntity();
  entity.addChild();
  entity.addChild();
  entity.addChild();
}

i32 main(i32 const argc, char* argv[]) {

  auto const args = std::span(argv, argc);
  auto engine     = init_from_config<graphics::Dx12, window::Win32>(args);

  engine.run();
}
