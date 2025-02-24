#include <spdlog/spdlog.h>
#include <cstdlib>
#include <libcompressor/libcompressor.hpp>

int main(int argc, char** argv) {
  if (argc < 3) {
    spdlog::error("not enough arguments");
    return EXIT_FAILURE;
  }
  libcompressor_Buffer buf;
  buf.data = argv[2];
  buf.size = strlen(argv[2]);
  libcompressor_Buffer res;
  if (strcmp(argv[1], "zlib") == 0) {
    res = libcompressor_compress(libcompressor_Zlib, buf);
  } else if (strcmp(argv[1], "bzip") == 0) {
    res = libcompressor_compress(libcompressor_Bzip, buf);
  } else {
    spdlog::error("no such algorithm");
    return EXIT_FAILURE;
  }

  if (res.size == 0) {
    spdlog::error("compress failed");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < res.size; i++) {
    std::printf("%0.2hhx", res.data[i]);
  }
  std::printf("\n");
  std::free(res.data);

  return EXIT_SUCCESS;
}