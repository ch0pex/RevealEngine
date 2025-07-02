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

#include "engine/scene/entity.hpp"

// #define EXPAND_COMPONENT_METHOD(name, ...)                                                                             \
//   auto name() const {                                                                                                  \
//     using namespace rflect;                                                                                            \
//     return this->template member<#name##_ss>();                                                                        \
//   }                                                                                                                    \
//   void name(auto const& value) const { using namespace rflect; }
//
// #define DEFINE_COMPONENT_METHODS(name, ...) \
//   using ComponentProxy<name, Container>::operator=; \
//   using ComponentProxy<name, Container>::ComponentProxy; \ FOR_EACH(EXPAND_COMPONENT_METHOD, __VA_ARGS__)
//
namespace rflect3d::ecs {
//
// template<rflect::has_proxy T>
// using proxy_base = rflect::proxy_base<T::template proxy_type, container_type<T>>;
//
// template<template<typename> class Proxy, class Container>
// struct ComponentProxy : rflect::proxy_base<Proxy, Container> {
//   using rflect::proxy_base<Proxy, Container>::operator=;
//   using rflect::proxy_base<Proxy, Container>::proxy_base;
// };
//
//
// template<template<typename> class Proxy, class DataType>
// class ProxyComponent {
// public:
//   // *** Type traits ***
//   using container_type = System<Proxy<DataType>>;
//   using proxy_type     = Proxy<container_type>;
//   using value_type     = typename container_type::value_type;
//
//   // *** Constructors ***
//   constexpr ProxyComponent(container_type& cont, index_t const index) : index_(index), system_(cont) { }
//
//   constexpr explicit ProxyComponent(ProxyComponent const& other) = default;
//
//   constexpr explicit ProxyComponent(ProxyComponent&& other) = default;
//
//   constexpr ~ProxyComponent() = default;
//
//   // *** Operators ***
//   constexpr proxy_type& operator=(ProxyComponent&& other) noexcept {
//     system_ = other.system_;
//     index_  = other.index_;
//     return static_cast<proxy_type&>(*this);
//   }
//
//   constexpr proxy_type& operator=(value_type const& value) {
//     system_.at(index_) = value;
//     return static_cast<proxy_type&>(*this);
//   }
//
//   constexpr proxy_type& operator=(ProxyComponent const& value) {
//     if (this != &value) {
//       system_.at(index_) = *static_cast<proxy_type const&>(value);
//     }
//     return static_cast<proxy_type&>(*this);
//   }
//
//   // *** Member functions ***
//   constexpr Entity entity_id() { return system_.entity_id(index_); }
//
// private:
//   index_t index_;
//   Ecs& system_;
// };

template<typename Data>
class Component {
public:
  // *** Type traits ***
  using data_type  = Data;
  using proxy_type = proxy_component<data_type>;

  // *** Constructors ***
  Component(Ecs<Entity>& ecs, index_t const index) : index_(index), ecs_(&ecs) { }

  // *** Member functions ***
  [[nodiscard]] Entity entity() const {
    auto entity_id = system().entity_id(index_);
    return {*ecs_, entity_id};
  }

protected:
  [[nodiscard]] proxy_type data() const { return system().at(index_); }

  System<data_type>& system() const { return ecs_->system<Component>(); }

private:
  index_t index_;
  Ecs<Entity>* ecs_;
};

} // namespace rflect3d::ecs
