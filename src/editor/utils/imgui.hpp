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
#include <imgui/imgui_impl_dx12.h>
#include <imgui/imgui_impl_win32.h>
#endif

#include <imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui_internal.h>


#include "window/window.hpp"

namespace ImGui {

// *** Function declarations ***

template<rflect3d::graphics::HRI Gfx, rflect3d::window::Manager<Gfx> Window>
void Init(Gfx& graphics, auto window_handle) {
  logger(LogError) << "Not implemented";
}

template<rflect3d::graphics::HRI Gfx, rflect3d::window::Manager<Gfx> Window>
void Shutdown() {
  logger(LogError) << "Not implemented";
}

template<rflect3d::graphics::HRI Gfx, rflect3d::window::Manager<Gfx> Window>
void NewFrame() {
  logger(LogError) << "Not implemented";
}
// *** Function implementations ***

#ifdef WIN32

template<>
inline void Shutdown<rflect3d::graphics::Dx12, rflect3d::window::Win32>() {
  ImGui_ImplWin32_Shutdown();
  ImGui_ImplDX12_Shutdown();
}

template<>
inline void Shutdown<rflect3d::graphics::OpenGL, rflect3d::window::Win32>() {
  Shutdown();
}

template<>
inline void Init<rflect3d::graphics::Dx12, rflect3d::window::Win32>(
    rflect3d::graphics::Dx12& graphics, WindowHandle const window_handle
) {
  logger(LogInfo) << "Initialized Win32 and Dx12 backends for IMGUI";
  auto const& srv_heap = graphics.heaps().heap<rflect3d::graphics::dx12::HeapType::Srv>();
  ImGui_ImplWin32_Init(window_handle.hwnd);
  ImGui_ImplDX12_InitInfo init_info = {};
  init_info.Device                  = graphics.device();
  init_info.CommandQueue            = graphics.queue();
  init_info.NumFramesInFlight       = rflect3d::config::render.graphics.buffer_count;
  init_info.RTVFormat               = DXGI_FORMAT_R8G8B8A8_UNORM;
  init_info.DSVFormat               = DXGI_FORMAT_UNKNOWN;
  init_info.SrvDescriptorHeap       = srv_heap.get();

  auto const srv_descriptor              = graphics.heaps().alloc<rflect3d::graphics::dx12::HeapType::Srv>();
  init_info.LegacySingleSrvCpuDescriptor = srv_descriptor.cpu;
  init_info.LegacySingleSrvGpuDescriptor = srv_descriptor.gpu;
  ImGui_ImplDX12_Init(&init_info);
  // Allocating SRV descriptors (for textures) is up to the application, so we provide callbacks.
  // (current version of the backend will only allocate one descriptor, future versions will need to allocate more)
  //  init_info.SrvDescriptorAllocFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_handle,
  //                                      D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_handle) {
  //    auto const desc     = srv_heap.alloc();
  //    out_cpu_handle->ptr = desc.cpu.ptr;
  //    out_gpu_handle->ptr = desc.gpu.ptr;
  //  };
  //
  //  init_info.SrvDescriptorFreeFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle,
  //                                     D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle) {
  //    // TODO think about this feature I don't like how it is implemented ngl
  //  };
}

template<>
inline void NewFrame<rflect3d::graphics::Dx12, rflect3d::window::Win32>() {
  ImGui_ImplDX12_NewFrame();
  ImGui_ImplWin32_NewFrame();
  NewFrame();
}

#endif

template<>
inline void Init<rflect3d::graphics::OpenGL, rflect3d::window::Glfw>(
    rflect3d::graphics::OpenGL& graphics, GLFWwindow* window_handle
) {
  ImGui_ImplGlfw_InitForOpenGL(window_handle, true);
  ImGui_ImplOpenGL3_Init("#version 330");
}


template<>
inline void NewFrame<rflect3d::graphics::OpenGL, rflect3d::window::Glfw>() {
  ImGui_ImplGlfw_NewFrame();
  ImGui_ImplOpenGL3_NewFrame();
  NewFrame();
}

template<>
inline void Shutdown<rflect3d::graphics::OpenGL, rflect3d::window::Glfw>() {
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
  //    std::string font_path = relative("../../assets/fonts/FontAwesome.ttf");
  //    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 12);
  ImGuiStyle& style = ImGui::GetStyle();
  if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
    style.WindowRounding              = 0.0F;
    style.Colors[ImGuiCol_WindowBg].w = 1.0F;
  }
}

} // namespace ImGui
