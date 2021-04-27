//
// Created by Sweet Acid on 27.04.2021.
//

#include <pch.h>
#include <Snow/GUI/imgui_impl_opengl3.h>
#include "GUI.h"

namespace Snow {
    void Snow::GUI::init() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.DisplaySize = ImVec2(1280, 720);
        io.DeltaTime = .16f;

        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void Snow::GUI::update() {
//        ImGuiIO &io = ImGui::GetIO();
//        io.DisplaySize = ImVec2(1280, 720);
//        io.DeltaTime = .16f;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
