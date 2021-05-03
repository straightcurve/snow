//
// Created by Sweet Acid on 02.05.2021.
//

#pragma once

#include <Snow.h>

class ExampleWindow : public Snow::GUIWindow {
public:
    ExampleWindow() {
        name = "Example window";
    }

    void update() override {
        ImGui::LabelText("FPS", "%f", 1 / Snow::Time::deltaTime);
    }
};
