#pragma once

#include <memory>
template <typename T>
using Ref = std::shared_ptr<T>;

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#pragma warning(pop)

namespace Logger
{
    class Log
    {
    public:
        static void Init();

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
