/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file data_types.hpp
 * @version 1.0
 * @date 7/1/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include <rflect/containers/dual_vector.hpp>

namespace rflect3d::ecs {

template<rflect::has_proxy T>
using container_type = rflect::dual_vector<T, rflect::layout::soa>;

template<rflect::has_proxy T>
using proxy_component = typename T::template proxy_type<container_type<T>>;

} // namespace rflect3d::ecs
