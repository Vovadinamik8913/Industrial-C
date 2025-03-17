#pragma once
#include <vector>

namespace libregex {
/// @brief class for cecking allowed symbols in pattern and input
class checker {
  /**
   * @brief Get the allowed chars object
   *
   * @return allowed chars
   */
  static const std::vector<char> &get_allowed_chars();
  /**
   * @brief generate allowed chars
   *
   * @return allowed char
   */
  static std::vector<char> generate_allowed_chars();

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