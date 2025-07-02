set(OPENGL_DIR ${PROJECT_SOURCE_DIR}/src/engine/graphics/opengl)

# target_sources(rflect3d-engine
#     PRIVATE
#      ${OPENGL_DIR}/gl_graphics_core.cpp
#       ${OPENGL_DIR}/gl_render_info.cpp
#        ${OPENGL_DIR}/gl_render_layers.cpp
# )

target_sources(rflect3d-engine
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src
        FILES
        ${OPENGL_DIR}/gl_graphics_core.hpp
        ${OPENGL_DIR}/gl_render_info.hpp
        ${OPENGL_DIR}/gl_render_layers.hpp
)

