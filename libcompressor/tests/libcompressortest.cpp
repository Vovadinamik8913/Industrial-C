#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string.h>

#include <libcompressor/libcompressor.hpp>

TEST(TestGroupName, NotEmptyTest) {
  libcompressor_Buffer buf;
  buf.data = strdup("test");
  buf.size = strlen(buf.data);
  libcompressor_Buffer res = libcompressor_compress(libcompressor_Zlib, buf);
  ASSERT_TRUE(res.size != 0);
}

TEST(TestGroupName, EmptyTest) {
  libcompressor_Buffer buf;
  buf.data = NULL;
  buf.size = 0;
  libcompressor_Buffer res = libcompressor_compress(libcompressor_Zlib, buf);
  ASSERT_FALSE(res.size != 0);
}

TEST(TestGroupName, ZlibTest) {
  libcompressor_Buffer buf;
  buf.data = strdup("test_string");
  buf.size = strlen(buf.data);
  libcompressor_Buffer res = libcompressor_compress(libcompressor_Zlib, buf);
  char testres[] = {
      static_cast<char>(0x78), static_cast<char>(0x9c), static_cast<char>(0x2b), static_cast<char>(0x49),
      static_cast<char>(0x2d), static_cast<char>(0x2e), static_cast<char>(0x89), static_cast<char>(0x2f),
      static_cast<char>(0x2e), static_cast<char>(0x29), static_cast<char>(0xca), static_cast<char>(0xcc),
      static_cast<char>(0x4b), static_cast<char>(0x07), static_cast<char>(0x00), static_cast<char>(0x1c),
      static_cast<char>(0x79), static_cast<char>(0x04), static_cast<char>(0xb7),
  };
  ASSERT_TRUE(res.data != NULL);
  ASSERT_TRUE(strcmp(res.data, testres) == 0);
}

TEST(TestGroupName, BzipTest) {
  libcompressor_Buffer buf;
  buf.data = strdup("test_string");
  buf.size = strlen(buf.data);
  libcompressor_Buffer res = libcompressor_compress(libcompressor_Bzip, buf);
  char testres[] = {
      static_cast<char>(0x42), static_cast<char>(0x5a), static_cast<char>(0x68), static_cast<char>(0x31),
      static_cast<char>(0x31), static_cast<char>(0x41), static_cast<char>(0x59), static_cast<char>(0x26),
      static_cast<char>(0x53), static_cast<char>(0x59), static_cast<char>(0x4a), static_cast<char>(0x7c),
      static_cast<char>(0x69), static_cast<char>(0x05), static_cast<char>(0x00), static_cast<char>(0x00),
      static_cast<char>(0x04), static_cast<char>(0x83), static_cast<char>(0x80), static_cast<char>(0x00),
      static_cast<char>(0x00), static_cast<char>(0x82), static_cast<char>(0xa1), static_cast<char>(0x1c),
      static_cast<char>(0x00), static_cast<char>(0x20), static_cast<char>(0x00), static_cast<char>(0x22),
      static_cast<char>(0x03), static_cast<char>(0x68), static_cast<char>(0x84), static_cast<char>(0x30),
      static_cast<char>(0x22), static_cast<char>(0x50), static_cast<char>(0xdf), static_cast<char>(0x04),
      static_cast<char>(0x99), static_cast<char>(0xe2), static_cast<char>(0xee), static_cast<char>(0x48),
      static_cast<char>(0xa7), static_cast<char>(0x0a), static_cast<char>(0x12), static_cast<char>(0x09),
      static_cast<char>(0x4f), static_cast<char>(0x8d), static_cast<char>(0x20), static_cast<char>(0xa0),
  };
  ASSERT_TRUE(strcmp(res.data, testres) == 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}