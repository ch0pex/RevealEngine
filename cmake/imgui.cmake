target_compile_definitions(Reveal3d PUBLIC IMGUI_DISABLE_SSE=1)
message("-- IMGUI DISABLE SSE")

find_package(imgui REQUIRED)
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/src/engine/extern/imgui)
set(IMGUI_BACKENDS
    ${IMGUI_DIR}/imgui_impl_glfw.cpp ${IMGUI_DIR}/imgui_impl_glfw.h
    ${IMGUI_DIR}/imgui_impl_opengl3.cpp ${IMGUI_DIR}/imgui_impl_opengl3.h)

if(WIN32)
  message("-- Adding IMGUI WIN32 implementation sources")
  list(
    APPEND
    IMGUI_BACKENDS
    ${IMGUI_DIR}/imgui_impl_dx12.cpp
    ${IMGUI_DIR}/imgui_impl_dx12.h
    ${IMGUI_DIR}/imgui_impl_win32.cpp
    ${IMGUI_DIR}/imgui_impl_win32.h
    ${IMGUI_DIR}/imgui_impl_dx11.cpp
    ${IMGUI_DIR}/imgui_impl_dx11.h)
endif()

target_sources(rflect3d PUBLIC ${IMGUI} ${IMGUI_BACKENDS})

target_link_libraries(rflect3d PUBLIC imgui::imgui)
