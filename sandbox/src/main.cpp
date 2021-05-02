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

        auto e = registry.create();
        auto &transform = registry.emplace<Snow::TransformComponent>(e);
        transform.position = glm::vec2(100, 100);
        transform.rotation = 30;
        transform.scale = glm::vec2(100, 100);

        auto &sprite = registry.emplace<Snow::SpriteComponent>(e);
        sprite.texture = tex.id;


        auto e2 = registry.create();
        auto &transform2 = registry.emplace<Snow::TransformComponent>(e2);
        transform2.position = glm::vec2(300, 100);
        transform2.rotation = -45;
        transform2.scale = glm::vec2(200, 200);

        auto &sprite2 = registry.emplace<Snow::SpriteComponent>(e2);
        sprite2.texture = tex.id;

        Snow::GUI::add_window(new ExampleWindow());
    }

    void update() override {

    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
