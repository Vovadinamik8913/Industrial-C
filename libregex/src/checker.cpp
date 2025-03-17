#include <algorithm>
#include <libregex/checker.hpp>

const std::vector<char> &libregex::checker::get_allowed_chars() {
  static const std::vector<char> instance = generate_allowed_chars();
  return instance;
}

std::vector<char> libregex::checker::generate_allowed_chars() {
  std::vector<char> chars;
  for (char c = 'a'; c <= 'z'; ++c) {
    chars.push_back(c);
  }
  for (char c = 'A'; c <= 'Z'; ++c) {
    chars.push_back(c);
  }
  for (char c = '0'; c <= '9'; ++c) {
    chars.push_back(c);
  }
  chars.push_back(' ');
  return chars;
}

bool libregex::checker::allowed(char sym) {
  std::vector<char> chars = get_allowed_chars();
  return std::find(chars.begin(), chars.end(), sym) != chars.end();
}

bool libregex::checker::pattern_allowed(char sym) {
  std::vector<char> chars = get_allowed_chars();
  chars.push_back('-');
  chars.push_back('.');
  chars.push_back('*');
  chars.push_back('+');
  chars.push_back('?');
  chars.push_back('[');
  chars.push_back(']');
  return std::find(chars.begin(), chars.end(), sym) != chars.end();
}
