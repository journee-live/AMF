/*
 * Musepack SV8 decoder
 * Copyright (c) 2007 Konstantin Shishkov
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_MPC8HUFF_H
#define AVCODEC_MPC8HUFF_H

#include <stdint.h>

#define MPC8_MAX_VLC_SIZE 256

#define MPC8_BANDS_SIZE 33
#define MPC8_BANDS_BITS 9

static const uint8_t mpc8_bands_syms[MPC8_BANDS_SIZE] = {
    13, 19, 10, 11, 12, 14, 15, 16, 17, 18, 20, 21, 22,  9, 23, 24, 25,  8, 26,
    27,  7, 28,  5,  6, 29,  4,  3, 30,  2, 31,  1, 32,  0
};
static const uint8_t mpc8_bands_len_counts[16] = {
    1,  1,  1,  0,  2,  2,  1,  3,  2,  3,  4, 11,  2,  0,  0,  0
};

static const uint8_t mpc8_scfi_syms[] = {
    /* SCFI[0] VLC symbols - 4 entries */
    0,  1,  3,  2,
    /* SCFI[1] VLC symbols - 16 entries */
    1,  4,  0,  2,  3,  8, 12,  5,  6,  7,  9, 13, 11, 14, 10, 15
};

static const uint8_t mpc8_scfi_len_counts[2][16] = {
    {  1,  1,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0  },
    {  0,  2,  2,  0,  5,  5,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0  },
};

#define MPC8_DSCF0_BITS 9
#define MPC8_DSCF1_BITS 9

static const uint8_t mpc8_dscf_syms[] = {
    /* DSCF[0] VLC symbols - 64 entries */
    58, 59, 60, 61, 62, 63, 55, 56, 57,  0,  1,  2, 53, 54,  3,  4,  5, 50, 51,
    52,  6,  7,  8,  9, 10, 31, 47, 48, 49, 11, 12, 13, 14, 44, 45, 46, 15, 16,
    17, 18, 41, 42, 43, 19, 20, 21, 22, 40, 23, 24, 38, 39, 25, 28, 37, 26, 27,
    29, 30, 32, 36, 33, 34, 35,
    /* DSCF[1] VLC symbols - 65 entries */
     0, 59, 60, 61, 62, 63,  1,  2, 56, 57, 58,  3,  4,  5, 53, 54, 55,  6,  7,
     8,  9, 49, 50, 51, 52, 64, 10, 11, 12, 13, 46, 47, 48, 14, 15, 16, 17, 43,
    44, 45, 18, 19, 20, 41, 42, 21, 22, 39, 40, 23, 24, 38, 25, 37, 26, 35, 36,
    27, 28, 34, 29, 30, 31, 32, 33,
};

static const uint8_t mpc8_dscf_len_counts[2][16] = {
    {  0,  0,  3,  6,  3,  4,  5,  7,  7,  9,  6,  5,  3,  6,  0,  0  },
    {  0,  0,  5,  3,  3,  2,  3,  4,  5,  7,  7,  9,  6,  5,  6,  0  },
};

#define MPC8_RES_BITS 9

static const uint8_t mpc8_res_syms[] = {
    /* RES[0] VLC symbols - 17 entries */
    13, 14, 12, 11, 10,  9,  8,  7,  6, 15,  5,  4,  3,  2, 16,  1,  0,
    /* RES[1] VLC symbols - 17 entries */
     8,  9, 10, 11,  7, 12,  6, 13,  5,  4, 14,  3, 15,  2,  0,  1, 16,
};

static const uint8_t mpc8_res_len_counts[2][16] = {
    {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2  },
    {  0,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  4,  0,  0  },
};

#define MPC8_Q1_BITS 9

static const uint8_t mpc8_q1_len_counts[16] = {
    0,  0,  5,  5,  1,  1,  1,  1,  1,  1,  1,  2,  0,  0,  0,  0
};

#define MPC8_Q9UP_BITS 9

static const uint8_t mpc8_q9up_len_counts[16] = {
    0,  0,  0,  0,  0,  2, 38, 134, 71,  9,  2,  0,  0,  0,  0,  0
};

#define MPC8_Q2_BITS 9

static const uint8_t mpc8_q2_len_counts[2][16] = {
    {  0,  0,  1,  6,  0, 17,  9, 24, 24,  9, 27,  4,  4,  0,  0,  0  },
    {  0,  0,  0,  1, 16, 10,  6, 48,  9, 27,  4,  4,  0,  0,  0,  0  },
};

#define MPC8_Q3_BITS 9
#define MPC8_Q4_BITS 9

static const uint8_t mpc8_q34_len_counts[2][16] = {
    {  0,  0,  1,  6,  6, 11, 13,  8,  4,  0,  0,  0,  0,  0,  0,  0  },
    {  0,  0,  0,  1, 12, 23, 14, 19,  8,  4,  0,  0,  0,  0,  0,  0  },
};

static const uint8_t mpc8_q5_8_len_counts[2][4][16] = {
    { /* Q5[0], Q6[0], Q7[0], Q8[0] */
        {  0,  1,  4,  2,  2,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0  },
        {  0,  1,  2,  4,  3,  7,  2,  4,  8,  0,  0,  0,  0,  0,  0,  0  },
        {  0,  1,  2,  2,  4,  6, 10, 10, 12, 16,  0,  0,  0,  0,  0,  0  },
        {  0,  1,  2,  1,  3,  8,  8, 15, 24, 42, 17,  6,  0,  0,  0,  0  },
    },
    { /* Q5[1], Q6[1], Q7[1], Q8[1] */
        {  0,  0,  5,  4,  2,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0  },
        {  0,  0,  0, 11,  6,  4,  6,  4,  0,  0,  0,  0,  0,  0,  0,  0  },
        {  0,  0,  0,  0, 20, 15, 10, 14,  4,  0,  0,  0,  0,  0,  0,  0  },
        {  0,  0,  0,  0,  0, 26, 55, 38,  8,  0,  0,  0,  0,  0,  0,  0  },
    }
};

static const uint8_t mpc8_q_syms[] = {
     /* Q1 VLC symbols - 19 entries */
     17,  18,  16,  15,  14,  13,  12,   0,  11,   1,   2,   8,   9,  10,   3,
      4,   5,   6,   7,
     /* Q9UP VLC symbols - 256 entries */
    254, 255,   0,   1,   2,   3,   4, 250, 251, 252, 253,   5,   6,   7,   8,
      9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  21,  22,  23,  24,  25,
     26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  41,
    213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227,
    228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
    243, 244, 245, 246, 247, 248, 249,  19,  20,  40,  42,  43,  44,  45,  46,
     47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,
     62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,
     77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,
     92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 147, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161,
    162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176,
    177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
    192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206,
    207, 208, 209, 210, 211, 212, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 129, 130, 131, 132, 133,
    134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 148, 127,
    128,
     /* Q2[0] VLC symbols - 125 entries */
      4,  24, 100, 120,   0,  20, 104, 124,   1,   3,   5,   9,  10,  14,  15,
     19,  21,  23,  25,  29,  45,  49,  75,  79,  95,  99, 101, 103, 105, 109,
    114, 115, 119, 121, 123,   2,  22,  50,  54,  70,  74, 102, 110, 122,   6,
      8,  16,  18,  26,  28,  30,  34,  40,  44,  46,  48,  76,  78,  80,  84,
     90,  94,  96,  98, 106, 108, 116, 118,   7,  11,  13,  17,  27,  35,  39,
     47,  51,  53,  55,  59,  65,  69,  71,  73,  77,  85,  89,  97, 107, 111,
    113, 117,  12,  33,  43,  52,  60,  64,  72,  91, 112,  31,  32,  36,  38,
     41,  42,  56,  58,  66,  68,  81,  82,  83,  86,  88,  92,  93,  37,  57,
     61,  63,  67,  87,  62,
     /* Q3 VLC symbols - 49 entries */
     13,   3, 109,  99,  14,   2,  29,  19,  93,  83, 110,  98,  15,   0,   1,
     18,  45,  35,  61,  51,  77,  67, 111,  96,  97,  30,  31,  17,  46,  34,
     78,  66,  94,  95,  81,  82,  16,  33,  62,  50,  79,  80,  47,  32,  63,
     49,  64,  65,  48,
     /* Q5[0] VLC symbols - 15 entries */
      0,   1,  13,  14,   2,  12,   3,  11,   4,  10,   5,   6,   8,   9,   7,
     /* Q6[0] VLC symbols - 31 entries */
      0,   1,   2,   3,  27,  28,  29,  30,   4,   5,  25,  26,   6,  24,   7,
      8,   9,  20,  21,  22,  23,  10,  11,  19,  12,  13,  17,  18,  14,  16,
     15,
     /* Q7[0] VLC symbols - 63 entries */
      0,   1,   2,   5,   6,   7,   8,   9,  53,  54,  55,  56,  57,  60,  61,
     62,   3,   4,  10,  11,  12,  13,  49,  50,  51,  52,  58,  59,  14,  15,
     16,  17,  18,  43,  45,  46,  47,  48,  19,  20,  21,  22,  23,  39,  40,
     41,  42,  44,  24,  25,  26,  36,  37,  38,  27,  28,  34,  35,  29,  33,
     30,  32,  31,
     /* Q8[0] VLC symbols - 127 entries */
     11,  12, 111, 113, 114, 115,   0,   1,  13,  14,  15,  16,  17,  18,  19,
     21, 104, 105, 107, 108, 109, 110, 112,   2,   3,   4,   5,   6,   8,  10,
     20,  22,  23,  24,  25,  26,  27,  28,  29,  31,  32,  33,  34,  35,  92,
     93,  95,  96,  97,  98,  99, 100, 101, 102, 103, 106, 116, 117, 120, 121,
    122, 123, 124, 125, 126,   7,   9,  30,  36,  37,  38,  39,  40,  41,  42,
     43,  45,  83,  84,  85,  86,  87,  88,  89,  90,  91,  94, 118, 119,  44,
     46,  47,  48,  49,  50,  51,  75,  76,  77,  78,  79,  80,  81,  82,  52,
     53,  54,  55,  71,  72,  73,  74,  56,  57,  58,  59,  67,  68,  69,  70,
     60,  65,  66,  61,  62,  64,  63,
     /* Q2[1] VLC symbols - 125 entries */
      4,  24, 100, 120,   0,  20, 104, 124,   1,   3,   5,   9,  10,  15,  19,
     21,  23,  25,  29,  45,  49,  75,  79,  95,  99, 101, 102, 103, 105, 109,
    114, 115, 119, 121, 123,   2,  14,  22,  50,  54,  70,  74, 110, 122,   6,
      7,   8,  11,  13,  16,  17,  18,  26,  27,  28,  30,  34,  35,  39,  40,
     44,  46,  47,  48,  51,  53,  55,  59,  65,  69,  71,  73,  76,  77,  78,
     80,  84,  85,  89,  90,  94,  96,  97,  98, 106, 107, 108, 111, 113, 116,
    117, 118,  12,  52,  60,  64,  72, 112,  31,  33,  36,  41,  43,  81,  83,
     88,  91,  93,  32,  37,  38,  42,  56,  57,  58,  61,  63,  66,  67,  68,
     82,  86,  87,  92,  62,
     /* Q4 VLC symbols - 81 entries */
     12,   4, 140, 132,  13,   3,  28,  20, 124, 116, 141, 131,  14,   1,   2,
     29,  19,  44,  36,  60,  52,  92,  84, 108, 100, 125, 115, 142, 143, 129,
    130,  15,   0,  30,  18,  45,  35,  76,  68, 109,  99, 126, 127, 114, 128,
     31,  16,  17,  46,  47,  33,  34,  61,  62,  50,  51,  77,  67,  93,  94,
     82,  83, 110, 111,  97,  98, 112, 113,  32,  63,  48,  49,  78,  79,  65,
     66,  95,  80,  81,  96,  64,
     /* Q5[1] VLC symbols - 15 entries */
      0,   1,  13,  14,   2,  12,   3,   4,  10,  11,   5,   6,   7,   8,   9,
     /* Q6[1] VLC symbols - 31 entries */
      0,   1,  29,  30,   2,   3,   4,  26,  27,  28,   5,   6,  24,  25,   7,
      8,   9,  21,  22,  23,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
     20,
     /* Q7[1] VLC symbols - 63 entries */
      0,   1,  61,  62,   2,   3,   4,   5,   6,   7,   8,  54,  55,  56,  57,
     58,  59,  60,   9,  10,  11,  12,  13,  49,  50,  51,  52,  53,  14,  15,
     16,  17,  18,  19,  20,  21,  42,  43,  44,  45,  46,  47,  48,  22,  23,
     24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,
     39,  40,  41,
     /* Q8[1] VLC symbols - 127 entries */
      0,   1,   2,   3, 123, 124, 125, 126,   4,   5,   6,   7,   8,   9,  10,
     11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,
     36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  75,
     77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,
     92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102,  50,  51,  52,  53,
     54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,
     69,  70,  71,  72,  73,  74,  76,
};

#endif /* AVCODEC_MPC8HUFF_H */
