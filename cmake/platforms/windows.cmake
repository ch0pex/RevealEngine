set(PLAT win32)

include(${PROJECT_SOURCE_DIR}/cmake/backends/window/win32.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/backends/graphics/directx12.cmake)

target_link_libraries( rflect3d-engine PRIVATE d3d12 dxgi d3dcompiler ${OPENGL_LIBRARY})
target_compile_definitions(rflect3d-engine PUBLIC NOMINMAX)
