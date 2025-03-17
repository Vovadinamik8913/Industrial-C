#include <algorithm>
#include <libregex/checker.hpp>
#include <libregex/exception.hpp>
#include <libregex/nodes.hpp>

std::shared_ptr<libregex::regex_node> libregex::regex_node::get_next() {
  return this->next;
}

void libregex::regex_node::set_next(std::shared_ptr<regex_node> next) {
  this->next = next;
}

bool libregex::char_node::match(const std::string &input, size_t &pos) const {
  if (pos < input.size()) {
    if (!checker::allowed(input[pos])) {
      throw regex_exception(
          std::to_string(input[pos]) +
          " is not allowed at position: " + std::to_string(pos));
    }
    if (input[pos] == this->ch) {
      pos++;
      return true;
    }
  }
  return false;
}

bool libregex::dot_node::match(const std::string &input, size_t &pos) const {
  if (pos < input.size()) {
    char sym = input[pos++];
    if (!checker::allowed(sym)) {
      throw regex_exception("String contains not allowed symbol");
    }
    return true;
  }
  return false;
}

bool libregex::group_node::match(const std::string &input, size_t &pos) const {
  if (pos < input.size()) {
    if (!checker::allowed(input[pos])) {
      throw regex_exception("String contains not allowed symbol");
    }
    if (std::find(chars.begin(), chars.end(), input[pos]) != chars.end()) {
      pos++;
      return true;
    }
  }
  return false;
}

bool libregex::modifier_node::match(const std::string &input,
                                    size_t &pos) const {
  size_t count = 0;
  if (modifier == '*') {
    while (pos < input.size()) {
      size_t prev_pos = pos;
      if (!child->match(input, pos)) {
        break;
      }
      if (prev_pos == pos) {
        break;
      }
      count++;
    }
    return true;
  } else if (modifier == '+') {
    while (pos < input.size()) {
      size_t prev_pos = pos;
      if (!child->match(input, pos)) {
        break;
      }
      if (prev_pos == pos) {
        break;
      }
      count++;
    }
    return count > 0;
  } else if (modifier == '?') {
    child->match(input, pos);
    return true;
  }
  return false;
}
