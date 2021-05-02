//
// Created by Sweet Acid on 27.04.2021.
//

#pragma once
#include <GLFW/glfw3.h>
#include <Snow/Window.h>
#include <Snow/GUI/Window.h>

namespace Snow {
    class GUI {
        friend class Application;
    private:
        static std::vector<GUIWindow*> windows;
        static void init(Impl::Window *);
        static void shutdown();
        static void update();

    public:
        static void add_window(GUIWindow* window);
    };
}
