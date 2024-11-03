/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file engine_cfg.hpp
 * @version 1.0
 * @date 01/11/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once
#include "common/common.hpp"

#include <span>
#include <toml++/toml.hpp>

#include "engine.hpp"

namespace reveal3d {

namespace detail {

inline math::vec2 loadV2_or(const toml::node_view<toml::node const> node, const math::vec2 def) {
  if (const auto value = node.as_array()) {
    if (auto array = *value; array.size() == 2) {
      return {(array.at(0).as_floating_point()->value_or(def.x)), (array.at(1).as_floating_point()->value_or(def.y))};
    }
  }
  return def;
}

inline math::vec3 loadV3_or(const toml::node_view<toml::node const> node, const math::vec3 def) {
  if (const auto value = node.as_array()) {
    if (auto array = *value; array.size() == 3) {
      return {
        (array.at(0).as_floating_point()->value_or(def.x)), (array.at(1).as_floating_point()->value_or(def.y)),
        (array.at(2).as_floating_point()->value_or(def.z))
      };
    }
  }
  return def;
}

inline math::vec4 loadV4_or(const toml::node_view<toml::node const> node, const math::vec4 def) {
  if (const auto value = node.as_array()) {
    if (auto array = *value; array.size() == 4) {
      return {
        (array.at(0).as_floating_point()->value_or(def.x)), (array.at(1).as_floating_point()->value_or(def.y)),
        (array.at(2).as_floating_point()->value_or(def.z)), (array.at(3).as_floating_point()->value_or(def.w))
      };
    }
  }
  return def;
}

inline config::Scene load_scene_cfg(const toml::table& cfg) {
  return {
    .clearColor = loadV4_or(cfg["clearColor"], config::scene.clearColor),
    .showGrid   = cfg["showGrid"].value_or(config::scene.showGrid)
  };
}

inline config::Window load_window_cfg(const toml::table& cfg) {
  return {
    .title      = cfg["title"].value_or(std::string {"Reveal3D"}),
    .resolution = loadV2_or(cfg["resolution"], config::Window {}.resolution)
  };
}

inline config::Lighting load_lighting_cfg(const toml::table& cfg) {
  return {
    .ambient_light_intensity = cfg["ambient_light_intensity"].value_or(config::Lighting {}.ambient_light_intensity),
    .ambient_color           = loadV3_or(cfg["ambient_color"], config::Lighting {}.ambient_color)
  };
}

inline config::Graphics load_graphics_cfg(const toml::table& cfg) {
  return {
    .max_framerate = cfg["max_framerate"].value_or(config::Graphics {}.max_framerate),
    .vsync         = cfg["vsync"].value_or(config::Graphics {}.vsync)
  };
}

inline config::Camera load_camera_cfg(const toml::table& cfg) {
  return {
    .fov            = cfg["fov"].value_or(config::Camera {}.fov),
    .near_plane     = cfg["near_plane"].value_or(config::Camera {}.near_plane),
    .far_plane      = cfg["far_plane"].value_or(config::Camera {}.far_plane),
    .movement_speed = cfg["movement_speed"].value_or(config::Camera {}.movement_speed),
    .sensitivity    = cfg["sensitivity"].value_or(config::Camera {}.sensitivity)
  };
}

} // namespace detail

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
Engine<Gfx, Window> init_from_config(const std::span<char*> args) {
  if (args.size() == 1) {
    logger(LogWarning) << "No config file was provided, using default settings";
    return {};
  }

  try {
    toml::table config = toml::parse_file(args[1]);
    if (const auto sceneTbl = config["scene"].as_table()) {
      config::scene = detail::load_scene_cfg(*sceneTbl);
    }
    if (const auto graphics_tbl = config["graphics"].as_table()) {
      config::graphics = detail::load_graphics_cfg(*graphics_tbl);
    }
    if (const auto light_tbl = config["lighting"].as_table()) {
      config::lighting = detail::load_lighting_cfg(*light_tbl);
    }
    if (const auto window_tbl = config["camera"].as_table()) {
      config::window = detail::load_window_cfg(*window_tbl);
    }
    if (const auto camera_tbl = config["camera"].as_table()) {
      config::camera = detail::load_camera_cfg(*camera_tbl);
    }
  }
  catch (const std::exception& e) {
    logger(LogError) << "Parsing file failed, using default settings";
    return {};
  }

  return {};
}

} // namespace reveal3d
