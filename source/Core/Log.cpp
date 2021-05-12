#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <iostream>
namespace Logger
{
    Ref<spdlog::logger> Log::s_CoreLogger;

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        try
        {
            // logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("../logs/logger.log", true));

            // logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[0]->set_pattern("[%T] [%l] %n: %v");
        }
        catch (const spdlog::spdlog_ex &ex)
        {
            std::cout << "Log init failed: " << ex.what() << std::endl;
        }

        s_CoreLogger = std::make_shared<spdlog::logger>("Cuber", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

    }
}