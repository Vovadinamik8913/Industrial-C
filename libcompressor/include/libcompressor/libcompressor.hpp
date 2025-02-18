#pragma once

/**
 * @brief algorithm for compressing
 *
 */
enum libcompressor_CompressionAlgorithm { libcompressor_Zlib, libcompressor_Bzip };

/**
 * @brief data
 *
 */
struct libcompressor_Buffer {
  char* data;
  int size;
};

/**
 * @brief compress input by choosen algorithm
 *
 * @param algo algorithm
 * @param input input data
 * @return compressed input or empty
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);