#include <unistd.h>
#include <stdio.h>
#include <chrono>
#include <string>
#include <iomanip>
#include "logger.hpp"

std::string Logger::logLevelToString(const int level)
{
  switch (level)
  {
  case INFO:
    return "INFO";
  case WARNING:
    return "WARNING";
  case ERROR:
    return "ERROR";
  case DEBUG:
    return "DEBUG";
  default:
    return "UNKNOWN";
  }
}

/**
 * Helper function to get the current timestamp used for log formatting
 */
std::string Logger::getCurrentISOTimestampString()
{
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&in_time_t), "%FT%TZ");
  return ss.str();
}

std::string Logger::formatLogMessage(std::string message, const int level)
{
  std::string levelString = logLevelToString(level);
  std::string timestampString = getCurrentISOTimestampString();
  std::string formattedMessage = "[" + levelString + "] " + timestampString + ": " + message;
  return formattedMessage;
}

void Logger::log(std::string message)
{
  fprintf(this->fileDescriptor, "%s\n", message.c_str());
}

/**
 * By default, flushes the log in the standard output.
 */
Logger::Logger(int fileDescriptor)
{
  FILE *file = fdopen(fileDescriptor, "w");
  this->fileDescriptor = file;
}

void Logger::info(std::string message)
{
  std::string logMessage = formatLogMessage(message, INFO);
  this->log(logMessage.c_str());
}

void Logger::warning(std::string message)
{
  std::string logMessage = formatLogMessage(message, WARNING);
  this->log(logMessage.c_str());
}

void Logger::error(std::string message)
{
  std::string logMessage = formatLogMessage(message, ERROR);
  this->log(logMessage.c_str());
}

void Logger::debug(std::string message)
{
  std::string logMessage = formatLogMessage(message, DEBUG);
  this->log(logMessage.c_str());
}

/**
 * When we destroy an object, we always need to destroy all its properties. In this case, the file should be closed for safety.
 */
Logger::~Logger()
{
  fclose(this->fileDescriptor);
}
