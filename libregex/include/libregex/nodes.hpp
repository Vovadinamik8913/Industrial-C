#pragma once
#include <memory>
#include <string>
#include <vector>

namespace libregex {
/// @brief abstract node of regexp
class regex_node {
 protected:
  std::shared_ptr<regex_node> next;

 public:
  regex_node() : next{nullptr} {}
  /// @brief get next
  /// @return ptr to next node
  std::shared_ptr<regex_node> get_next();
  /// @brief set next
  /// @param next next node
  void set_next(const std::shared_ptr<regex_node> &next);
  virtual ~regex_node() = default;
  /// @brief match symbol to node
  /// @param  string string to match
  /// @param  pos current position
  /// @return true or false
  virtual bool match(const std::string &, size_t &) const = 0;
};

/// @brief node for chars (a-b, A-B, 0-9, " ")
class char_node : public regex_node {
  char ch;

 public:
  explicit char_node(char c) : ch(c) {}
  bool match(const std::string &, size_t &) const override;
};

/// @brief node for .
class dot_node : public regex_node {
 public:
  bool match(const std::string &, size_t &) const override;
};

/// @brief node for groups ([abc], [a-g])
class group_node : public regex_node {
  std::vector<char> chars;

 public:
  explicit group_node(const std::vector<char> &chars) : chars(chars) {}
  bool match(const std::string &, size_t &) const override;
};

/// @brief node for modifier(*,+,?) for prev node
class modifier_node : public regex_node {
  std::shared_ptr<regex_node> child;
  char modifier;

 public:
  explicit modifier_node(const std::shared_ptr<regex_node> &child, char mod)
      : child(child), modifier(mod) {}
  bool match(const std::string &, size_t &) const override;
};
} // namespace libregex