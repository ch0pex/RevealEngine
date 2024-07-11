/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file project.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include <string>
#include "common/platform.hpp"

namespace reveal3d {

class Project {
public:
    explicit Project(std::string&& path);
    INLINE const std::string& RootPath() { return root_path_; }
private:
    std::string root_path_;
};

}
