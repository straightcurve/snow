//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <pch.h>
#include <Snow/GUI/GUI.h>

namespace Snow {
    class GUIWindow {
        friend class GUI;

    private:
        bool begin() {
            return ImGui::Begin(name.c_str(), &collapsed, window_flags);
        }

        static void end() {
            ImGui::End();
        }

    protected:
        std::string name = "Default";
        bool collapsed = false;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;

        virtual void pre_begin() = 0;

    public:
        GUIWindow() = default;

        virtual ~GUIWindow() = default;

        virtual void update() = 0;
    };
}
