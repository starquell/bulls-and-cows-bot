#pragma once

#include <spdlog.h>
#include <async.h>
#include <sinks/daily_file_sink.h>

#include <memory>
#include <cstdint>
#include <string_view>

namespace game {

    class Logger {
    private:
        explicit Logger();
    public:

        Logger (const Logger&) = delete;
        Logger (Logger&&) = delete;
        Logger& operator= (const Logger&) = delete;
        Logger& operator= (Logger&&) = delete;

        static auto get() -> std::shared_ptr<spdlog::logger>;

    private:
        static constexpr inline std::string_view _name = "logger";
        static constexpr inline std::string_view _path = "logs/daily";
        static constexpr inline std::uint8_t _hour = 6;
        static constexpr inline std::uint8_t _minute = 15;
        std::shared_ptr <spdlog::logger> _logger;
    };
}



