find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(VulkanLoader REQUIRED)
find_package(tomlplusplus REQUIRED)
find_package(fmt REQUIRED)

target_include_directories(Reveal3d PUBLIC engine/extern)
target_link_libraries(Reveal3d PUBLIC glfw GLEW::GLEW Vulkan::Loader tomlplusplus::tomlplusplus fmt::fmt)
