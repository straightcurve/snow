//
// Created by Sweet Acid on 27.04.2021.
//

#pragma once

#include <pch.h>

namespace Snow {
    class Event {
    private:
        std::vector<std::function<void()>> listeners;
    public:
        Event() = default;

        ~Event() = default;

        void dispatch() const;

        void subscribe(const std::function<void()> &);

        void unsubscribe(const std::function<void()> &);

        void unsubscribe_all();
    };
}
