
#function(create_new_test test_name source)
#    add_executable(${test_name} ${source})
#    target_compile_definitions(${test_name} PRIVATE
#            DOCTEST_CONFIG_COLORS_NONE
#            DOCTEST_CONFIG_NO_POSIX_SIGNALS
#            DOCTEST_CONFIG_NO_WINDOWS_SEH)
#    target_compile_options(${test_name} PRIVATE /wd4702) # unreachable code
#    add_test(NAME ${test_name} COMMAND ${test_name})
#    target_link_libraries(${test_name} PRIVATE doctest::doctest Engine)
#    target_include_directories(${test_name} PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
#    target_include_directories(${test_name} PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
#    target_include_directories(${test_name} PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
#    target_compile_definitions(${test_name} PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
#endfunction()

enable_testing()

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11  # Puedes cambiar esto a la versión que prefieras
)
FetchContent_MakeAvailable(doctest)

add_executable(test test_scene.cpp)
add_test(NAME run_tests COMMAND test_scene)
target_link_libraries(test PRIVATE doctest::doctest Reveal3d)
target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(test PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")

#foreach (f ${test_files})
#    create_new_test(${f} ${f}.cpp)
#endforeach ()


