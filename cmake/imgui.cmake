find_package(imgui REQUIRED)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/src/engine/extern/imgui)

set(IMGUI_BACKENDS
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.h
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.h
)

if (WIN32)
    message("-- Adding IMGUI WIN32 implementation sources")
    list(APPEND IMGUI_BACKENDS
            ${IMGUI_DIR}/imgui_impl_dx12.cpp
            ${IMGUI_DIR}/imgui_impl_dx12.h
            ${IMGUI_DIR}/imgui_impl_win32.cpp
            ${IMGUI_DIR}/imgui_impl_win32.h
            ${IMGUI_DIR}/imgui_impl_dx11.cpp
            ${IMGUI_DIR}/imgui_impl_dx11.h
    )
endif ()


target_sources(Reveal3d PUBLIC ${IMGUI} ${IMGUI_BACKENDS})

target_link_libraries(Reveal3d PUBLIC imgui::imgui)
