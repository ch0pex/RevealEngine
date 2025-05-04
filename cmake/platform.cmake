
if (WIN32)
    message("-- WINDOWS")
    message("-- Source dir: ${PROJECT_SOURCE_DIR}")
    include(${PROJECT_SOURCE_DIR}/cmake/platforms/windows.cmake)
elseif (UNIX)
    message("-- UNIX")
    message("-- Source dir: ${PROJECT_SOURCE_DIR}")
    include(${PROJECT_SOURCE_DIR}/cmake/platforms/unix.cmake)
endif ()

# Cross platform backends
include(${PROJECT_SOURCE_DIR}/cmake/backends/graphics/opengl.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/backends/graphics/vulkan.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/backends/window/glfw.cmake)
