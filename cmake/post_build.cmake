function(copy_glew_dll target path)
    if (WIN32)
        set(GLEW_DLL_PATH "${CMAKE_SOURCE_DIR}/src/engine/extern/lib/win32/glew32.dll")
        set(TARGET_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${GLEW_DLL_PATH}" ${path}
                COMMENT "Copying glew32.dll"
        )
    endif ()
endfunction()