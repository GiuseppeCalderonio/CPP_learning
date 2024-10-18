#ifndef LOGGER_H
#define LOGGER_H
#include <string>

enum LogLevel
{
  INFO,
  WARNING,
  ERROR,
  DEBUG
};

class Logger
{

  /**
   * By default, flushes the log in the standard output.
   */
public:
  Logger(int fileDescriptor = STDOUT_FILENO);
  void info(std::string message);
  void warning(std::string message);
  void error(std::string message);
  void debug(std::string message);
  ~Logger();

private:
  FILE *fileDescriptor;
  /**
   * Helper function to get the current timestamp used for log formatting
   */
  std::string getCurrentISOTimestampString();
  std::string formatLogMessage(std::string message, const int level);
  std::string logLevelToString(const int level);
  void log(std::string message);
};

#endif