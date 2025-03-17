#pragma once
#include <libregex/nodes.hpp>

namespace libregex {
/// @brief class for mathcing strings
class matcher {
  /// @brief tree by pattern
  std::shared_ptr<regex_node> ast;

 public:
  /// @brief init matcher ast
  /// @param head ast start
  explicit matcher(std::shared_ptr<regex_node> head) : ast{head} {}
  /// @brief is word matching pattern
  /// @param  string input
  /// @return true or false
  bool full_match(const std::string &);
};
} // namespace libregex