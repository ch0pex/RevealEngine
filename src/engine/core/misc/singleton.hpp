/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file singleton.hpp
 * @version 1.0
 * @date 9/4/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once


namespace rflect3d {

template<typename T>
class Singleton {
  Singleton()  = default;
  ~Singleton() = default;

public:
  explicit Singleton(T const&)   = delete;
  Singleton& operator=(T const&) = delete;

  static T& instance() {
    static T instance;
    return instance;
  }
};

} // namespace rflect3d
