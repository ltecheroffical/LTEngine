#include <cstdarg>
#include <iostream>

#include <LTCore/logger.hpp>


using namespace LTCore;


void Logger::info(const char *format, ...) {
	Log log;

	log.type = LogType::Info;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	m_logs.push(log);

	switch (m_output) {
		case LogOutput::Stdout:
			{
				std::string type = "";
				if (log.type == LogType::Info) {
					type = "INFO";
				} else if (log.type == LogType::Warn) {
					type = "WARN";
				} else if (log.type == LogType::Error) {
					type = "ERROR";
				} else if (log.type == LogType::Fatal) {
					type = "FATAL";
				}

				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::Stderr:
			{
				std::string type = "";
				if (log.type == LogType::Info) {
					type = "INFO";
				} else if (log.type == LogType::Warn) {
					type = "WARN";
				} else if (log.type == LogType::Error) {
					type = "ERROR";
				} else if (log.type == LogType::Fatal) {
					type = "FATAL";
				}

				std::cerr << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		default:
			break;
	}
}

void Logger::warn(const char *format, ...) {
	Log log;

	log.type = LogType::Info;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	m_logs.push(log);

	switch (m_output) {
		case LogOutput::Stdout:
			{
				std::string type = "INFO";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::Stderr:
			{
				std::string type = "INFO";

				std::cerr << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		default:
			break;
	}
}

void Logger::error(const char *format, ...) {
	Log log;

	log.type = LogType::Info;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	m_logs.push(log);

	switch (m_output) {
		case LogOutput::Stdout:
			{
				std::string type = "WARN";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::Stderr:
			{
				std::string type = "WARN";
				std::cerr << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		default:
			break;
	}
}

void Logger::fatal(const char *format, ...) {
	Log log;

	log.type = LogType::Info;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	m_logs.push(log);

	switch (m_output) {
		case LogOutput::Stdout:
			{
				std::string type = "FATAL";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::Stderr:
			{
				std::string type = "FATAL";
				std::cerr << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		default:
			break;
	}
}
