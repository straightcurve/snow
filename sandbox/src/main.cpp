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
    XID xid = 0x4800006;    //  xwininfo
    XWindowData host_window;

    entt::entity e, e2;

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

        e = registry.create();
        auto &transform = registry.emplace<Snow::TransformComponent>(e);
        transform.position = glm::vec2(0, -Snow::Screen::height);
        transform.scale = glm::vec2(Snow::Screen::width,
                                    Snow::Screen::height * 2);

        auto &sprite = registry.emplace<Snow::SpriteComponent>(e);
        sprite.texture = rt.id;

        e2 = registry.create();
        auto &transform2 = registry.emplace<Snow::TransformComponent>(e2);
        transform2.position = glm::vec2(0, 0);
        transform2.scale = glm::vec2(200, 200);

//        auto &sprite2 = registry.emplace<Snow::SpriteComponent>(e2);
//        sprite2.texture = rt.id;

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

        {
            auto &transform = registry.get<Snow::TransformComponent>(e);
            float aspect_ratio;
            if (host_window.height == 0) {
                aspect_ratio = (float) Snow::Screen::width /
                               (float) Snow::Screen::height;
            }

            aspect_ratio =
                    (float) host_window.width / (float) host_window.height;

            /**
             * check if we have to scale on x/y depending
             * on which dimension is longer
             *
             * TODO: clamp this to some value
             */
            if (host_window.width > Snow::Screen::width) {
                transform.scale.x = Snow::Screen::width * 2;
                transform.scale.y = transform.scale.x / aspect_ratio;
                transform.position.x = (float) -Snow::Screen::width;
                transform.position.y = -transform.scale.y / 2;
            } else {
                transform.scale.y = Snow::Screen::height * 2;
                transform.scale.x = aspect_ratio * transform.scale.y;
                transform.position.y = (float) -Snow::Screen::height;
                transform.position.x = -transform.scale.x / 2;
            }
        }

        rt.update(image->data);
        image->f.destroy_image(image);
    }
};

Snow::Application *Snow::CreateApplication() {
    return new Sandbox();
}
