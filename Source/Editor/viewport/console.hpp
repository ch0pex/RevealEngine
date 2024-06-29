/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file Console.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "common/logger.hpp"
#include "common/timer.hpp"

namespace reveal3d::ui {

struct Stats {
    std::string fps;
    std::string ms;
};

class Console {
public:
    Console();
    void Draw(Timer& timer);
    void RightClick(LogLevel tab);
private:
    Stats stats_;
};



}
