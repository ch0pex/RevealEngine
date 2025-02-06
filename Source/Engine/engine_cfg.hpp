/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file engine_cfg.hpp
 * @version 1.0
 * @date 01/11/2024
 * @brief Loads engine configuration
 *
 */

#pragma once
#include "common/common.hpp"

#include <span>
#include <toml++/toml.hpp>

#include "engine.hpp"

namespace reveal3d::engine {

namespace detail {

inline math::vec2 loadV2_or(toml::node_view<toml::node const> const node, math::vec2 const def) {
  if (auto const* const value = node.as_array()) {
    if (auto array = *value; array.size() == 2) {
      return {(array.at(0).as_integer()->value_or(def.x)), (array.at(1).as_integer()->value_or(def.y))};
    }
  }
  return def;
}

inline math::vec3 loadV3_or(toml::node_view<toml::node const> const node, math::vec3 const def) {
  if (auto const* const value = node.as_array()) {
    if (auto array = *value; array.size() == 3) {
      return {
        (array.at(0).as_floating_point()->value_or(def.x)), (array.at(1).as_floating_point()->value_or(def.y)),
        (array.at(2).as_floating_point()->value_or(def.z))
      };
    }
  }
  return def;
}

inline math::vec4 loadV4_or(toml::node_view<toml::node const> const node, math::vec4 const def) {
  if (auto const* const value = node.as_array()) {
    if (auto array = *value; array.size() == 4) {
      return {
        (array.at(0).as_floating_point()->value_or(def.x)), (array.at(1).as_floating_point()->value_or(def.y)),
        (array.at(2).as_floating_point()->value_or(def.z)), (array.at(3).as_floating_point()->value_or(def.w))
      };
    }
  }
  return def;
}

template<typename T>
T load_cfg(toml::table const& cfg) = delete;

template<>
inline config::Scene load_cfg(toml::table const& cfg) {
  return {
    .clearColor = loadV4_or(cfg["clearColor"], config::scene.clearColor),
    .showGrid   = cfg["showGrid"].value_or(config::scene.showGrid)
  };
}

template<>
inline config::Window load_cfg(toml::table const& cfg) {
  return {
    .backend    = config::backends::get_window_backend(cfg["backend"].value_or("win32")),
    .title      = cfg["title"].value_or(std::string {"Reveal3D"}),
    .resolution = loadV2_or(cfg["resolution"], config::window.resolution)
  };
}

template<>
inline config::Render load_cfg(toml::table const& cfg) {
  auto const gfx = cfg["graphics"];
  auto const lgt = cfg["lighting"];
  return {
    .graphics =
        {.backend       = config::backends::get_graphics_backend(gfx["backend"].value_or("directx12")),
         .max_framerate = gfx["max_framerate"].value_or(config::render.graphics.max_framerate),
         .vsync         = gfx["vsync"].value_or(config::render.graphics.vsync),
         .buffer_count  = gfx["buffer_count"].value_or(config::render.graphics.buffer_count)},
    .lighting =
        {
          .ambient_light_intensity =
              lgt["ambient_light_intensity"].value_or(config::render.lighting.ambient_light_intensity),
          .sun_light_intensity = lgt["sun_light_intensity"].value_or(config::render.lighting.sun_light_intensity),
          .ambient_color       = loadV3_or(lgt["ambient_color"], config::render.lighting.ambient_color),
          .sun_light_color     = loadV3_or(lgt["sun_light_color"], config::render.lighting.sun_light_color),
          .sun_light_direction = loadV3_or(lgt["sun_light_direction"], config::render.lighting.sun_light_direction),
        }
  };
}

template<>
inline config::Camera load_cfg(toml::table const& cfg) {
  return {
    .fov            = cfg["fov"].value_or(config::camera.fov),
    .near_plane     = cfg["near_plane"].value_or(config::camera.near_plane),
    .far_plane      = cfg["far_plane"].value_or(config::camera.far_plane),
    .movement_speed = cfg["movement_speed"].value_or(config::camera.movement_speed),
    .sensitivity    = cfg["sensitivity"].value_or(config::camera.sensitivity)
  };
}

template<>
inline config::General load_cfg(toml::table const& cfg) {
  return {};
}

} // namespace detail

template<typename T>
T config_section(toml::table const& cfg, std::string_view const name) {
  if (auto const* const sceneTbl = cfg[name].as_table()) {
    return detail::load_cfg<T>(*sceneTbl);
  }
  return {};
}

inline config::Backends read_config(std::span<char*> const args) {
  if (args.size() == 1) {
    logger(LogWarning) << "No config file was provided, using default settings";
    return {};
  }

  try {
    auto const config = toml::parse_file(args[1]);
    config::general   = config_section<config::General>(config, "general");
    config::scene     = config_section<config::Scene>(config, "scene");
    config::render    = config_section<config::Render>(config, "render");
    config::window    = config_section<config::Window>(config, "window");
    config::camera    = config_section<config::Camera>(config, "camera");
  }
  catch (std::exception const& e) {
    logger(LogError) << "Parsing file failed, using default settings";
    return {};
  }

  return {config::window.backend, config::render.graphics.backend};
}

} // namespace reveal3d::engine
