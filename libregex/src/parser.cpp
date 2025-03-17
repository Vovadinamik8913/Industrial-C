#include <libregex/checker.hpp>
#include <libregex/exception.hpp>
#include <libregex/parser.hpp>
#include <memory>

std::shared_ptr<libregex::regex_node> libregex::parser::parse_char() {
  if (pattern[pos] == '.') {
    pos++;
    return std::shared_ptr(std::make_shared<dot_node>(dot_node()));
  }
  return std::shared_ptr(
      std::make_shared<char_node>(char_node(pattern[pos++])));
}

std::shared_ptr<libregex::regex_node>
libregex::parser::parse_modifier(std::shared_ptr<libregex::regex_node> prev) {
  if (pos == 0) {
    throw regex_exception("Invalid modifier syntax");
  }
  if (pattern[pos - 1] == '*' || pattern[pos - 1] == '?' ||
      pattern[pos - 1] == '+') {
    throw regex_exception("Invalid modifier syntax");
  }
  return std::shared_ptr(
      std::make_shared<modifier_node>(modifier_node(prev, pattern[pos++])));
}

std::vector<char> libregex::parser::parse_group_chars() {
  std::vector<char> chars;
  while (pos < pattern.size() && pattern[pos] != ']') {
    if (pattern[pos] == '-') {
      throw regex_exception("Invalid group syntax");
    }
    if (pos + 1 < pattern.size() && pattern[pos + 1] == '-') {
      if (pos + 2 >= pattern.size())
        throw regex_exception("Invalid range");
      for (char c = pattern[pos]; c <= pattern[pos + 2]; ++c) {
        chars.push_back(c);
      }
      pos += 3;
    } else {
      chars.push_back(pattern[pos++]);
    }
  }
  if (pos >= pattern.size() && pattern[pos - 1] != ']') {
    throw regex_exception("Invalid group syntax");
  }
  pos++;
  return chars;
}

std::shared_ptr<libregex::regex_node> libregex::parser::parse_group() {
  ;
  return std::shared_ptr(
      std::make_shared<group_node>(group_node(parse_group_chars())));
}

std::shared_ptr<libregex::regex_node> libregex::parser::parse() {
  std::shared_ptr<regex_node> head = nullptr;
  std::shared_ptr<regex_node> tail = nullptr;
  while (pos < pattern.size()) {
    std::shared_ptr<regex_node> node = nullptr;
    if (!checker::pattern_allowed(pattern[pos])) {
      throw regex_exception("Pattern contains not allowed symbol");
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
        (*head).set_next(node);
        tail = node;
      } else {
        (*tail).set_next(node);
        tail = node;
      }
    }
  }
  return head;
}
