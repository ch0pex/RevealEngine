add_library(
  rflect3d_static_test STATIC #
  primitive_types.cpp #
)

target_link_libraries(rflect3d_static_test PRIVATE rflect3d-engine)
