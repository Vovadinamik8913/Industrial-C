#include <bzlib.h>
#include <zlib.h>
#include <cstddef>
#include <cstdlib>
#include <libcompressor/libcompressor.hpp>

/**
 * @brief compressing by zlib
 *
 * @param input data
 * @return compressed input or empty
 */
libcompressor_Buffer z_compress(libcompressor_Buffer input) {
  libcompressor_Buffer res = {NULL, 0};
  res.data = (char*)std::malloc(input.size + 1024);
  z_stream data;
  data.zalloc = Z_NULL;
  data.zfree = Z_NULL;
  data.opaque = Z_NULL;

  if (deflateInit(&data, Z_DEFAULT_COMPRESSION) != Z_OK) {
    free(res.data);
    res.data = NULL;
    res.size = 0;
    return res;
  }

  data.avail_in = input.size;
  data.next_in = (Bytef*)input.data;
  data.avail_out = res.size;
  data.next_out = (Bytef*)res.data;

  if (deflate(&data, Z_FINISH) != Z_STREAM_END) {
    free(res.data);
    deflateEnd(&data);
    res.size = 0;
    res.data = NULL;
    return res;
  }

  fprintf(stderr, "Failed to compress data 4\n");
  res.size = data.total_out;
  deflateEnd(&data);
  return res;
}

/**
 * @brief compressing by bzlib
 *
 * @param input data
 * @return compressed input or empty
 */
libcompressor_Buffer b_compress(libcompressor_Buffer input) {
  libcompressor_Buffer res = {NULL, 0};
  res.data = (char*)std::malloc(input.size + 1024);
  if (!res.data) return res;
  res.size = input.size + 1024;

  int rc = BZ2_bzBuffToBuffCompress(res.data, (unsigned int*)&res.size, input.data, input.size, 1, 0, 0);
  if (rc != BZ_OK) {
    std::free(res.data);
    res.data = NULL;
    return res;
  }
  return res;
}

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
  libcompressor_Buffer res = {NULL, 0};
  if (!input.data || !input.size) {
    return res;
  }

  switch (algo) {
    case libcompressor_Zlib:
      return z_compress(input);
    case libcompressor_Bzip:
      return b_compress(input);
    default:
      return res;
  }
}