#include <Snow/Application.h>
#include <Snow/GUI/GUI.h>
#include <Snow/Graphics/Renderer.h>
#include <Snow/Input/Input.h>
#include <Snow/Core/Time.h>
#include <Snow/Core/Screen.h>
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

        auto camera_entity = registry.create();
        auto camera = CameraComponent();
        registry.emplace<CameraComponent>(camera_entity, camera);
        registry.emplace<TransformComponent>(camera_entity);

        sprite_renderer_system = new SpriteRendererSystem(registry);

        glfwGetWindowSize(window->get_window(), &Screen::width, &Screen::height);
    }

    void Application::run() {
        while (is_running) {
            auto time = (float)glfwGetTime();
            Time::deltaTime = time - Time::time;
            Time::time = time;

            window->update();

            update();

            CameraSystem::update(registry);
            sprite_renderer_system->update(registry);

            GUI::update();

            Renderer::swap_buffers(window.get());
        }
    }

    Application::~Application() {
        delete sprite_renderer_system;
        Resources::cleanup();
        GUI::shutdown();
    }
}
