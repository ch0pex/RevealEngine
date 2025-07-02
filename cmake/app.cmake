target_sources(
  rflect3d-editor
  PUBLIC FILE_SET
         HEADERS
         BASE_DIRS
         ${PROJECT_SOURCE_DIR}/src
         FILES
         ${PROJECT_SOURCE_DIR}/src/app/project/project.hpp
         ${PROJECT_SOURCE_DIR}/src/app/state_machine/fsm.hpp
         ${PROJECT_SOURCE_DIR}/src/app/state_machine/states.hpp
         ${PROJECT_SOURCE_DIR}/src/app/engine.hpp
         ${PROJECT_SOURCE_DIR}/src/app/engine_cfg.hpp
         ${PROJECT_SOURCE_DIR}/src/app/run_engine.hpp)
