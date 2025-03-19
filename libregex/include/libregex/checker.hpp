#pragma once
#include <string_view>
#include <vector>

namespace libregex {
/// @brief class for cecking allowed symbols in pattern and input
class checker {
  /// @brief allowed symbols
  static const std::string_view allowed_chars;
  /// @brief allowed symbols for pattern
  static const std::string_view pattern_allowed_chars;

 public:
  /**
   * @brief is symbol allowed?
   *
   * @param sym symbol
   * @return true or false
   */
  static bool allowed(char);
  /**
   * @brief is symbol allowed for pattern?
   *
   * @param sym symbol
   * @return true or false
   */
  static bool pattern_allowed(char);
};
} // namespace libregex