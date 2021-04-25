//
// Created by tony on 24.04.2021.
//

#include <Snow/Log.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Snow {
    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        Log::core_logger = spdlog::stdout_color_mt("Snow");
        Log::core_logger->set_level(spdlog::level::trace);

        Log::client_logger = spdlog::stdout_color_mt("App");
        Log::client_logger->set_level(spdlog::level::trace);
    }
}
