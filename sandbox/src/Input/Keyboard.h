//
// Created by Sweet Acid on 20.05.2021.
//

#pragma once

#include <linux/uinput.h>
#include <fcntl.h>
#include <cstring>
#include <zconf.h>
#include <unordered_map>

#include <Snow/Input/Key.h>
#include "LinuxKey.h"

namespace Input {
    class Keyboard {
    private:
        int fd;
        std::unordered_map<Snow::Key, LinuxKey> map;

    public:
        Keyboard() {
            struct uinput_setup usetup{};

            fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
            ioctl(fd, UI_SET_EVBIT, EV_KEY);

            for (int k = 0; k < 249; ++k) {
                ioctl(fd, UI_SET_KEYBIT, k);
            }

            memset(&usetup, 0, sizeof(usetup));
            usetup.id.bustype = BUS_USB;
            usetup.id.vendor = 0x1234; /* sample vendor */
            usetup.id.product = 0x5678; /* sample product */
            strcpy(usetup.name, "Snow Virtual Keyboard");

            ioctl(fd, UI_DEV_SETUP, &usetup);
            ioctl(fd, UI_DEV_CREATE);

            setup_keymap();
        }

        ~Keyboard() {
            ioctl(fd, UI_DEV_DESTROY);
            close(fd);
        }

        void emit(int type, int code, int val) const {
            struct input_event ie {};

            ie.type = type;
            ie.code = code;
            ie.value = val;
            /* timestamp values below are ignored */
            ie.time.tv_sec = 0;
            ie.time.tv_usec = 0;

            write(fd, &ie, sizeof(ie));
        }

        void press_key(Snow::Key key) const {
            emit(EV_KEY, static_cast<int>(map.at(key)), 1);

            /**
             * report the event
             */
            emit(EV_SYN, SYN_REPORT, 0);
        }

        void release_key(Snow::Key key) const {
            emit(EV_KEY, static_cast<int>(map.at(key)), 0);

            /**
             * report the event
             */
            emit(EV_SYN, SYN_REPORT, 0);
        }

        void setup_keymap() {
            map.insert_or_assign(Snow::Key::W, LinuxKey::W);
            map.insert_or_assign(Snow::Key::A, LinuxKey::A);
            map.insert_or_assign(Snow::Key::S, LinuxKey::S);
            map.insert_or_assign(Snow::Key::D, LinuxKey::D);
            map.insert_or_assign(Snow::Key::J, LinuxKey::J);
            map.insert_or_assign(Snow::Key::K, LinuxKey::K);
            map.insert_or_assign(Snow::Key::L, LinuxKey::L);
            map.insert_or_assign(Snow::Key::I, LinuxKey::I);
            map.insert_or_assign(Snow::Key::Q, LinuxKey::Q);
            map.insert_or_assign(Snow::Key::E, LinuxKey::E);
            map.insert_or_assign(Snow::Key::R, LinuxKey::R);
        }
    };
}
