#pragma once
#include <mfl/code_point.hpp>
#include <mfl/abstract_font_face.hpp>
#include <mfl/layout.hpp>

enum class SpecialGlyphType {
    Unknown = 0,

    Summation,
    Integral,
    Pi,
    Equivalent,
    Implies,
    ImpliedBy,
    Infinity
};

class SpecialGlyph : public cocos2d::CCNode {
public:
    static size_t generateSpecialGlyphID(SpecialGlyphType charCode);
    static bool isSpecialIDGlyph(size_t index);

    static SpecialGlyph* create(mfl::shaped_glyph glyph);
    bool init(mfl::shaped_glyph glyph);
};
