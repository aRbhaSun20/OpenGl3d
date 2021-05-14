#include "LogFile.h"

namespace Logger
{
    Ref<spdlog::logger> LogFile::s_CoreLogger;

    LogFile::LogFile()
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

        s_CoreLogger = std::make_shared<spdlog::logger>("3dEngine", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);
    }
} // namespace Logger