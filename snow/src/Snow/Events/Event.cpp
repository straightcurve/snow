//
// Created by Sweet Acid on 27.04.2021.
//

#include "Event.h"

namespace Snow {
    void Event::subscribe(const std::function<void()> &callback) {
        listeners.push_back(callback);
    }

    void Event::unsubscribe(const std::function<void()> &callback) {
        const int count = listeners.size();
        auto i = 0;
        bool found = false;
        while (!found && i < count)
            found = &listeners[i++] == &callback;

        if (!found)
            return;

        listeners.erase(listeners.begin() + i);
    }

    void Event::unsubscribe_all() {
        listeners.clear();
    }

    void Event::dispatch() const {
        for (const auto &l: listeners)
            l();
    }
}
