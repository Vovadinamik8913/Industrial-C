#include <libregex/matcher.hpp>

bool libregex::matcher::full_match(const std::string &input) {
  std::shared_ptr<regex_node> current = this->ast;
  size_t pos = 0;
  while (current != nullptr) {
    if (!(*current).match(input, pos)) {
      return false;
    }
    current = (*current).get_next();
  }
  if (pos < input.size()) {
    return false;
  }
  return true;
}