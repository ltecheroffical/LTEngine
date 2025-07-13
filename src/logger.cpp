#include <cstdarg>
#include <iostream>

#include <LTEngine/logger.hpp>


using namespace LTEngine;


void Logger::info(const char *format, ...) {
	Log log;

	log.type = LogType::INFO;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	_logs.push(log);

	switch (_output) {
		case LogOutput::STDOUT:
			{
				std::string type = "";
				if (log.type == LogType::INFO) {
					type = "INFO";
				} else if (log.type == LogType::WARN) {
					type = "WARN";
				} else if (log.type == LogType::ERROR) {
					type = "ERROR";
				} else if (log.type == LogType::FATAL) {
					type = "FATAL";
				}

				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::STDERR:
			{
				std::string type = "";
				if (log.type == LogType::INFO) {
					type = "INFO";
				} else if (log.type == LogType::WARN) {
					type = "WARN";
				} else if (log.type == LogType::ERROR) {
					type = "ERROR";
				} else if (log.type == LogType::FATAL) {
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

	log.type = LogType::INFO;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	_logs.push(log);

	switch (_output) {
		case LogOutput::STDOUT:
			{
				std::string type = "INFO";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::STDERR:
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

	log.type = LogType::INFO;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	_logs.push(log);

	switch (_output) {
		case LogOutput::STDOUT:
			{
				std::string type = "WARN";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::STDERR:
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

	log.type = LogType::INFO;

	va_list args;
	va_start(args, format);

	char buffer[1024];
	std::vsnprintf(buffer, sizeof(buffer), format, args);

	log.message = std::string(buffer);

	va_end(args);

	_logs.push(log);

	switch (_output) {
		case LogOutput::STDOUT:
			{
				std::string type = "FATAL";
				std::cout << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		case LogOutput::STDERR:
			{
				std::string type = "FATAL";
				std::cerr << "[" << log.time << "][" << type << "] " << log.message << std::endl;
				break;
			}
		default:
			break;
	}
}
