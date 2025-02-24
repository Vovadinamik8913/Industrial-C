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
  libcompressor_Buffer result_buffer = {NULL, 0};

  result_buffer.data = (char*)malloc(input.size + 1024);
  z_stream data;
  data.zalloc = Z_NULL;
  data.zfree = Z_NULL;
  data.opaque = Z_NULL;
  
  if (deflateInit(&data, Z_DEFAULT_COMPRESSION) != Z_OK) {
      result_buffer.data = NULL;
      result_buffer.size = 0;
      return result_buffer;
  }
  result_buffer.size = deflateBound(&data, input.size);
  
  data.avail_in = input.size;
  data.next_in = (Bytef*)input.data;
  data.avail_out = result_buffer.size;
  data.next_out = (Bytef*)result_buffer.data;
  if (deflate(&data, Z_FINISH) != Z_STREAM_END) {
      free(result_buffer.data);
      deflateEnd(&data);
      result_buffer.size = 0;
      return result_buffer;
  }
  result_buffer.size = data.total_out;
  deflateEnd(&data);
  return result_buffer;
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