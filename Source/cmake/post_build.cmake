
if (WIN32)
    set(GLEW_DLL_PATH "${CMAKE_SOURCE_DIR}/Source/Reveal3d/extern/lib/win32/glew32.dll")
    set(TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

    if (NOT TARGET_DIR)
        set(TARGET_DIR "${CMAKE_BINARY_DIR}")
    endif ()

    add_custom_command(TARGET RevealEngine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GLEW_DLL_PATH}" "${TARGET_DIR}/Source"
            COMMENT "Copying glew32.dll"
    )
endif ()