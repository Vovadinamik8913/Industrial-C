#pragma once
#include <string>

namespace libregex {
/// @brief own exception realisation
class regex_exception : public std::exception {
  std::string message;

 public:
  /// @brief constructor by message
  /// @param message message
  regex_exception(const std::string &message) : message{message} {}
  /// @brief return exception message
  /// @return exception
  const char *what() const noexcept override { return message.c_str(); }
};
} // namespace libregex
