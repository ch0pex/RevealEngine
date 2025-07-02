function(add_rflect3d_utest test_name test_src)
  list(APPEND TEST_FLAGS "--duration=true")

  set(JUNIT_DIR "${PROJECT_BINARY_DIR}/junit")
  file(MAKE_DIRECTORY ${JUNIT_DIR})
  set(JUNIT_FILE "${JUNIT_DIR}/${test_name}.xml")
  message("Setting junit file: ${JUNIT_FILE}")
  list(APPEND TEST_FLAGS "--reporters=junit")
  list(APPEND TEST_FLAGS "--out=${JUNIT_FILE}")

  set(test_exe_name "rflect3d_${test_name}")
  add_executable(${test_exe_name} ${test_src})
  target_link_libraries(${test_exe_name} PRIVATE doctest::doctest)
  target_link_libraries(${test_exe_name} PUBLIC rflect3d-engine)
  target_include_directories(
    ${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src/engine
                            ${PROJECT_SOURCE_DIR}/src/engine/extern)
  target_compile_definitions(${test_exe_name}
                             PRIVATE DOCTEST_CONFIG_NO_SHORT_MACRO_NAMES)
  target_include_directories(${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src)
  add_test(${test_name} ${test_exe_name} ${TEST_FLAGS})
endfunction()

function(add_rflect3d_ftest test_name test_src)
  set(test_exe_name "rflect3d_${test_name}")
  include(${PROJECT_SOURCE_DIR}/cmake/editor.cmake)
  include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)
  list(TRANSFORM EDITOR_SOURCES PREPEND "${BASE}")
  list(TRANSFORM ENGINE_SOURCES PREPEND "${BASE}")
  add_executable(${test_exe_name} ${test_src} ${ENGINE_SOURCES}
                                  ${EDITOR_SOURCES})
  target_link_libraries(${test_exe_name} PUBLIC rflect3d-engine)
  target_include_directories(
    ${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src/engine
                            ${PROJECT_SOURCE_DIR}/src/engine/extern)
  target_include_directories(${test_exe_name} PUBLIC ${PROJECT_SOURCE_DIR}/src)
endfunction()
