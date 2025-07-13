#ifndef _LTENGINE_LOGGER_HPP_
#define _LTENGINE_LOGGER_HPP_

#include <string>
#include <queue>
#include <chrono>


namespace LTEngine {
    class Logger {
    public:
        Logger() = default;
        ~Logger() = default;

        enum class LogOutput {
            NONE = 0,
            STDOUT,
            STDERR
        };

        enum class LogType {
            INFO = 0,
            WARN,
            ERROR,
            FATAL
        };

        struct Log {
            std::string message;
            LogType type;
            std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
        };

        void info(const char *format, ...);
        void warn(const char *format, ...);
        void error(const char *format, ...);
        void fatal(const char *format, ...);

        void set_log_output(LogOutput output) { _output = output; }

    private:
        std::queue<Log> _logs;
        LogOutput _output = LogOutput::NONE;
    };
}

#endif
