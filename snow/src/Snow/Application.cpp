#include <Snow/Application.h>
#include <Snow/GUI/GUI.h>
#include <Snow/Graphics/Renderer.h>
#include <Snow/Input/Input.h>
#include "Resources.h"

namespace Snow {
    Application::Application() {
        window = std::make_unique<Snow::Impl::Window>();

        window->on_window_closed([=]() {
            try {
                exit.dispatch();
            } catch (std::exception &exception) {
                SNOW_CORE_ERROR(exception.what());
            } catch (const char *exception) {
                SNOW_CORE_ERROR(exception);
            }

            this->is_running = false;
        });

        GUI::init(window.get());
        Input::set_window(window.get());
    }

    void Application::run() {
        while (is_running) {
            window->update();

            update();

            GUI::update();

            Renderer::swap_buffers(window.get());
        }
    }

    Application::~Application() {
        Resources::cleanup();
        GUI::shutdown();
    }
}
