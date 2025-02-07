#include <cstdarg>
#include <iostream>

#include <LTEngine/logger.hpp>


using namespace LTEngine;


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
