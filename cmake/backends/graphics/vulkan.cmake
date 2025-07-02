set(VULKAN_DIR ${PROJECT_SOURCE_DIR}/src/engine/graphics/vulkan)

target_sources(
  rflect3d-engine PUBLIC FILE_SET HEADERS BASE_DIRS ${PROJECT_SOURCE_DIR}/src
                      FILES ${VULKAN_DIR}/vk_graphics_core.hpp)
