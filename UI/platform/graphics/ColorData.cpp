/* C++ code produced by gperf version 3.0.3 */
/* Command-line: gperf -L C++ ColorData.gperf  */
/* Computed positions: -k'1,3,6-8,12-13' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "ColorData.gperf"

#include "HashTools.h"
#include <string.h>

namespace UI {
enum
  {
    TOTAL_KEYWORDS = 150,
    MIN_WORD_LENGTH = 3,
    MAX_WORD_LENGTH = 20,
    MIN_HASH_VALUE = 4,
    MAX_HASH_VALUE = 561
  };

/* maximum key range = 558, duplicates = 0 */

class ColorDataHash
{
private:
  static inline unsigned int colordata_hash_function (const char *str, unsigned int len);
public:
  static const struct NamedColor *findColorImpl (const char *str, unsigned int len);
};

inline unsigned int
ColorDataHash::colordata_hash_function (register const char *str, register unsigned int len)
{
  static const unsigned short asso_values[] =
    {
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562,   5, 110,   0,
       35,   0,  75,  10,  30,   0, 562, 160,  10,  40,
       85,  60,  70,  70,   0,  20,  45,  85, 115, 190,
       15, 235, 562,  15, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562, 562, 562,
      562, 562, 562, 562, 562, 562, 562, 562
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
      case 10:
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]+2];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

static const struct NamedColor wordlist[] =
  {
    {""}, {""}, {""}, {""},
#line 39 "ColorData.gperf"
    {"cyan", 0xff00ffff},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 72 "ColorData.gperf"
    {"gray", 0xff808080},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 73 "ColorData.gperf"
    {"grey", 0xff808080},
#line 74 "ColorData.gperf"
    {"green", 0xff008000},
    {""}, {""}, {""},
#line 91 "ColorData.gperf"
    {"lightgrey", 0xffd3d3d3},
#line 92 "ColorData.gperf"
    {"lightgreen", 0xff90ee90},
    {""}, {""}, {""},
#line 90 "ColorData.gperf"
    {"lightgray", 0xffd3d3d3},
    {""}, {""}, {""}, {""},
#line 152 "ColorData.gperf"
    {"slategrey", 0xff708090},
    {""},
#line 147 "ColorData.gperf"
    {"sienna", 0xffa0522d},
    {""}, {""},
#line 151 "ColorData.gperf"
    {"slategray", 0xff708090},
    {""}, {""}, {""},
#line 146 "ColorData.gperf"
    {"seashell", 0xfffff5ee},
#line 157 "ColorData.gperf"
    {"teal", 0xff008080},
#line 35 "ColorData.gperf"
    {"coral", 0xffff7f50},
    {""}, {""}, {""}, {""}, {""},
#line 94 "ColorData.gperf"
    {"lightsalmon", 0xffffa07a},
    {""}, {""},
#line 99 "ColorData.gperf"
    {"lightslategrey", 0xff778899},
    {""}, {""}, {""}, {""},
#line 98 "ColorData.gperf"
    {"lightslategray", 0xff778899},
    {""},
#line 125 "ColorData.gperf"
    {"orange", 0xffffa500},
    {""},
#line 82 "ColorData.gperf"
    {"lavender", 0xffe6e6fa},
#line 126 "ColorData.gperf"
    {"orangered", 0xffff4500},
    {""}, {""}, {""}, {""},
#line 102 "ColorData.gperf"
    {"lime", 0xff00ff00},
#line 80 "ColorData.gperf"
    {"ivory", 0xfffffff0},
    {""}, {""},
#line 139 "ColorData.gperf"
    {"red", 0xffff0000},
#line 103 "ColorData.gperf"
    {"limegreen", 0xff32cd32},
#line 87 "ColorData.gperf"
    {"lightcoral", 0xfff08080},
    {""}, {""}, {""}, {""},
#line 104 "ColorData.gperf"
    {"linen", 0xfffaf0e6},
    {""},
#line 67 "ColorData.gperf"
    {"fuchsia", 0xffff00ff},
    {""},
#line 45 "ColorData.gperf"
    {"darkgreen", 0xff006400},
    {""}, {""}, {""}, {""},
#line 153 "ColorData.gperf"
    {"snow", 0xfffffafa},
#line 33 "ColorData.gperf"
    {"chartreuse", 0xff7fff00},
#line 154 "ColorData.gperf"
    {"springgreen", 0xff00ff7f},
#line 105 "ColorData.gperf"
    {"magenta", 0xffff00ff},
    {""},
#line 70 "ColorData.gperf"
    {"gold", 0xffffd700},
    {""},
#line 127 "ColorData.gperf"
    {"orchid", 0xffda70d6},
    {""}, {""},
#line 121 "ColorData.gperf"
    {"navy", 0xff000080},
    {""},
#line 47 "ColorData.gperf"
    {"darkmagenta", 0xff8b008b},
    {""}, {""}, {""}, {""},
#line 148 "ColorData.gperf"
    {"silver", 0xffc0c0c0},
    {""},
#line 145 "ColorData.gperf"
    {"seagreen", 0xff2e8b57},
    {""},
#line 26 "ColorData.gperf"
    {"black", 0xff000000},
    {""}, {""},
#line 156 "ColorData.gperf"
    {"tan", 0xffd2b48c},
#line 134 "ColorData.gperf"
    {"peru", 0xffcd853f},
#line 50 "ColorData.gperf"
    {"darkorchid", 0xff9932cc},
#line 138 "ColorData.gperf"
    {"purple", 0xff800080},
#line 51 "ColorData.gperf"
    {"darkred", 0xff8b0000},
#line 83 "ColorData.gperf"
    {"lavenderblush", 0xfffff0f5},
#line 117 "ColorData.gperf"
    {"mintcream", 0xfff5fffa},
    {""}, {""},
#line 149 "ColorData.gperf"
    {"skyblue", 0xff87ceeb},
    {""},
#line 64 "ColorData.gperf"
    {"firebrick", 0xffb22222},
    {""},
#line 160 "ColorData.gperf"
    {"transparent", 0x00000000},
    {""},
#line 95 "ColorData.gperf"
    {"lightseagreen", 0xff20b2aa},
    {""}, {""}, {""}, {""}, {""},
#line 34 "ColorData.gperf"
    {"chocolate", 0xffd2691e},
    {""},
#line 79 "ColorData.gperf"
    {"indigo", 0xff4b0082},
#line 122 "ColorData.gperf"
    {"oldlace", 0xfffdf5e6},
    {""},
#line 135 "ColorData.gperf"
    {"pink", 0xffffc0cb},
#line 52 "ColorData.gperf"
    {"darksalmon", 0xffe9967a},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 119 "ColorData.gperf"
    {"moccasin", 0xffffe4b5},
#line 97 "ColorData.gperf"
    {"lightslateblue", 0xff8470ff},
    {""}, {""}, {""}, {""}, {""},
#line 58 "ColorData.gperf"
    {"darkviolet", 0xff9400d3},
    {""}, {""}, {""},
#line 129 "ColorData.gperf"
    {"palegreen", 0xff98fb98},
#line 81 "ColorData.gperf"
    {"khaki", 0xfff0e68c},
    {""}, {""}, {""},
#line 78 "ColorData.gperf"
    {"indianred", 0xffcd5c5c},
#line 89 "ColorData.gperf"
    {"lightgoldenrodyellow", 0xfffafad2},
#line 159 "ColorData.gperf"
    {"tomato", 0xffff6347},
    {""}, {""},
#line 93 "ColorData.gperf"
    {"lightpink", 0xffffb6c1},
    {""},
#line 106 "ColorData.gperf"
    {"maroon", 0xff800000},
    {""}, {""},
#line 161 "ColorData.gperf"
    {"turquoise", 0xff40e0d0},
#line 49 "ColorData.gperf"
    {"darkorange", 0xffff8c00},
    {""}, {""},
#line 40 "ColorData.gperf"
    {"darkblue", 0xff00008b},
#line 100 "ColorData.gperf"
    {"lightsteelblue", 0xffb0c4de},
#line 30 "ColorData.gperf"
    {"brown", 0xffa52a2a},
#line 66 "ColorData.gperf"
    {"forestgreen", 0xff228b22},
    {""}, {""},
#line 111 "ColorData.gperf"
    {"mediumseagreen", 0xff3cb371},
    {""}, {""},
#line 53 "ColorData.gperf"
    {"darkseagreen", 0xff8fbc8f},
    {""}, {""}, {""},
#line 143 "ColorData.gperf"
    {"salmon", 0xfffa8072},
#line 85 "ColorData.gperf"
    {"lemonchiffon", 0xfffffacd},
    {""},
#line 21 "ColorData.gperf"
    {"aqua", 0xff00ffff},
#line 23 "ColorData.gperf"
    {"azure", 0xfff0ffff},
#line 25 "ColorData.gperf"
    {"bisque", 0xffffe4c4},
    {""}, {""}, {""},
#line 164 "ColorData.gperf"
    {"wheat", 0xfff5deb3},
    {""}, {""}, {""}, {""},
#line 22 "ColorData.gperf"
    {"aquamarine", 0xff7fffd4},
    {""},
#line 116 "ColorData.gperf"
    {"midnightblue", 0xff191970},
    {""},
#line 118 "ColorData.gperf"
    {"mistyrose", 0xffffe4e1},
    {""},
#line 142 "ColorData.gperf"
    {"saddlebrown", 0xff8b4513},
    {""}, {""},
#line 48 "ColorData.gperf"
    {"darkolivegreen", 0xff556b2f},
    {""}, {""},
#line 158 "ColorData.gperf"
    {"thistle", 0xffd8bfd8},
#line 37 "ColorData.gperf"
    {"cornsilk", 0xfffff8dc},
#line 86 "ColorData.gperf"
    {"lightblue", 0xffadd8e6},
#line 123 "ColorData.gperf"
    {"olive", 0xff808000},
    {""}, {""}, {""},
#line 141 "ColorData.gperf"
    {"royalblue", 0xff4169e1},
    {""}, {""}, {""}, {""},
#line 150 "ColorData.gperf"
    {"slateblue", 0xff6a5acd},
    {""},
#line 162 "ColorData.gperf"
    {"violet", 0xffee82ee},
    {""},
#line 54 "ColorData.gperf"
    {"darkslateblue", 0xff483d8b},
#line 163 "ColorData.gperf"
    {"violetred", 0xffd02090},
#line 63 "ColorData.gperf"
    {"dodgerblue", 0xff1e90ff},
    {""}, {""}, {""},
#line 155 "ColorData.gperf"
    {"steelblue", 0xff4682b4},
    {""}, {""}, {""}, {""},
#line 71 "ColorData.gperf"
    {"goldenrod", 0xffdaa520},
    {""},
#line 107 "ColorData.gperf"
    {"mediumaquamarine", 0xff66cdaa},
    {""}, {""},
#line 84 "ColorData.gperf"
    {"lawngreen", 0xff7cfc00},
    {""}, {""}, {""}, {""},
#line 88 "ColorData.gperf"
    {"lightcyan", 0xffe0ffff},
    {""}, {""},
#line 109 "ColorData.gperf"
    {"mediumorchid", 0xffba55d3},
    {""},
#line 136 "ColorData.gperf"
    {"plum", 0xffdda0dd},
    {""},
#line 101 "ColorData.gperf"
    {"lightyellow", 0xffffffe0},
    {""},
#line 57 "ColorData.gperf"
    {"darkturquoise", 0xff00ced1},
#line 124 "ColorData.gperf"
    {"olivedrab", 0xff6b8e23},
#line 144 "ColorData.gperf"
    {"sandybrown", 0xfff4a460},
    {""}, {""},
#line 131 "ColorData.gperf"
    {"palevioletred", 0xffdb7093},
    {""},
#line 24 "ColorData.gperf"
    {"beige", 0xfff5f5dc},
#line 75 "ColorData.gperf"
    {"greenyellow", 0xffadff2f},
    {""}, {""}, {""}, {""}, {""},
#line 113 "ColorData.gperf"
    {"mediumspringgreen", 0xff00fa9a},
    {""},
#line 46 "ColorData.gperf"
    {"darkkhaki", 0xffbdb76b},
#line 108 "ColorData.gperf"
    {"mediumblue", 0xff0000cd},
    {""}, {""}, {""},
#line 32 "ColorData.gperf"
    {"cadetblue", 0xff5f9ea0},
    {""}, {""}, {""},
#line 42 "ColorData.gperf"
    {"darkgoldenrod", 0xffb8860b},
    {""}, {""}, {""}, {""},
#line 59 "ColorData.gperf"
    {"deeppink", 0xffff1493},
    {""}, {""}, {""}, {""}, {""},
#line 28 "ColorData.gperf"
    {"blue", 0xff0000ff},
#line 132 "ColorData.gperf"
    {"papayawhip", 0xffffefd5},
    {""}, {""}, {""},
#line 133 "ColorData.gperf"
    {"peachpuff", 0xffffdab9},
#line 69 "ColorData.gperf"
    {"ghostwhite", 0xfff8f8ff},
    {""},
#line 38 "ColorData.gperf"
    {"crimson", 0xffdc143c},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 112 "ColorData.gperf"
    {"mediumslateblue", 0xff7b68ee},
    {""},
#line 110 "ColorData.gperf"
    {"mediumpurple", 0xff9370db},
#line 44 "ColorData.gperf"
    {"darkgrey", 0xffa9a9a9},
    {""}, {""}, {""}, {""},
#line 43 "ColorData.gperf"
    {"darkgray", 0xffa9a9a9},
    {""},
#line 115 "ColorData.gperf"
    {"mediumvioletred", 0xffc71585},
    {""}, {""},
#line 76 "ColorData.gperf"
    {"honeydew", 0xfff0fff0},
#line 27 "ColorData.gperf"
    {"blanchedalmond", 0xffffebcd},
    {""}, {""},
#line 62 "ColorData.gperf"
    {"dimgrey", 0xff696969},
    {""}, {""}, {""}, {""},
#line 61 "ColorData.gperf"
    {"dimgray", 0xff696969},
#line 130 "ColorData.gperf"
    {"paleturquoise", 0xffafeeee},
#line 140 "ColorData.gperf"
    {"rosybrown", 0xffbc8f8f},
    {""}, {""}, {""}, {""},
#line 68 "ColorData.gperf"
    {"gainsboro", 0xffdcdcdc},
    {""}, {""}, {""}, {""}, {""},
#line 165 "ColorData.gperf"
    {"white", 0xffffffff},
    {""}, {""}, {""}, {""},
#line 114 "ColorData.gperf"
    {"mediumturquoise", 0xff48d1cc},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 128 "ColorData.gperf"
    {"palegoldenrod", 0xffeee8aa},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 19 "ColorData.gperf"
    {"aliceblue", 0xfff0f8ff},
#line 29 "ColorData.gperf"
    {"blueviolet", 0xff8a2be2},
    {""}, {""}, {""}, {""}, {""},
#line 65 "ColorData.gperf"
    {"floralwhite", 0xfffffaf0},
    {""},
#line 56 "ColorData.gperf"
    {"darkslategrey", 0xff2f4f4f},
    {""}, {""},
#line 120 "ColorData.gperf"
    {"navajowhite", 0xffffdead},
    {""},
#line 55 "ColorData.gperf"
    {"darkslategray", 0xff2f4f4f},
    {""}, {""}, {""},
#line 77 "ColorData.gperf"
    {"hotpink", 0xffff69b4},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 20 "ColorData.gperf"
    {"antiquewhite", 0xfffaebd7},
    {""}, {""}, {""}, {""}, {""},
#line 41 "ColorData.gperf"
    {"darkcyan", 0xff008b8b},
#line 36 "ColorData.gperf"
    {"cornflowerblue", 0xff6495ed},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 137 "ColorData.gperf"
    {"powderblue", 0xffb0e0e6},
    {""},
#line 96 "ColorData.gperf"
    {"lightskyblue", 0xff87cefa},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 31 "ColorData.gperf"
    {"burlywood", 0xffdeb887},
    {""}, {""}, {""}, {""}, {""},
#line 166 "ColorData.gperf"
    {"whitesmoke", 0xfff5f5f5},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 167 "ColorData.gperf"
    {"yellow", 0xffffff00},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 168 "ColorData.gperf"
    {"yellowgreen", 0xff9acd32},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 60 "ColorData.gperf"
    {"deepskyblue", 0xff00bfff}
  };

const struct NamedColor *
ColorDataHash::findColorImpl (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = colordata_hash_function (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
#line 169 "ColorData.gperf"

const struct NamedColor* findColor(register const char* str, register unsigned int len)
{
    return ColorDataHash::findColorImpl(str, len);
}

} // namespace UI 
