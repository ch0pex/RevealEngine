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

#include "app/engine_cfg.hpp"
#include "app/run_engine.hpp"

using namespace reveal3d;
i32 main(i32 const argc, char* argv[]) {

  auto const config = engine::read_config(std::span(argv, argc));
  engine::run_from_cfg(config);
}
