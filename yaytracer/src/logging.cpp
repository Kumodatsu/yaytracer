#include "logging.hpp"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <format>
#include <stdexcept>

namespace yay {

  std::ostream& operator << (std::ostream& stream, LogLevel level) {
    switch (level) {
      case LogLevel::Debug:   return stream << "Debug";
      case LogLevel::Verbose: return stream << "Verbose";
      case LogLevel::Info:    return stream << "Info";
      case LogLevel::Warning: return stream << "Warning";
      case LogLevel::Error:   return stream << "Error";
      case LogLevel::Fatal:   return stream << "Fatal";
    }
    assert(("Invalid LogLevel value.", false));
    return stream;
  }

  LogMessage::LogMessage(LogLevel log_level)
    : std::stringstream()
    , m_log_level(log_level)
  { }

  Logger::Logger(LogLevel log_level)
    : m_stream(std::cout)
    , m_log_level(log_level)
  { }

  void Logger::operator += (const LogMessage& message) {
    const auto message_log_level = message.get_log_level();
    if (message_log_level < m_log_level) {
      return;
    }
    const auto time = std::chrono::system_clock::now();
    log(std::cout, message, time);
    if (message_log_level == LogLevel::Fatal) {
      throw std::runtime_error("An unrecoverable error occured.");
    }
  }

  void Logger::log(std::ostream& stream, const LogMessage& message,
      std::chrono::system_clock::time_point time) {
    std::lock_guard<std::mutex> lock(m_mutex);
    stream
      << "["
      << std::format("{:%H:%M:%OS}", time)
      << " " << std::left << std::setw(7) << message.get_log_level()
      << "] "
      << message.str() << std::endl;
  }

}
