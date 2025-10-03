/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file bi_map.hpp
 * @version 1.0
 * @date 6/23/2025
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include <concepts>
#include <flat_map>

namespace rflect3d::core {

template<typename Key, typename Value>
  requires(not std::same_as<Key, Value>)
class BiMap {
public:
  template<typename Self>
  auto&& at(this Self&& self, Key const key) {
    return std::forward<Self>(self).map_1.at(key);
  }

  template<typename Self>
  auto&& at(this Self&& self, Value const val) {
    return std::forward<Self>(self).map_2.at(val);
  }

  void insert(Key const key, Value const value) {
    map_1[key]   = value;
    map_2[value] = key;
  }

  void erase(Key const key) {
    auto const value = map_1.at(key);
    map_1.erase(key);
    map_2.erase(value);
  }
  void erase(Value const value) {
    auto const key = map_2.at(value);
    map_1.erase(key);
    map_2.erase(value);
  }

private:
  std::flat_map<Key, Value> map_1 {};
  std::flat_map<Value, Key> map_2 {};
};

} // namespace rflect3d::core
