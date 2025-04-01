#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <libregex/parser.hpp>
#include <string.h>

TEST(ParserTest, ParserThrowTest) {
  libregex::parser parser("!$235^");
  ASSERT_THROW(parser.parse(), std::runtime_error);
}

TEST(ParserTest, ParserNotThrowTest) {
  libregex::parser parser("a*[abc]");
  ASSERT_NO_THROW(parser.parse());
}