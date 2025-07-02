
target_sources(rflect3d-engine
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src/engine/window/win32/win32.cpp
)

target_sources(rflect3d-engine
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src
        FILES
        ${PROJECT_SOURCE_DIR}/src/engine/window/win32/win32.hpp
)
