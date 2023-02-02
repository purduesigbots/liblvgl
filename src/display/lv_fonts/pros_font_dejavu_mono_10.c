/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "display/lvgl.h"
#endif

#ifndef PROS_FONT_DEJAVU_MONO_10
#define PROS_FONT_DEJAVU_MONO_10 1
#endif

#if PROS_FONT_DEJAVU_MONO_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xf9,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x28, 0xa7, 0xca, 0x53, 0xe5, 0x14,

    /* U+0024 "$" */
    0x23, 0xa9, 0x47, 0x14, 0xbe, 0x21, 0x0,

    /* U+0025 "%" */
    0x42, 0x8a, 0x32, 0x31, 0x62, 0x4e,

    /* U+0026 "&" */
    0x71, 0x4, 0x18, 0x96, 0x5c, 0x9d,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x5a, 0xaa, 0x40,

    /* U+0029 ")" */
    0xa5, 0x56, 0xa0,

    /* U+002A "*" */
    0x25, 0x5d, 0xf2, 0x0,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x8, 0x44, 0x22, 0x10, 0x88, 0x40,

    /* U+0030 "0" */
    0x76, 0xe3, 0x58, 0xc7, 0x6e,

    /* U+0031 "1" */
    0xe1, 0x8, 0x42, 0x10, 0x9f,

    /* U+0032 "2" */
    0x70, 0x42, 0x11, 0x11, 0x1f,

    /* U+0033 "3" */
    0x70, 0x42, 0x60, 0x86, 0x3e,

    /* U+0034 "4" */
    0x11, 0x94, 0xa9, 0x7c, 0x42,

    /* U+0035 "5" */
    0x72, 0x10, 0xe0, 0x84, 0x3e,

    /* U+0036 "6" */
    0x76, 0x21, 0xe8, 0xc6, 0x2e,

    /* U+0037 "7" */
    0xf8, 0x44, 0x21, 0x10, 0x84,

    /* U+0038 "8" */
    0x69, 0x96, 0x99, 0x96,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x6e,

    /* U+003A ":" */
    0x88,

    /* U+003B ";" */
    0x8e,

    /* U+003C "<" */
    0x9, 0xb0, 0xc1, 0x80,

    /* U+003D "=" */
    0xfc, 0xf, 0xc0,

    /* U+003E ">" */
    0x83, 0x6, 0x6c, 0x0,

    /* U+003F "?" */
    0xe1, 0x12, 0x44, 0x4,

    /* U+0040 "@" */
    0x39, 0x19, 0xe9, 0xa6, 0x99, 0xd0, 0x38,

    /* U+0041 "A" */
    0x30, 0xc3, 0x12, 0x49, 0xe4, 0xa1,

    /* U+0042 "B" */
    0xe4, 0xa5, 0xc9, 0xc6, 0x3e,

    /* U+0043 "C" */
    0x7e, 0x61, 0x8, 0x43, 0x2f,

    /* U+0044 "D" */
    0xf4, 0xa3, 0x18, 0xc6, 0x7e,

    /* U+0045 "E" */
    0xf8, 0x8f, 0x88, 0x8f,

    /* U+0046 "F" */
    0xf8, 0x8f, 0x88, 0x88,

    /* U+0047 "G" */
    0x7a, 0x61, 0x9, 0xc7, 0x2f,

    /* U+0048 "H" */
    0x8c, 0x63, 0xf8, 0xc6, 0x31,

    /* U+0049 "I" */
    0xf9, 0x8, 0x42, 0x10, 0x9f,

    /* U+004A "J" */
    0x71, 0x11, 0x11, 0x1e,

    /* U+004B "K" */
    0x8c, 0xa9, 0xca, 0x4a, 0x51,

    /* U+004C "L" */
    0x84, 0x21, 0x8, 0x42, 0x1f,

    /* U+004D "M" */
    0xde, 0xf7, 0xda, 0xc6, 0x31,

    /* U+004E "N" */
    0xce, 0x73, 0x5a, 0xce, 0x73,

    /* U+004F "O" */
    0x74, 0x63, 0x18, 0xc6, 0x2e,

    /* U+0050 "P" */
    0xf4, 0x63, 0x1f, 0x42, 0x10,

    /* U+0051 "Q" */
    0x74, 0x63, 0x18, 0xc6, 0x2e, 0x10,

    /* U+0052 "R" */
    0xe4, 0xa5, 0x2e, 0x4a, 0x51,

    /* U+0053 "S" */
    0x7c, 0x61, 0xc1, 0x84, 0x3e,

    /* U+0054 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84,

    /* U+0055 "U" */
    0x8c, 0x63, 0x18, 0xc6, 0x2e,

    /* U+0056 "V" */
    0x85, 0x24, 0x92, 0x48, 0xc3, 0xc,

    /* U+0057 "W" */
    0x86, 0x1b, 0x6d, 0xb9, 0xe4, 0x92,

    /* U+0058 "X" */
    0x49, 0x23, 0xc, 0x30, 0xa4, 0xa1,

    /* U+0059 "Y" */
    0x8c, 0x54, 0xc2, 0x10, 0x84,

    /* U+005A "Z" */
    0xf8, 0x44, 0x42, 0x22, 0x1f,

    /* U+005B "[" */
    0xea, 0xaa, 0xb0,

    /* U+005C "\\" */
    0x42, 0x8, 0x42, 0x8, 0x41, 0x8,

    /* U+005D "]" */
    0xd5, 0x55, 0x70,

    /* U+005E "^" */
    0x31, 0x24, 0x80,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x48,

    /* U+0061 "a" */
    0xf0, 0x5f, 0x18, 0xbc,

    /* U+0062 "b" */
    0x84, 0x3d, 0x18, 0xc6, 0x3e,

    /* U+0063 "c" */
    0x78, 0x88, 0x87,

    /* U+0064 "d" */
    0x8, 0x5f, 0x18, 0xc6, 0x2f,

    /* U+0065 "e" */
    0x74, 0x7f, 0xc, 0x3c,

    /* U+0066 "f" */
    0x74, 0xf4, 0x44, 0x44,

    /* U+0067 "g" */
    0x7c, 0x63, 0x18, 0xbc, 0x2e,

    /* U+0068 "h" */
    0x88, 0xf9, 0x99, 0x99,

    /* U+0069 "i" */
    0x20, 0x18, 0x42, 0x10, 0x9f,

    /* U+006A "j" */
    0x23, 0x92, 0x49, 0x3c,

    /* U+006B "k" */
    0x84, 0x25, 0x4c, 0x52, 0x52,

    /* U+006C "l" */
    0xc4, 0x44, 0x44, 0x47,

    /* U+006D "m" */
    0xfd, 0x6b, 0x5a, 0xd4,

    /* U+006E "n" */
    0xf9, 0x99, 0x99,

    /* U+006F "o" */
    0x74, 0x63, 0x18, 0xb8,

    /* U+0070 "p" */
    0xf4, 0x63, 0x18, 0xfa, 0x10,

    /* U+0071 "q" */
    0x7c, 0x63, 0x18, 0xbc, 0x21,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88,

    /* U+0073 "s" */
    0xf8, 0xc3, 0x1e,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x47,

    /* U+0075 "u" */
    0x99, 0x99, 0x9f,

    /* U+0076 "v" */
    0x49, 0x24, 0x8c, 0x30, 0xc0,

    /* U+0077 "w" */
    0x86, 0x1b, 0x9e, 0x79, 0x20,

    /* U+0078 "x" */
    0x48, 0xc3, 0xc, 0x49, 0x20,

    /* U+0079 "y" */
    0x94, 0xa4, 0xc6, 0x11, 0x18,

    /* U+007A "z" */
    0xf1, 0x24, 0x8f,

    /* U+007B "{" */
    0x32, 0x22, 0x2c, 0x22, 0x23,

    /* U+007C "|" */
    0xff, 0xe0,

    /* U+007D "}" */
    0xc4, 0x44, 0x43, 0x44, 0x4c,

    /* U+007E "~" */
    0xe1, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 96, .box_w = 1, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 17, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 96, .box_w = 1, .box_h = 3, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 30, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 40, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 44, .adv_w = 96, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 45, .adv_w = 96, .box_w = 2, .box_h = 1, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 46, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 96, .box_w = 1, .box_h = 5, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 96, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 104, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 108, .adv_w = 96, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 111, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 115, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 96, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 126, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 210, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 261, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 267, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 270, .adv_w = 96, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 273, .adv_w = 96, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 274, .adv_w = 96, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 275, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 305, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 96, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 318, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 343, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 348, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 381, .adv_w = 96, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 389, .adv_w = 96, .box_w = 1, .box_h = 11, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 391, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 396, .adv_w = 96, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t pros_font_dejavu_mono_10 = {
#else
lv_font_t pros_font_dejavu_mono_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if PROS_FONT_DEJAVU_MONO_10*/

