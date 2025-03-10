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

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "window/window.hpp"


namespace ImGui {

// *** Function declarations ***

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void Init(Gfx& graphics, WHandle window_handle) {
  logger(LogError) << "Not implemented";
  std::abort();
}

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void Shutdown() {
  logger(LogError) << "Not implemented";
  std::abort();
}

template<reveal3d::graphics::HRI Gfx, reveal3d::window::Manager<Gfx> Window>
void NewFrame() {
  logger(LogError) << "Not implemented";
  std::abort();
}
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
  auto const& srv_heap = graphics.heaps().heap<reveal3d::graphics::dx12::HeapType::Srv>();
  ImGui_ImplWin32_Init(window_handle.hwnd);
  ImGui_ImplDX12_Init(
      graphics.device(), reveal3d::config::render.graphics.buffer_count, DXGI_FORMAT_R8G8B8A8_UNORM, srv_heap.get(),
      srv_heap.cpuStart(), srv_heap.gpuStart()
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
inline void
Init<reveal3d::graphics::OpenGL, reveal3d::window::Glfw>(reveal3d::graphics::OpenGL& graphics, WHandle window_handle) {
  ImGui_ImplGlfw_InitForOpenGL(window_handle, true);
  ImGui_ImplOpenGL3_Init("#version 300");
}


template<>
inline void
NewFrame<reveal3d::graphics::OpenGL, reveal3d::window::Glfw>() {
  ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();
  NewFrame();
}

template<>
inline void Shutdown<reveal3d::graphics::OpenGL, reveal3d::window::Glfw>() {
  Shutdown();
}

inline void Config() {
  ImGuiIO& io = GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
  io.ConfigViewportsNoAutoMerge   = true;
  io.ConfigViewportsNoTaskBarIcon = true;
  io.WantCaptureKeyboard          = false;
  //    std::string font_path = relative("../../Assets/fonts/FontAwesome.ttf");
  //    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 12);
  ImGuiStyle& style = ImGui::GetStyle();
  if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
    style.WindowRounding              = 0.0F;
    style.Colors[ImGuiCol_WindowBg].w = 1.0F;
  }
}

} // namespace ImGui
