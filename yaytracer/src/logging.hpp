#pragma once
#include <sstream>
#include <type_traits>
#include <chrono>
#include <filesystem>
#include <mutex>

#ifdef NDEBUG
#define YAY_LOG_TO(logger, log_level)                                          \
  if constexpr (::yay::LogLevel::log_level != ::yay::LogLevel::Debug)          \
    logger += ::yay::LogMessage(::yay::LogLevel::log_level)
#else
#define YAY_LOG_TO(logger, log_level)                                          \
  logger += ::yay::LogMessage(::yay::LogLevel::log_level)                      \
    << "(" << ::std::filesystem::path(__FILE__).filename().string()            \
    << ":" << __LINE__ << ") "
#endif

#define YAY_LOG(log_level)                                                     \
  YAY_LOG_TO(::yay::Logger::get_static_logger(), log_level)

#define YAY_EXPRESSION(expr) #expr << ": " << (expr)

namespace yay {

  enum class LogLevel {
    Debug,   // Messages for debug purposes. Stripped out of release builds.
    Verbose, // Extra messages that generally may be superfluous.
    Info,    // Regular log messages.
    Warning, // Messages indicating a problem might appear in the future.
    Error,   // Messages for recovarable errors.
    Fatal,   // Messages for non-recoverable errors. Will throw a runtime error. 
  };

  std::ostream& operator << (std::ostream& stream, LogLevel level);

  class LogMessage : public std::stringstream {
  public:
    LogMessage(LogLevel log_level);

    inline LogLevel get_log_level() const {
      return m_log_level;
    }
  private:
    LogLevel m_log_level;
  };

  class Logger {
  public:
    Logger(LogLevel log_level = LogLevel::Info);

    void operator += (const LogMessage& message);

    inline static Logger& get_static_logger() {
      static Logger logger;
      return logger;
    }

    inline LogLevel get_log_level() const {
      return m_log_level;
    }

    inline void set_log_level(LogLevel log_level) {
      m_log_level = log_level;
    }
  private:
    std::ostream& m_stream;
    LogLevel      m_log_level;
    std::mutex    m_mutex;

    void log(std::ostream& stream, const LogMessage& message,
      std::chrono::system_clock::time_point time);
  };

}
