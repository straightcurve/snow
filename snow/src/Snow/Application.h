#pragma once

#include <Snow/Window.h>
#include <Snow/Events/Event.h>
#include <entt.hpp>
#include <Snow/Core/SpriteRendererSystem.h>

namespace Snow {
    class Application {
    public:
        Application();

        /**
         * marked virtual because we need to
         * clean up other systems e.g. Resources
         */
        virtual ~Application();

        void run();

        virtual void update() = 0;

        Event exit;

    protected:
        //  FIXME: temporary
        entt::registry registry;

    private:
        bool is_running = true;
        std::unique_ptr<Snow::Impl::Window> window;

        SpriteRendererSystem *sprite_renderer_system;
    };

    extern Application *CreateApplication();
}
