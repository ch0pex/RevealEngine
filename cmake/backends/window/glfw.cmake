target_sources(rflect3d-engine
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src
        FILES
        ${PROJECT_SOURCE_DIR}/src/engine/window/glfw/glfw.hpp
)

