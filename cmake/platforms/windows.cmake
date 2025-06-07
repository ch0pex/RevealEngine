
set(PLAT win32)
add_compile_options(/Wall /Wextra /external:anglebrakets /external:W0 /fp:fast)

include(${PROJECT_SOURCE_DIR}/cmake/backends/graphics/directx12.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/backends/window/win32.cmake)

target_compile_definitions(rflect3d PUBLIC NOMINMAX)
target_link_libraries(rflect3d PRIVATE d3d12 dxgi d3dcompiler ${OPENGL_LIBRARY})
