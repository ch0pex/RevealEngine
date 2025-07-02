
# Definir los directorios base
set(DIRECTX12_DIR ${PROJECT_SOURCE_DIR}/src/engine/graphics/directX12)

# Archivos de DirectX12
target_sources(rflect3d-engine
        PRIVATE
        ${DIRECTX12_DIR}/resources/dx_deferring_system.cpp
        ${DIRECTX12_DIR}/utils/dx_debug.cpp
        ${DIRECTX12_DIR}/dx_commands.cpp
        ${DIRECTX12_DIR}/dx_gpass.cpp
        ${DIRECTX12_DIR}/dx_graphics_core.cpp
        ${DIRECTX12_DIR}/dx_root_signature.cpp
        ${DIRECTX12_DIR}/dx_surface.cpp
)

target_sources(rflect3d-engine
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROJECT_SOURCE_DIR}/src
        FILES
        ${DIRECTX12_DIR}/utils/dx_defaults.hpp
        ${DIRECTX12_DIR}/resources/dx_buffer.hpp
        ${DIRECTX12_DIR}/resources/dx_render_target.hpp
        ${DIRECTX12_DIR}/resources/dx_release_policies.hpp
        ${DIRECTX12_DIR}/resources/dx_render_texture.hpp
        ${DIRECTX12_DIR}/resources/dx_deferring_system.hpp
        ${DIRECTX12_DIR}/resources/dx_descriptor_heap.hpp
        ${DIRECTX12_DIR}/resources/dx_descriptor_heap_type.hpp
        ${DIRECTX12_DIR}/resources/dx_descriptors.hpp
        ${DIRECTX12_DIR}/resources/dx_frame_resource.hpp
        ${DIRECTX12_DIR}/resources/dx_texture.hpp
        ${DIRECTX12_DIR}/resources/dx_upload_buffer.hpp
        ${DIRECTX12_DIR}/resources/dx_depth_buffer.hpp
        ${DIRECTX12_DIR}/resources/dx_heaps.hpp
        ${DIRECTX12_DIR}/resources/dx_concepts.hpp
        ${DIRECTX12_DIR}/utils/dx_checker.hpp
        ${DIRECTX12_DIR}/utils/dx_resource_array.hpp
        ${DIRECTX12_DIR}/utils/dx_constants.hpp
        ${DIRECTX12_DIR}/utils/dx_debug.hpp
        ${DIRECTX12_DIR}/utils/imgui.hpp
        ${DIRECTX12_DIR}/d3dx12.h
        ${DIRECTX12_DIR}/dx_shader.hpp
        ${DIRECTX12_DIR}/dx_build_pso.hpp
        ${DIRECTX12_DIR}/dx_adapter.hpp
        ${DIRECTX12_DIR}/dx_commands.hpp
        ${DIRECTX12_DIR}/dx_gpass.hpp
        ${DIRECTX12_DIR}/dx_graphics_core.hpp
        ${DIRECTX12_DIR}/dx_pso.hpp
        ${DIRECTX12_DIR}/dx_render_element.hpp
        ${DIRECTX12_DIR}/dx_root_signature.hpp
        ${DIRECTX12_DIR}/dx_surface.hpp
)
