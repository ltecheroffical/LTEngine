#ifndef _LTCORE_LOGGER_HPP_
#define _LTCORE_LOGGER_HPP_

#include <string>
#include <queue>
#include <chrono>


namespace LTCore {
    class Logger {
    public:
        Logger() = default;
        ~Logger() = default;

        enum class LogOutput {
            None = 0,
            Stdout,
            Stderr
        };

        enum class LogType {
            Info = 0,
            Warn,
            Error,
            Fatal
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

        void setLogOutput(LogOutput output) { m_output = output; }

    private:
        std::queue<Log> m_logs;
        LogOutput m_output = LogOutput::None;
    };
}

#endif
