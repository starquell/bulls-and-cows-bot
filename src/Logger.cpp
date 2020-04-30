#include "Logger.hpp"

namespace game {

    Logger::Logger()
         : _logger{spdlog::daily_logger_mt(_name.data(), _path.data(), _hour, _minute)}
    {
        _logger->set_pattern("*** [%H:%M:%S] [thread %t] [%s] [line %#] %v");
    }

    auto Logger::get() -> std::shared_ptr<spdlog::logger>
    {
        static Logger _instance;
        return _instance._logger;
    }
}
