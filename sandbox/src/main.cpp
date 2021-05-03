#include <iostream>
#include <Snow.h>
#include "ExampleWindow.h"

class Sandbox : public Snow::Application {
public:
    Sandbox() {
        auto tex = Snow::Resources::load_texture(
                "assets/textures/korone-derp.png",
                true,
                "derp"
        );

        const int ppu = 100;
        const int start_x = 200;
        const int start_y = 360;
        const int count = 2500;
        for (size_t i = 0; i < count; i++) {
            auto e = registry.create();
            auto &transform = registry.emplace<Snow::TransformComponent>(e);
            if (i < count * .5)
                transform.position = glm::vec2(start_x + i * ppu, start_y - i * ppu);
            else
                transform.position = glm::vec2(start_x + (count - i) * ppu, start_y + (count - i) * ppu);
            transform.rotation = 30;
            transform.scale = glm::vec2(100, 100);

            auto &sprite = registry.emplace<Snow::SpriteComponent>(e);
            sprite.texture = tex.id;
        }

        auto e2 = registry.create();
        auto &transform2 = registry.emplace<Snow::TransformComponent>(e2);
        transform2.position = glm::vec2(300, 360);
        transform2.rotation = -45;
        transform2.scale = glm::vec2(200, 200);

        auto &sprite2 = registry.emplace<Snow::SpriteComponent>(e2);
        sprite2.texture = tex.id;

        Snow::GUI::add_window(new ExampleWindow());
    }

    void update() override {
        auto view = registry.view<Snow::TransformComponent>();
        for (auto e : view) {
            auto &transform = view.get<Snow::TransformComponent>(e);
            transform.rotation += 200 * Snow::Time::deltaTime;
            transform.position.x += 500.f * Snow::Time::deltaTime;
            transform.position.y += sinf(transform.position.x / 100) * 500.f * Snow::Time::deltaTime;
            transform.position.x = (lround(transform.position.x) % 1280);
            transform.position.y = (lround(transform.position.y) % 720);
        }
    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
