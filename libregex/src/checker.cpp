#include <algorithm>
#include <libregex/checker.hpp>
#include <string_view>

const std::string_view libregex::checker::allowed_chars =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

const std::string_view libregex::checker::pattern_allowed_chars =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .-*+?[]";

bool libregex::checker::allowed(char sym) {
  return allowed_chars.find(sym) != std::string_view::npos;
}

bool libregex::checker::pattern_allowed(char sym) {
  return pattern_allowed_chars.find(sym) != std::string_view::npos;
}
