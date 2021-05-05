#include "logger.hpp"

#include <cstdarg>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>

std::unique_ptr<Logger> Logger::Root(new Logger(LogCategory::kRoot));
std::unique_ptr<Logger> Logger::Profiling(new Logger(LogCategory::kProfiling));

// Format the output line
const std::unordered_map<LogLevel, std::string> kLogLevelDescriptions = {{LogLevel::kError, "ERROR"},
                                                                         {LogLevel::kWarn, "WARN"},
                                                                         {LogLevel::kInfo, "INFO"},
                                                                         {LogLevel::kDebug, "DEBUG"},
                                                                         {LogLevel::kTrace, "TRACE"}};

Logger::Logger(LogCategory log_category)
: level_(LogLevel::kInfo), is_init_(false), is_console_on_(true), is_active_(is_console_on_), target_(nullptr) {}

Logger::~Logger() {
  if (target_ != nullptr) {
    fclose(target_);
    target_ = nullptr;
  }
}

std::string Logger::ToLogCategoryName(LogCategory category_) {
  switch (category_) {
  case LogCategory::kRoot:
    return "root";
  case LogCategory::kProfiling:
    return "profiling";
  default:
    std::cerr << "Unknown LogCategory:" << static_cast<int>(category_) << '\n';
    return "";
  }
}

void Logger::Init(const std::string& log_file, bool is_console_output, LogLevel level) {
  if (is_init_) {
    std::cerr << "Logger can only be init once.";
    return;
  }

  level_ = level;
  is_console_on_ = is_console_output;

  if (!log_file.empty()) {
    target_ = fopen(log_file.c_str(), "w");
  }

  is_active_ = is_console_on_ || target_ != nullptr;
}

const std::string& Logger::GetLevelName(LogLevel level) {
  return kLogLevelDescriptions.at(level);
}