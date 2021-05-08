#include <iostream>
#include <Snow.h>
#include "ExampleWindow.h"

#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/extensions/Xcomposite.h>
#include <memory>

class Sandbox : public Snow::Application {
public:
    Snow::RenderTexture rt;
    Snow::Shader shader;

    _XImage *image;
    Display *display;
    Pixmap pixmap;
    XID xid = 0x1600006;    //  xwininfo
    int width;
    int height;

    ~Sandbox() {
        XFreePixmap(display, pixmap);
        XCompositeUnredirectWindow(display, xid, CompositeRedirectAutomatic);
    }

    Sandbox() {
        Snow::GUI::add_window(new ExampleWindow());

        display = XOpenDisplay(nullptr);

        // Check if Composite extension is enabled
        int event_base_return;
        int error_base_return;
        if (!XCompositeQueryExtension(display, &event_base_return,
                                     &error_base_return))
            SNOW_CORE_WARN("Composite not available!\n");

        // Requests the X server to direct the hierarchy starting at window to off-screen storage
        XCompositeRedirectWindow(display, xid, CompositeRedirectAutomatic);

        // Preventing the backing pixmap from being freed when the window is hidden/destroyed
        // If you want the window contents to still be available after the window has been destroyed,
        // or after the window has been resized (but not yet redrawn), you can increment the backing
        // pixmaps ref count to prevent it from being deallocated.
        pixmap = XCompositeNameWindowPixmap(display, xid);

        // Get window attributes
        XWindowAttributes attr;
        Status s = XGetWindowAttributes(display, xid, &attr);
        if (s == 0) {
            SNOW_ERROR("Failed to get window attributes!");
            return;
        }

        width = attr.width;
        height = attr.height;

        image = XGetImage(display, xid, 0, 0, width, height, 0xffffffff,
                          ZPixmap);
        rt.generate(width, height, image->data);

        auto e = registry.create();
        auto &transform = registry.emplace<Snow::TransformComponent>(e);
        transform.position = glm::vec2(0, 0);
        transform.scale = glm::vec2(1280, 720);

        auto &sprite = registry.emplace<Snow::SpriteComponent>(e);
        sprite.texture = rt.id;

        shader = Snow::Resources::load_shader(
                "assets/shaders/base/vertex.shader",
                "assets/shaders/x11/fragment.shader",
                nullptr,
                "base"
        );
    }

    void update() override {
        image = XGetImage(display, xid, 0, 0, width, height, 0xffffffff,
                          ZPixmap);
        if (image == nullptr)
            return;

        shader.use();
        rt.update(image->data);
        image->f.destroy_image(image);
    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
