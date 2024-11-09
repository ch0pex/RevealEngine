enable_testing()

include(FetchContent)

FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

add_executable(run_tests test_scene.cpp test_content.cpp)
add_executable(test_scene test_scene.cpp)
add_executable(test_content test_content.cpp)
add_test(NAME test_scene COMMAND test_scene)
add_test(NAME test_content COMMAND test_content)
target_link_libraries(run_tests PRIVATE doctest::doctest Reveal3d)
target_include_directories(run_tests PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(run_tests PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(run_tests PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(run_tests PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
target_link_libraries(test_scene PRIVATE doctest::doctest Reveal3d)
target_include_directories(test_scene PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(test_scene PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(test_scene PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(test_scene PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
target_link_libraries(test_content PRIVATE doctest::doctest Reveal3d)
target_include_directories(test_content PRIVATE ${PROJECT_SOURCE_DIR}/Source/Reveal3d)
target_include_directories(test_content PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/math/win32)
target_include_directories(test_content PUBLIC ${PROJECT_SOURCE_DIR}/Source/Reveal3d/extern/include)
target_compile_definitions(test_content PUBLIC PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
