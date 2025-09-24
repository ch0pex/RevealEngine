find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
find_package(VulkanLoader REQUIRED)
find_package(tomlplusplus REQUIRED)
find_package(quill REQUIRED)
include_directories(extern)

target_link_libraries(rflect3d-engine PUBLIC glfw GLEW::GLEW Vulkan::Loader tomlplusplus::tomlplusplus rflect::rflect quill::quill)

