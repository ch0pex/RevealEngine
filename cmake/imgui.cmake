target_compile_definitions(rflect3d-engine PUBLIC IMGUI_DISABLE_SSE=1)
message("-- IMGUI DISABLE SSE")

find_package(imgui REQUIRED)
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/src/engine/extern/imgui)

target_sources(rflect3d-engine
        PRIVATE
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)


target_sources(rflect3d-engine
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src
        FILES
        ${IMGUI_DIR}/imgui_impl_glfw.h
        ${IMGUI_DIR}/imgui_impl_opengl3.h
)

if (WIN32)
    message("-- Adding IMGUI WIN32 implementation sources")
    target_sources(rflect3d-engine
            PRIVATE
            ${IMGUI_DIR}/imgui_impl_dx12.cpp
            ${IMGUI_DIR}/imgui_impl_win32.cpp
            ${IMGUI_DIR}/imgui_impl_dx11.cpp
    )
    target_sources(rflect3d-engine
            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS ${PROJECT_SOURCE_DIR}/src
            FILES
            ${IMGUI_DIR}/imgui_impl_dx12.h
            ${IMGUI_DIR}/imgui_impl_win32.h
            ${IMGUI_DIR}/imgui_impl_dx11.h
    )
endif ()

target_link_libraries(rflect3d-engine PUBLIC imgui::imgui)
