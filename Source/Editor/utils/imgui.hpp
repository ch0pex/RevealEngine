/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file imgui.hpp
 * @version 1.0
 * @date 06/11/2024
 * @brief Imgui functions
 *
 * Imgui context utility functions
 */

#pragma once

#ifdef WIN32
#include <imgui/backends/imgui_impl_dx12.h>
#include <imgui/backends/imgui_impl_win32.h>
#endif

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "window/window.hpp"


namespace ImGui {

// *** Function declarations ***

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void Init(Gfx& graphics, WHandle window_handle) { }

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void Shutdown() { }

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void NewFrame() { }

// *** Function implementations ***

#ifdef WIN32

template<>
inline void Shutdown<reveal3d::graphics::Dx12, reveal3d::window::Win32>() {
  ImGui_ImplWin32_Shutdown();
  ImGui_ImplDX12_Shutdown();
}

template<>
inline void Shutdown<reveal3d::graphics::OpenGL, reveal3d::window::Win32>() {
  Shutdown();
}

template<>
inline void Init<reveal3d::graphics::Dx12, reveal3d::window::Win32>(
    reveal3d::graphics::Dx12& graphics, WHandle const window_handle
) {
  ImGui_ImplWin32_Init(window_handle.hwnd);
  ImGui_ImplDX12_Init(
      graphics.device(), reveal3d::config::render.graphics.buffer_count, DXGI_FORMAT_R8G8B8A8_UNORM,
      graphics.heaps().srv.get(), graphics.heaps().srv.cpuStart(), graphics.heaps().srv.gpuStart()
  );
}

template<>
inline void NewFrame<reveal3d::graphics::Dx12, reveal3d::window::Win32>() {
  ImGui_ImplDX12_NewFrame();
  ImGui_ImplWin32_NewFrame();
  NewFrame();
}

#endif

template<>
inline void Shutdown<reveal3d::graphics::OpenGL, reveal3d::window::Glfw>() {
  Shutdown();
}


} // namespace ImGui
