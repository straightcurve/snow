//
// Created by Sweet Acid on 27.04.2021.
//

#include <Snow/GUI/Backends/imgui_impl_opengl3.h>
#include <Snow/GUI/Backends/imgui_impl_glfw.h>
#include "GUI.h"

namespace Snow {
    void Snow::GUI::init(GLFWwindow *window) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.DisplaySize = ImVec2(1280, 720);
        io.DeltaTime = .16f;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void GUI::shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Snow::GUI::update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
