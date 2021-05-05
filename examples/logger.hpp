#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "absl/strings/str_format.h"

enum class LogLevel { kError = 0, kWarn = 1, kInfo = 2, kDebug = 3, kTrace = 4 };

enum class LogCategory {
  kRoot,
  kProfiling,
};

class Logger {
public:
  using LoggerFileHandle = FILE*;
  using Pointer = std::unique_ptr<Logger>::pointer;
  static std::string ToLogCategoryName(LogCategory category);
  static std::unique_ptr<Logger> Root;
  static std::unique_ptr<Logger> Profiling;

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void Init(const std::string& log_file, bool is_console_output, LogLevel level);

  template <typename... Args>
  void Log(LogLevel level, const absl::FormatSpec<Args...>& format, const Args&... args) const {
    if (level <= level_ && is_active_) {
      std::string content = absl::StrFormat(format, args...);
      if (is_console_on_) {
        absl::PrintF("%s  %s\n", GetLevelName(level), content);
      }

      if (target_ != nullptr) {
        absl::FPrintF(target_, "%s  %s\n", GetLevelName(level), content);
      }
    }
  }

  ~Logger();

private:
  explicit Logger(LogCategory log_category);
  static const std::string& GetLevelName(LogLevel level);
  LogLevel level_;
  bool is_init_;
  bool is_console_on_;
  bool is_active_;
  LoggerFileHandle target_;
};

// Log macro.
#define LOGE(...) Logger::Root->Log(LogLevel::kError, __VA_ARGS__)
#define LOGW(...) Logger::Root->Log(LogLevel::kWarn, __VA_ARGS__)
#define LOGI(...) Logger::Root->Log(LogLevel::kInfo, __VA_ARGS__)
#define LOGD(...) Logger::Root->Log(LogLevel::kDebug, __VA_ARGS__)

#ifdef NDEBUG
#define LOGT(...)
#else
#define LOGT(...) // Logger::Root->Log(LogLevel::kTrace, __VA_ARGS__)
#endif

// Utilities
#define LOG_EXCEPTION(ex) LOGE("Caught exception: %s", ex.what())

#endif
