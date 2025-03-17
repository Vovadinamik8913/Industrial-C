#pragma once
#include <libregex/nodes.hpp>
#include <vector>

namespace libregex {
/// @brief parsing regex pattern
class parser {
  std::string pattern;
  size_t pos;
  /// @brief parse char(a-b, 0-9, .)
  /// @return char_node or dor_node
  std::shared_ptr<regex_node> parse_char();
  /// @brief parse (*, ?, +)
  /// @param prev previous node to modify
  /// @return modifier_node
  std::shared_ptr<regex_node> parse_modifier(std::shared_ptr<regex_node> prev);
  /// @brief parsing ([abc], [a-g])
  /// @return group_node
  std::shared_ptr<regex_node> parse_group();
  /// @brief get chars from group
  /// @return chars from group
  std::vector<char> parse_group_chars();

 public:
  /// @brief set pattern
  /// @param pattern pattern
  explicit parser(const std::string &pattern) : pattern{pattern}, pos{0} {}
  /// @brief get ast by pattern
  /// @return ast
  std::shared_ptr<regex_node> parse();
};
} // namespace libregex