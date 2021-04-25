//
// Created by Sweet Acid on 24.04.2021.
//

#pragma once

#include <spdlog/spdlog.h>

namespace Snow {
    class Log {
    private:
        inline static std::shared_ptr<spdlog::logger> core_logger;
        inline static std::shared_ptr<spdlog::logger> client_logger;

    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger> &get_core_logger() {
            return core_logger;
        }

        inline static std::shared_ptr<spdlog::logger> &get_client_logger() {
            return client_logger;
        }
    };
}

#define SNOW_CORE_FATAL(...) ::Snow::Log::get_core_logger()->fatal(__VA_ARGS__);
#define SNOW_CORE_ERROR(...) ::Snow::Log::get_core_logger()->error(__VA_ARGS__);
#define SNOW_CORE_WARN(...)  ::Snow::Log::get_core_logger()->warn(__VA_ARGS__);
#define SNOW_CORE_INFO(...)  ::Snow::Log::get_core_logger()->info(__VA_ARGS__);
#define SNOW_CORE_TRACE(...) ::Snow::Log::get_core_logger()->trace(__VA_ARGS__);

#define SNOW_FATAL(...) ::Snow::Log::get_client_logger()->fatal(__VA_ARGS__);
#define SNOW_ERROR(...) ::Snow::Log::get_client_logger()->error(__VA_ARGS__);
#define SNOW_WARN(...)  ::Snow::Log::get_client_logger()->warn(__VA_ARGS__);
#define SNOW_INFO(...)  ::Snow::Log::get_client_logger()->info(__VA_ARGS__);
#define SNOW_TRACE(...) ::Snow::Log::ge~t_client_logger()->trace(__VA_ARGS__);
