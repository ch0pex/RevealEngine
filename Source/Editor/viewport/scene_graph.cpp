/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "scene_graph.hpp"


using namespace std::literals::string_literals;



namespace reveal3d::ui {

SceneGraph::SceneGraph() : selected_(UINT_MAX) {

}

void SceneGraph::Draw() {

    ImGui::Begin("Scene Graph");
    for (size_t i = 0; i < core::scene.NumEntities(); ++i) {

        std::string name = core::scene.GetName(i);
        if (name[0] != '\0') {
            if (ImGui::Selectable(name.c_str(), selected_ == i)) {
                selected_ = i;
            }
        } else {
            if (ImGui::Selectable("##SelectedEntity", selected_ == i)) {
                selected_ = i;
            }
        }
    }

    ImGui::End();
}

}

