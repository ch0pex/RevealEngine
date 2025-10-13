/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file component.hpp
 * @version 1.0
 * @date 15/12/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/core/core.hpp"
#include "engine/scene/systems/core/data_types.hpp"

#include <rflect/containers/proxy.hpp>

#define DEFINE_COMPONENT_PROXY_METHODS(...)                                                                            \
  using Component<System>::Component;                                                                                  \
  using Component<System>::operator=;                                                                                  \
  FOR_EACH(EXPAND_PROXY_METHOD, __VA_ARGS__)

// using rflect::Component<name, Container>::operator=;

#define DEFINE_COMPONENT_PROXY(...)                                                                                    \
  DEFINE_PROXY(__VA_ARGS__);                                                                                           \
  template<typename System>                                                                                            \
  struct ProxyComponent : Component<System> {                                                                          \
    DEFINE_COMPONENT_PROXY_METHODS(__VA_ARGS__)                                                                        \
  }

namespace rflect3d::ecs {

/**
 * Base Component template class
 *
 * @tparam System System type were component is stored
 *
 * @note benchmark to store the proxy_type instead of index,
 * having a bigger class but less indirection maybe is better
 */
template<typename System>
class Component {
public:
  // *** Type traits ***
  using system_type = System;
  using data_type   = system_type::data_type;
  using proxy_type  = proxy_data<data_type>;

  // *** Constructors ***

  Component(system_type& system, index_t const index) : index(index), system(&system) { }

  constexpr explicit Component(Component const& other) = default;

  constexpr explicit Component(Component&& other) = default;

  constexpr ~Component() = default;

  // *** Operators ***

  constexpr proxy_type& operator=(data_type const& value) {
    data() = value;
    return static_cast<proxy_type&>(*this);
  }

  // constexpr proxy_type& operator=(Component const& value) {
  //   if (this != &value) {
  //     data() = *static_cast<proxy_type const&>(value);
  //   }
  //   return static_cast<proxy_type&>(*this);
  // }

  // constexpr auto operator*(this Self&& self) {
  // template<typename Self>
  //   return self.container_.at(self.index);
  // }

  // *** Member functions ***
  [[nodiscard]] id_t entityId() const { return system->entityId(index); }

protected:
  template<char const* name, typename Self>
  constexpr auto member(this Self&& self) -> decltype(auto) {
    return (self.data().[:nonstatic_data_member<data_type>(name):]);
  }

  [[nodiscard]] proxy_type data() const { return system->at(index); }

private:
  index_t index;
  system_type* system;
};

} // namespace rflect3d::ecs
