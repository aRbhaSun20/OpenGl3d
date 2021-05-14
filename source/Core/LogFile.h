#pragma once

#include "../precomz.h"

template <typename T>
using Ref = std::shared_ptr<T>;

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#pragma warning(pop)

namespace Logger
{
    class LogFile
    {
    public:
        LogFile();
        static Ref<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
    };
} // namespace Logger

// Core log macros
#define CORE_TRACE(...) ::Logger::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_INFO(...) ::Logger::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_WARN(...) ::Logger::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_ERROR(...) ::Logger::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_CRITICAL(...) ::Logger::Log::GetCoreLogger()->critical(__VA_ARGS__)
