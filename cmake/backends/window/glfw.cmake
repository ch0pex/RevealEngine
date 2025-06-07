set(GLFW_SOURCES
)

set(GLFW_HEADERS
        window/glfw/glfw.hpp
)

target_sources(Reveal3d PUBLIC ${GLFW_SOURCES} ${GLFW_HEADERS})
