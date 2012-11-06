/* C++ code produced by gperf version 3.0.3 */
/* Command-line: gperf -L C++ ViewAttributesHash.gperf  */
/* Computed positions: -k'1,$' */

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

#line 1 "ViewAttributesHash.gperf"

#include "ViewAttributesHash.h"
#include <string.h>

namespace UI {
enum
  {
    TOTAL_KEYWORDS = 32,
    MIN_WORD_LENGTH = 1,
    MAX_WORD_LENGTH = 18,
    MIN_HASH_VALUE = 1,
    MAX_HASH_VALUE = 56
  };

/* maximum key range = 56, duplicates = 0 */

class ViewAttributesHash
{
private:
  static inline unsigned int viewAttribteHashFunction (const char *str, unsigned int len);
public:
  static const struct ViewAttributeName *findAttributeImpl (const char *str, unsigned int len);
};

inline unsigned int
ViewAttributesHash::viewAttribteHashFunction (register const char *str, register unsigned int len)
{
  static const unsigned char asso_values[] =
    {
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 15,  0,
       0,  5, 20,  0,  0,  0, 57, 57, 57,  5,
      15, 57,  0, 57, 15,  0,  0, 57, 35,  0,
       0, 20, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
      57, 57, 57, 57, 57, 57
    };
  return len + asso_values[(unsigned char)str[len - 1]] + asso_values[(unsigned char)str[0]];
}

static const struct ViewAttributeName wordlist[] =
  {
    {""},
#line 33 "ViewAttributesHash.gperf"
    {"x", Attr_PositionX},
#line 20 "ViewAttributesHash.gperf"
    {"id", Attr_Id},
    {""}, {""},
#line 31 "ViewAttributesHash.gperf"
    {"width", Attr_PositionWidth},
#line 32 "ViewAttributesHash.gperf"
    {"height", Attr_PositionHeight},
#line 21 "ViewAttributesHash.gperf"
    {"padding", Attr_Padding},
    {""}, {""}, {""},
#line 24 "ViewAttributesHash.gperf"
    {"padding-top", Attr_PaddingTop},
#line 22 "ViewAttributesHash.gperf"
    {"padding-left", Attr_PaddingLeft},
#line 23 "ViewAttributesHash.gperf"
    {"padding-right", Attr_PaddingRight},
    {""},
#line 29 "ViewAttributesHash.gperf"
    {"margin-top", Attr_MarginTop},
#line 27 "ViewAttributesHash.gperf"
    {"margin-left", Attr_MarginLeft},
#line 28 "ViewAttributesHash.gperf"
    {"margin-right", Attr_MarginRight},
    {""},
#line 25 "ViewAttributesHash.gperf"
    {"padding-bottom", Attr_PaddingBottom},
#line 51 "ViewAttributesHash.gperf"
    {"color", Attr_TextColor},
#line 40 "ViewAttributesHash.gperf"
    {"halign", Attr_HAlign},
#line 35 "ViewAttributesHash.gperf"
    {"postion", Attr_Position},
#line 30 "ViewAttributesHash.gperf"
    {"margin-bottom", Attr_MarginBottom},
    {""},
#line 49 "ViewAttributesHash.gperf"
    {"text-align", Attr_TextAlign},
#line 26 "ViewAttributesHash.gperf"
    {"margin", Attr_Margin},
#line 37 "ViewAttributesHash.gperf"
    {"border-width", Attr_BorderWidth},
#line 38 "ViewAttributesHash.gperf"
    {"border-radius", Attr_BorderRadius},
    {""},
#line 50 "ViewAttributesHash.gperf"
    {"text-decoration", Attr_TextDecoration},
#line 47 "ViewAttributesHash.gperf"
    {"font-weight", Attr_FontWeight},
#line 44 "ViewAttributesHash.gperf"
    {"background-repeat", Attr_BackgroundRepeat},
    {""},
#line 45 "ViewAttributesHash.gperf"
    {"font-size", Attr_FontSize},
#line 48 "ViewAttributesHash.gperf"
    {"font-style", Attr_FontStyle},
#line 42 "ViewAttributesHash.gperf"
    {"background-image", Attr_BackgroundImage},
    {""}, {""}, {""}, {""},
#line 34 "ViewAttributesHash.gperf"
    {"y", Attr_PositionY},
#line 36 "ViewAttributesHash.gperf"
    {"border-color", Attr_BorderColor},
    {""}, {""}, {""},
#line 41 "ViewAttributesHash.gperf"
    {"background-color", Attr_BackgroundColor},
    {""},
#line 43 "ViewAttributesHash.gperf"
    {"background-postion", Attr_BackgroundPosition},
    {""}, {""},
#line 46 "ViewAttributesHash.gperf"
    {"font-family", Attr_FontFamily},
    {""}, {""}, {""}, {""},
#line 39 "ViewAttributesHash.gperf"
    {"valign", Attr_VAlign}
  };

const struct ViewAttributeName *
ViewAttributesHash::findAttributeImpl (register const char *str, register unsigned int len)
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = viewAttribteHashFunction (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
#line 52 "ViewAttributesHash.gperf"

const ViewAttributeName* findViewAttribute(register const char *str, register unsigned int len)
{
    return ViewAttributesHash::findAttributeImpl(str, len);
}

} //namespace UI
