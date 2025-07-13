#include "TX/Log.h"

#include <cstddef>
#include <cstdio>
#include <string>

#include "TX/Exception.h"

#ifdef USE_FMT
#include "fmt/base.h"
#include "fmt/format.h"
#endif  // USE_FMT

#ifdef _WIN32
#else
#include <cstdlib>
#endif

#ifdef USE_FMT
template <>
struct fmt::formatter<TX::Logger::Level> : formatter<string_view> {
  format_context::iterator format(TX::Logger::Level level,
                                  format_context &ctx) const {
    string_view name = "U";
    switch (level) {
      case TX::Logger::Level::Trace:
        name = "T";
        break;
      case TX::Logger::Level::Debug:
        name = "D";
        break;
      case TX::Logger::Level::Info:
        name = "I";
        break;
      case TX::Logger::Level::Warn:
        name = "W";
        break;
      case TX::Logger::Level::Error:
        name = "E";
        break;
      case TX::Logger::Level::Fatal:
        name = "F";
        break;
    }
    return formatter<string_view>::format(name, ctx);
  }
};
#else
const char *GetLogLevelString(TX::Logger::Level level) {
  switch (level) {
    case TX::Logger::Level::Trace:
      return "T";
    case TX::Logger::Level::Debug:
      return "D";
    case TX::Logger::Level::Info:
      return "I";
    case TX::Logger::Level::Warn:
      return "W";
    case TX::Logger::Level::Error:
      return "E";
    case TX::Logger::Level::Fatal:
      return "F";
  }
}
#endif  // USE_FMT

namespace TX {
static Logger::Reporter gReporter;
static Logger::Formatter gFormatter;
Logger::Level Logger::level_ = Level::Debug;
Logger::Reporter *Logger::reporter_ = &gReporter;
Logger::Formatter *Logger::formatter_ = &gFormatter;

void Logger::Log::clean() {
  const auto pos = file_.find_last_of('/');
  if (pos != std::string::npos) {
    file_ = file_.substr(pos + 1);
  } else {
#ifdef TK_SOURCE_DIR
    file_ = file_.substr(sizeof TK_SOURCE_DIR);
#endif
  }
}

void Logger::Log::output() const {
  reporter_->Report(*this);
  if (level_ == Level::Fatal) abort();
}

void Logger::Log::throwException() const { throw Exception(message_, scope_); }

std::string Logger::Formatter::Format(const Logger::Log &log) {
#ifdef USE_FMT
  return fmt::format("[{:s}][{:s}][{:s}][{:s}:{:d}][{:s}] {}", log.level_,
                     log.time_.Format(), log.scope_, log.file_, log.line_,
                     log.function_, log.message_);
#else
  char buf[128];
  std::snprintf(buf, sizeof(buf), "[%s][%s][%s][%s:%d][%s] %s",
                GetLogLevelString(log.level_), log.time_.Format().c_str(),
                log.scope_.c_str(), log.file_.c_str(), log.line_,
                log.function_.c_str(), log.message_.c_str());
  return buf;
#endif  // USE_FMT
}

void Logger::Reporter::Report(const Log &log) {
#ifdef USE_FMT
  fmt::println("{:s}", formatter_->Format(log));
#else
  printf("%s", formatter_->Format(log).c_str());
#endif  // USE_FMT
}
}  // namespace TX
