//
// Created by Sweet Acid on 27.04.2021.
//

#include <Snow/GUI/Backends/imgui_impl_opengl3.h>
#include <Snow/GUI/Backends/imgui_impl_glfw.h>
#include "GUI.h"
#include <pch.h>

namespace Snow {
    std::vector<GUIWindow*> GUI::windows;

    void GUI::init(Impl::Window *window) {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO &io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        io.DisplaySize = ImVec2(1280, 720);
        io.DeltaTime = .16f;

        ImGui_ImplGlfw_InitForOpenGL(window->get_window(), true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void GUI::shutdown() {
        for (auto window : windows)
            delete window;
        windows.clear();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void GUI::update() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (auto window : windows) {
            window->pre_begin();
            window->begin();
            window->update();
            GUIWindow::end();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GUI::add_window(GUIWindow *window) {
        windows.push_back(window);
    }
}
