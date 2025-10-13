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
using proxy_data = typename T::template proxy_type<container_type<T>>;

template<typename Data, template<class, class> typename System>
using core_component = Data::template ProxyComponent<System<Data, std::true_type>>;

template<typename Data, template<class, class> typename System>
using optional_component = Data::template ProxyComponent<System<Data, std::true_type>>;
} // namespace rflect3d::ecs
