#include <algorithm>
#include <libregex/checker.hpp>
#include <libregex/parser.hpp>
#include <memory>
#include <stdexcept>

std::shared_ptr<libregex::regex_node> libregex::parser::parse_char() {
  if (pattern[pos] == '.') {
    pos++;
    return std::make_shared<dot_node>(dot_node());
  }
  if (!checker::allowed(pattern[pos])) {
    throw std::runtime_error("Invalid pattern syntax");
  }

  return std::make_shared<char_node>(char_node(pattern[pos++]));
}

std::shared_ptr<libregex::regex_node> libregex::parser::parse_modifier(
    const std::shared_ptr<libregex::regex_node> &prev) {
  if (pos == 0) {
    throw std::runtime_error("Invalid modifier syntax");
  }
  if (pattern[pos + 1] == '*' || pattern[pos + 1] == '?' ||
      pattern[pos + 1] == '+') {
    throw std::runtime_error("Invalid modifier syntax");
  }
  return std::make_shared<modifier_node>(modifier_node(prev, pattern[pos++]));
}

std::vector<char> libregex::parser::parse_group_chars() {
  std::vector<char> chars;
  while (pos < pattern.size() && pattern[pos] != ']') {
    if (pattern[pos] == '-' || !checker::pattern_allowed(pattern[pos])) {
      throw std::runtime_error("Invalid group syntax");
    }
    if (pos + 1 < pattern.size() && pattern[pos + 1] == '-') {
      if (pos + 2 >= pattern.size() ||
          !checker::pattern_allowed(pattern[pos + 2]) ||
          pattern[pos + 2] == '-') {
        throw std::runtime_error("Invalid range");
      }
      for (char c = pattern[pos]; c <= pattern[pos + 2]; ++c) {
        if (std::find(chars.begin(), chars.end(), c) != chars.end()) {
          continue;
        }
        chars.push_back(c);
      }
      pos += 3;
    } else {
      if (std::find(chars.begin(), chars.end(), pattern[pos]) != chars.end()) {
        pos++;
        continue;
      }
      chars.push_back(pattern[pos++]);
    }
  }
  if (pos >= pattern.size() && pattern[pos - 1] != ']') {
    throw std::runtime_error("Invalid group syntax");
  }
  pos++;
  return chars;
}

std::shared_ptr<libregex::regex_node> libregex::parser::parse_group() {
  return std::make_shared<group_node>(group_node(parse_group_chars()));
}

std::shared_ptr<libregex::regex_node> libregex::parser::parse() {
  std::shared_ptr<regex_node> head = nullptr;
  std::shared_ptr<regex_node> tail = nullptr;
  while (pos < pattern.size()) {
    std::shared_ptr<regex_node> node = nullptr;
    if (!checker::pattern_allowed(pattern[pos])) {
      throw std::runtime_error("Pattern contains not allowed symbol");
    }
    if (pattern[pos] == '[') {
      pos++;
      node = parse_group();
    } else {
      node = parse_char();
    }
    if (pos < pattern.size()) {
      if (pattern[pos] == '*' || pattern[pos] == '?' || pattern[pos] == '+') {
        node = parse_modifier(node);
      }
    }

    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      if (head == tail) {
        head->set_next(node);
        tail = node;
      } else {
        tail->set_next(node);
        tail = node;
      }
    }
  }
  return head;
}
