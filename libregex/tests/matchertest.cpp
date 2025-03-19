#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <libregex/matcher.hpp>
#include <libregex/parser.hpp>
#include <string.h>

#pragma region char
TEST(MatcherTest, CharTrueTest) {
  libregex::parser parser("a");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("a"));
}

TEST(MatcherTest, CharFalseTest) {
  libregex::parser parser("a");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match("b"));
}
#pragma endregion

#pragma region dot
TEST(MatcherTest, DotTrueTest) {
  libregex::parser parser(".");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("a"));
}
#pragma endregion

#pragma region star_modifier
TEST(MatcherTest, StarTrueTest) {
  libregex::parser parser("a*");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("aaaaaaa"));
}

TEST(MatcherTest, StarEmptyTest) {
  libregex::parser parser("a*");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match(""));
}

TEST(MatcherTest, StarSymbolFalseTest) {
  libregex::parser parser("a*a");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match("aaaaaaa"));
}

TEST(MatcherTest, StarFalseTest) {
  libregex::parser parser("a*");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match("ab"));
}
#pragma endregion

#pragma region plus_modifier
TEST(MatcherTest, PlusTrueTest) {
  libregex::parser parser("a+");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("aaaaaaa"));
}

TEST(MatcherTest, PlusEmptyTest) {
  libregex::parser parser("a+");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match(""));
}
#pragma endregion

#pragma region question_modifier
TEST(MatcherTest, QuestuionTrueTest) {
  libregex::parser parser("a?");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("a"));
}

TEST(MatcherTest, QuestuionLazyTrueTest) {
  libregex::parser parser("a?a");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match("a"));
}

TEST(MatcherTest, QuestionEmptyTest) {
  libregex::parser parser("a?");
  libregex::matcher matcher(parser.parse());
  ASSERT_TRUE(matcher.full_match(""));
}

TEST(MatcherTest, QuestuionFlaseTest) {
  libregex::parser parser("a?");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match("aaaaaaa"));
}
#pragma endregion

#pragma region group
TEST(MatcherTest, GroupTrueTest) {
  libregex::parser parser("[abc]");
  libregex::matcher matcher(parser.parse());
  EXPECT_TRUE(matcher.full_match("b"));
  EXPECT_TRUE(matcher.full_match("c"));
  ASSERT_TRUE(matcher.full_match("a"));
}

TEST(MatcherTest, GroupSlashTest) {
  libregex::parser parser("[a-d]");
  libregex::matcher matcher(parser.parse());
  EXPECT_TRUE(matcher.full_match("d"));
  EXPECT_TRUE(matcher.full_match("b"));
  EXPECT_TRUE(matcher.full_match("c"));
  ASSERT_TRUE(matcher.full_match("a"));
}

TEST(MatcherTest, GroupFlaseTest) {
  libregex::parser parser("[a-d]");
  libregex::matcher matcher(parser.parse());
  ASSERT_FALSE(matcher.full_match("x"));
}
#pragma endregion

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}