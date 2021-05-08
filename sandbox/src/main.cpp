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
    XID xid = 0x4400006;    //  xwininfo
    XWindowData host_window;

    ~Sandbox() {
        XFreePixmap(display, pixmap);
        XCompositeUnredirectWindow(display, xid, CompositeRedirectAutomatic);
    }

    Sandbox() {
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

        get_host_window_attributes(host_window);

        image = XGetImage(display, xid, 0, 0, host_window.width,
                          host_window.height, 0xffffffff,
                          ZPixmap);
        rt.generate(host_window.width, host_window.height, image->data);

        auto e = registry.create();
        auto &transform = registry.emplace<Snow::TransformComponent>(e);
        transform.position = glm::vec2(0, 0);
        transform.scale = glm::vec2(Snow::Screen::width, Snow::Screen::height);

        auto &sprite = registry.emplace<Snow::SpriteComponent>(e);
        sprite.texture = rt.id;

        Snow::GUI::add_window(new ExampleWindow(&host_window));
    }

    void get_host_window_attributes(XWindowData &data) const {
        // Get window attributes
        XWindowAttributes attr;
        Status s = XGetWindowAttributes(display, xid, &attr);
        if (s == 0) {
            SNOW_ERROR("Failed to get window attributes!");
            return;
        }

        data.width = attr.width;
        data.height = attr.height;
    }

    void update() override {
        get_host_window_attributes(host_window);

        try {
            image = XGetImage(display, xid, 0, 0, host_window.width,
                              host_window.height, 0xffffffff,
                              ZPixmap);
        } catch (std::exception &ex) {
            SNOW_ERROR(
                    "Failed getting image from host, display size {0}x{1}\n{2}",
                    host_window.width, host_window.height, ex.what());
            return;
        } catch (const char *ex) {
            SNOW_ERROR(
                    "Failed getting image from host, display size {0}x{1}\n{2}",
                    host_window.width, host_window.height, *ex);
            return;
        }

        if (image == nullptr)
            return;

        rt.generate(host_window.width, host_window.height, image->data);

        auto view = registry.view<Snow::TransformComponent>();
        for (auto e : view) {
            auto &transform = view.get<Snow::TransformComponent>(e);
            transform.position = glm::vec2(0, 0);

            float aspect_ratio =
                    (float) host_window.width / (float) host_window.height;
            if (aspect_ratio == 0)
                aspect_ratio = (float) Snow::Screen::width /
                               (float) Snow::Screen::height;
            transform.scale = glm::vec2(
                    aspect_ratio * (float) Snow::Screen::height,
                    Snow::Screen::height);
        }

        rt.update(image->data);
        image->f.destroy_image(image);
    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
