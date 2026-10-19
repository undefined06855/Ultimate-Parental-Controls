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
    Infinity,
    Root
};

class SpecialGlyph : public cocos2d::CCNode {
public:
    static size_t generateSpecialGlyphID(SpecialGlyphType charCode, int variation = 0);
    static std::pair<SpecialGlyphType, int>& lookupSpecialGlyphID(size_t id);
    static bool isSpecialIDGlyph(size_t index);

    static SpecialGlyph* create(mfl::shaped_glyph glyph);
    bool init(mfl::shaped_glyph glyph);

    SpecialGlyphType m_type = SpecialGlyphType::Unknown;

    mfl::math_glyph_info getGlyphInfo();
};
