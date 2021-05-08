//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <Snow.h>
#include "XWindowData.h"

class ExampleWindow : public Snow::GUIWindow {
private:
    int corner = 0;
    XWindowData *data;
public:
    ExampleWindow(XWindowData *_data) {
        name = "Statistics";
        window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
        data = _data;
    }

    void pre_begin() override {
        ImGuiIO& io = ImGui::GetIO();
        if (corner != -1)
        {
            const float PAD = 10.0f;
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
            ImVec2 work_size = viewport->WorkSize;
            ImVec2 window_pos, window_pos_pivot;
            window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
            window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
            window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
            window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
            ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
            ImGui::SetNextWindowViewport(viewport->ID);
            window_flags |= ImGuiWindowFlags_NoMove;
        }

        ImGui::SetNextWindowBgAlpha(0.65f); // Transparent background
    }

    void update() override {
        ImGui::LabelText("FPS", "%f", 1 / Snow::Time::deltaTime);

        ImGui::Separator();

        ImGuiIO& io = ImGui::GetIO();
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse Position: <invalid>");

        if (data != nullptr)
            ImGui::Text("Host Display: %dx%d", data->width, data->height);

        ImGui::Text("Display: %dx%d", Snow::Screen::width, Snow::Screen::height);

        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Custom",       NULL, corner == -1)) corner = -1;
            if (ImGui::MenuItem("Top-left",     NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right",    NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left",  NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            if (collapsed && ImGui::MenuItem("Close")) collapsed = false;
            ImGui::EndPopup();
        }
    }
};
