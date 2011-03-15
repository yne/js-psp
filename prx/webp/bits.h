// Copyright 2010 Google Inc.
//
// This code is licensed under the same terms as WebM:
//  Software License Agreement:  http://www.webmproject.org/license/software/
//  Additional IP Rights Grant:  http://www.webmproject.org/license/additional/
// -----------------------------------------------------------------------------
//
// Boolean decoder
//
// Author: Skal (pascal.massimino@gmail.com)

#ifndef WEBP_DEC_BITS_H_
#define WEBP_DEC_BITS_H_

#include <assert.h>
#include "webp/decode_vp8.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Bitreader and code-tree reader

typedef struct {
  const uint8_t* buf_;        // next byte to be read
  const uint8_t* buf_end_;    // end of read buffer
  int eof_;                   // true if input is exhausted

  // boolean decoder
  uint32_t range_;            // current range minus 1. In [127, 254] interval.
  uint32_t value_;            // current value
  int left_;                  // how many unused bits (negated)
} VP8BitReader;

// Initialize the bit reader and the boolean decoder.
void VP8Init(VP8BitReader* const br, const uint8_t* buf, uint32_t size);

// return the next value made of 'num_bits' bits
uint32_t VP8GetValue(VP8BitReader* const br, int num_bits);
static inline uint32_t VP8Get(VP8BitReader* const br) {
  return VP8GetValue(br, 1);
}

// return the next value with sign-extension.
int32_t VP8GetSignedValue(VP8BitReader* const br, int num_bits);

// Read a bit with proba 'prob'. Speed-critical function!
extern const uint8_t kVP8Log2Range[128];
extern const uint8_t kVP8NewRange[128];
static inline uint32_t VP8GetByte(VP8BitReader* const br) {
  assert(br);
  if (br->buf_ < br->buf_end_) {
    assert(br->buf_);
    return *br->buf_++;
  }
  br->eof_ = 1;
  return 0x80;
}

static inline void VP8Shift(VP8BitReader* const br) {
  // range_ is in [0..127] interval here.
  const int shift = kVP8Log2Range[br->range_];
  br->range_ = kVP8NewRange[br->range_];
  br->value_ <<= shift;
  br->left_ += shift;
  if (br->left_ > 0) {
    br->value_ |= VP8GetByte(br) << br->left_;
    br->left_ -= 8;
  }
}

static inline uint32_t VP8GetBit(VP8BitReader* const br, int prob) {
  const uint32_t split = (br->range_ * prob) >> 8;
  const uint32_t bit = ((br->value_ >> 8) > split);
  if (bit) {
    br->range_ -= split + 1;
    br->value_ -= (split + 1) << 8;
  } else {
    br->range_ = split;
  }
  if (br->range_ < 0x7f) {
    VP8Shift(br);
  }
  return bit;
}

static inline int VP8GetSigned(VP8BitReader* const br, int v) {
  const uint32_t split = br->range_ >> 1;
  const uint32_t bit = ((br->value_ >> 8) > split);
  if (bit) {
    br->range_ -= split + 1;
    br->value_ -= (split + 1) << 8;
    v = -v;
  } else {
    br->range_ = split;
  }
  VP8Shift(br);
  return v;
}

#if defined(__cplusplus) || defined(c_plusplus)
}    // extern "C"
#endif

#endif  // WEBP_DEC_BITS_H_
