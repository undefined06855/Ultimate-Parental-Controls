#include "BigFontMath.hpp"
#include "SpecialGlyph.hpp"

std::unique_ptr<BigFontMath> BigFontMath::create(const mfl::font_family font) {
    // we ignore the font passed in and just return a BigFontMath
    return std::make_unique<BigFontMath>();
}

// converts from points to the weird unit value that for some reason mfl wants?
constexpr std::int32_t u(float value) {
    return value * 65536;
};

mfl::math_constants BigFontMath::constants() const {
    auto s = [this](float v) { return u(v * m_size); };

    try {
        auto json = geode::utils::file::readJson(geode::dirs::getGameDir() / "constants.json").unwrap();

        return mfl::math_constants{
            .axis_height = s(json["axis_height"].asDouble().unwrap()),
            .fraction_rule_thickness = s(json["fraction_rule_thickness"].asDouble().unwrap()),
            .subscript_drop = s(json["subscript_drop"].asDouble().unwrap()),
            .subscript_shift_down = s(json["subscript_shift_down"].asDouble().unwrap()),
            .superscript_drop = s(json["superscript_drop"].asDouble().unwrap()),
            .superscript_shift_up = s(json["superscript_shift_up"].asDouble().unwrap()),
            .superscript_shift_up_cramped = s(json["superscript_shift_up_cramped"].asDouble().unwrap()),
            .minimum_dual_script_gap = s(json["minimum_dual_script_gap"].asDouble().unwrap()),
            .maximum_superscript_bottom_in_dual_script = s(json["maximum_superscript_bottom_in_dual_script"].asDouble().unwrap()),
            .space_after_script = s(json["space_after_script"].asDouble().unwrap()),
            .radical_vertical_gap = s(json["radical_vertical_gap"].asDouble().unwrap()),
            .radical_rule_thickness = s(json["radical_rule_thickness"].asDouble().unwrap()),
            .radical_extra_ascender = s(json["radical_extra_ascender"].asDouble().unwrap()),
            .radical_kern_before_degree = s(json["radical_kern_before_degree"].asDouble().unwrap()),
            .radical_kern_after_degree = s(json["radical_kern_after_degree"].asDouble().unwrap()),
            .radical_degree_bottom_raise_percent = (int)json["radical_degree_bottom_raise_percent"].asDouble().unwrap(),
            .overline_gap = s(json["overline_gap"].asDouble().unwrap()),
            .overline_padding = s(json["overline_padding"].asDouble().unwrap()),
            .overline_thickness = s(json["overline_thickness"].asDouble().unwrap()),
            .underline_gap = s(json["underline_gap"].asDouble().unwrap()),
            .underline_padding = s(json["underline_padding"].asDouble().unwrap()),
            .underline_thickness = s(json["underline_thickness"].asDouble().unwrap()),
            .lower_limit_min_gap = s(json["lower_limit_min_gap"].asDouble().unwrap()),
            .upper_limit_min_gap = s(json["upper_limit_min_gap"].asDouble().unwrap()),
            .default_fraction = {
                .numerator_shift_up = s(json["default_fraction"]["numerator_shift_up"].asDouble().unwrap()),
                .denominator_shift_down = s(json["default_fraction"]["denominator_shift_down"].asDouble().unwrap()),
                .numerator_min_gap = s(json["default_fraction"]["numerator_min_gap"].asDouble().unwrap()),
                .denominator_min_gap = s(json["default_fraction"]["denominator_min_gap"].asDouble().unwrap())
            },
            .display_style_fraction = {
                .numerator_shift_up = s(json["display_style_fraction"]["numerator_shift_up"].asDouble().unwrap()),
                .denominator_shift_down = s(json["display_style_fraction"]["denominator_shift_down"].asDouble().unwrap()),
                .numerator_min_gap = s(json["display_style_fraction"]["numerator_min_gap"].asDouble().unwrap()),
                .denominator_min_gap = s(json["display_style_fraction"]["denominator_min_gap"].asDouble().unwrap())
            },
            .default_atop = {
                .numerator_shift_up = s(json["default_atop"]["numerator_shift_up"].asDouble().unwrap()),
                .denominator_shift_down = s(json["default_atop"]["denominator_shift_down"].asDouble().unwrap()),
                .numerator_min_gap = s(json["default_atop"]["numerator_min_gap"].asDouble().unwrap()),
                .denominator_min_gap = s(json["default_atop"]["denominator_min_gap"].asDouble().unwrap())
            },
            .display_style_atop = {
                .numerator_shift_up = s(json["display_style_atop"]["numerator_shift_up"].asDouble().unwrap()),
                .denominator_shift_down = s(json["display_style_atop"]["denominator_shift_down"].asDouble().unwrap()),
                .numerator_min_gap = s(json["display_style_atop"]["numerator_min_gap"].asDouble().unwrap()),
                .denominator_min_gap = s(json["display_style_atop"]["denominator_min_gap"].asDouble().unwrap())
            }
        };
    } catch(...) {}

    return mfl::math_constants{
        .axis_height = u(12.5f),
        .fraction_rule_thickness = u(1.f),
        .subscript_drop = u(10),
        .subscript_shift_down = u(5),
        .superscript_drop = u(15),
        .superscript_shift_up = u(10),
        .superscript_shift_up_cramped = u(13),
        .minimum_dual_script_gap = u(4),
        .maximum_superscript_bottom_in_dual_script = u(25),
        .space_after_script = u(6),
        .radical_vertical_gap = u(0),
        .radical_rule_thickness = u(0),
        .radical_extra_ascender = u(0),
        .radical_kern_before_degree = u(5),
        .radical_kern_after_degree = u(-20),
        .radical_degree_bottom_raise_percent = 30,
        .overline_gap = u(0),
        .overline_padding = u(0),
        .overline_thickness = u(0),
        .underline_gap = u(0),
        .underline_padding = u(0),
        .underline_thickness = u(0),
        .lower_limit_min_gap = u(0),
        .upper_limit_min_gap = u(0),
        .default_fraction = {
            .numerator_shift_up = u(0),
            .denominator_shift_down = u(0),
            .numerator_min_gap = u(0),
            .denominator_min_gap = u(0)
        },
        .display_style_fraction = {
            .numerator_shift_up = u(0),
            .denominator_shift_down = u(0),
            .numerator_min_gap = u(0),
            .denominator_min_gap = u(0)
        },
        .default_atop = {
            .numerator_shift_up = u(0),
            .denominator_shift_down = u(0),
            .numerator_min_gap = u(0),
            .denominator_min_gap = u(0)
        },
        .display_style_atop = {
            .numerator_shift_up = u(0),
            .denominator_shift_down = u(0),
            .numerator_min_gap = u(0),
            .denominator_min_gap = u(0)
        }
    };

    // taken from mock_font_face
    /*
    https://github.com/cpp-niel/mfl/blob/7ef9f07/tests/unit_tests/framework/mock_font_face.cpp#L77
    return {.axis_height = 168960,
            .fraction_rule_thickness = 45056,
            .subscript_drop = 104448,
            .subscript_shift_down = 137216,
            .superscript_drop = 150528,
            .superscript_shift_up = 235520,
            .superscript_shift_up_cramped = 164864,
            .minimum_dual_script_gap = 98304,
            .maximum_superscript_bottom_in_dual_script = 248832,
            .space_after_script = 26624,
            .radical_vertical_gap = 55296,
            .radical_rule_thickness = 45056,
            .radical_extra_ascender = 51200,
            .radical_kern_before_degree = 43008,
            .radical_kern_after_degree = -219136,
            .radical_degree_bottom_raise_percent = 55,
            .overline_gap = 135168,
            .overline_padding = 45056,
            .overline_thickness = 45056,
            .underline_gap = 135168,
            .underline_padding = 45056,
            .underline_thickness = 45056,
            .lower_limit_min_gap = 135168,
            .upper_limit_min_gap = 135168,
            .default_fraction = {.numerator_shift_up = 95744,
                                 .denominator_shift_down = 95744,
                                 .numerator_min_gap = 45056,
                                 .denominator_min_gap = 45056},
            .display_style_fraction = {.numerator_shift_up = 419840,
                                       .denominator_shift_down = 419840,
                                       .numerator_min_gap = 98304,
                                       .denominator_min_gap = 98304},
            .default_atop = {.numerator_shift_up = 308224,
                             .denominator_shift_down = 251904,
                             .numerator_min_gap = 98304,
                             .denominator_min_gap = 0},
            .display_style_atop = {.numerator_shift_up = 510976,
                                   .denominator_shift_down = 452608,
                                   .numerator_min_gap = 196608,
                                   .denominator_min_gap = 0}};
    */
}

mfl::math_glyph_info BigFontMath::glyph_info(const size_t glyph_index) const {
    // copied from bigFont.fnt
    static std::unordered_map<int, std::array<int, 7>> bigFontShit = {
        { 32, { 498, 128, 0, 0, 0, 33, 15 } },
        { 33, { 338, 39, 18, 29, -0, 5, 12 } },
        { 34, { 385, 128, 20, 15, -0, 1, 14 } },
        { 35, { 230, 128, 30, 18, -0, 5, 23 } },
        { 36, { 115, 2, 28, 34, -0, 1, 21 } },
        { 37, { 194, 2, 33, 30, -0, 4, 27 } },
        { 38, { 407, 2, 30, 29, -0, 4, 23 } },
        { 39, { 407, 128, 13, 15, -0, 1, 7 } },
        { 40, { 79, 2, 16, 35, -0, 1, 10 } },
        { 41, { 97, 2, 16, 35, -0, 1, 10 } },
        { 42, { 323, 128, 17, 16, -0, 0, 11 } },
        { 43, { 162, 128, 22, 22, -0, 9, 16 } },
        { 44, { 342, 128, 14, 16, -0, 20, 8 } },
        { 45, { 446, 128, 19, 13, -0, 14, 13 } },
        { 46, { 467, 128, 13, 13, -0, 21, 7 } },
        { 47, { 289, 2, 19, 30, -0, 4, 13 } },
        { 48, { 209, 39, 27, 29, -0, 4, 21 } },
        { 49, { 413, 70, 23, 28, -0, 5, 17 } },
        { 50, { 93, 39, 27, 29, -0, 4, 21 } },
        { 51, { 122, 39, 27, 29, -0, 4, 21 } },
        { 52, { 439, 39, 30, 28, -0, 5, 23 } },
        { 53, { 238, 39, 26, 29, -0, 4, 20 } },
        { 54, { 151, 39, 27, 29, -0, 4, 21 } },
        { 55, { 273, 70, 27, 28, -0, 5, 21 } },
        { 56, { 266, 39, 26, 29, -0, 4, 19 } },
        { 57, { 180, 39, 27, 29, -0, 5, 21 } },
        { 58, { 146, 128, 14, 26, -0, 8, 8 } },
        { 59, { 358, 39, 14, 29, -0, 7, 8 } },
        { 60, { 186, 128, 20, 21, -0, 10, 14 } },
        { 61, { 262, 128, 18, 17, -0, 12, 12 } },
        { 62, { 208, 128, 20, 21, -0, 10, 14 } },
        { 63, { 261, 2, 26, 30, -0, 4, 20 } },
        { 64, { 160, 2, 32, 33, -0, 2, 26 } },
        { 65, { 343, 2, 30, 29, -0, 4, 24 } },
        { 66, { 95, 70, 28, 28, -0, 5, 22 } },
        { 67, { 439, 2, 29, 29, -0, 5, 23 } },
        { 68, { 125, 70, 28, 28, -0, 5, 21 } },
        { 69, { 302, 70, 26, 28, -0, 5, 20 } },
        { 70, { 330, 70, 26, 28, -0, 5, 20 } },
        { 71, { 470, 2, 29, 29, -0, 4, 23 } },
        { 72, { 407, 39, 30, 28, -0, 5, 23 } },
        { 73, { 438, 70, 18, 28, -0, 5, 12 } },
        { 74, { 294, 39, 21, 29, -0, 5, 15 } },
        { 75, { 155, 70, 28, 28, -0, 5, 22 } },
        { 76, { 386, 70, 25, 28, -0, 5, 19 } },
        { 77, { 374, 39, 31, 28, -0, 5, 25 } },
        { 78, { 215, 70, 27, 28, -0, 5, 21 } },
        { 79, { 375, 2, 30, 29, -0, 5, 23 } },
        { 80, { 471, 39, 29, 28, -0, 5, 22 } },
        { 81, { 229, 2, 30, 30, -0, 5, 23 } },
        { 82, { 2, 70, 29, 28, -0, 5, 22 } },
        { 83, { 33, 39, 28, 29, -0, 5, 21 } },
        { 84, { 185, 70, 28, 28, -0, 5, 22 } },
        { 85, { 63, 39, 28, 29, -0, 5, 22 } },
        { 86, { 33, 70, 29, 28, -0, 5, 23 } },
        { 87, { 310, 2, 31, 29, -0, 4, 25 } },
        { 88, { 2, 39, 29, 29, -0, 4, 23 } },
        { 89, { 64, 70, 29, 28, -0, 5, 23 } },
        { 90, { 358, 70, 26, 28, -0, 5, 20 } },
        { 91, { 22, 2, 17, 35, -0, 1, 11 } },
        { 92, { 317, 39, 19, 29, -0, 5, 13 } },
        { 93, { 2, 2, 18, 35, -0, 1, 11 } },
        { 94, { 301, 128, 20, 16, -0, 0, 13 } },
        { 95, { 422, 128, 22, 13, -0, 25, 16 } },
        { 96, { 482, 128, 14, 12, -0, -1, 7 } },
        { 97, { 62, 100, 27, 26, -0, 7, 21 } },
        { 98, { 403, 100, 25, 26, -0, 7, 19 } },
        { 99, { 207, 100, 26, 26, -0, 7, 20 } },
        { 100, { 430, 100, 25, 26, -0, 7, 19 } },
        { 101, { 2, 128, 24, 26, -0, 7, 18 } },
        { 102, { 28, 128, 24, 26, -0, 7, 18 } },
        { 103, { 235, 100, 26, 26, -0, 7, 20 } },
        { 104, { 91, 100, 27, 26, -0, 7, 21 } },
        { 105, { 127, 128, 17, 26, -0, 7, 10 } },
        { 106, { 105, 128, 20, 26, -0, 7, 13 } },
        { 107, { 263, 100, 26, 26, -0, 7, 20 } },
        { 108, { 80, 128, 23, 26, -0, 7, 17 } },
        { 109, { 2, 100, 28, 26, -0, 7, 22 } },
        { 110, { 457, 100, 25, 26, -0, 7, 19 } },
        { 111, { 120, 100, 27, 26, -0, 7, 21 } },
        { 112, { 291, 100, 26, 26, -0, 7, 20 } },
        { 113, { 244, 70, 27, 28, -0, 7, 21 } },
        { 114, { 319, 100, 26, 26, -0, 7, 20 } },
        { 115, { 458, 70, 25, 27, -0, 7, 19 } },
        { 116, { 484, 100, 25, 26, -0, 7, 19 } },
        { 117, { 347, 100, 26, 26, -0, 7, 20 } },
        { 118, { 149, 100, 27, 26, -0, 7, 20 } },
        { 119, { 32, 100, 28, 26, -0, 7, 22 } },
        { 120, { 178, 100, 27, 26, -0, 7, 20 } },
        { 121, { 375, 100, 26, 26, -0, 7, 20 } },
        { 122, { 54, 128, 24, 26, -0, 7, 18 } },
        { 123, { 41, 2, 17, 35, -0, 1, 10 } },
        { 124, { 145, 2, 13, 34, -0, 2, 6 } },
        { 125, { 60, 2, 17, 35, -0, 1, 10 } },
        { 126, { 358, 128, 25, 15, -0, 1, 18 } },
        { 8226, { 282, 128, 17, 17, -0, 12, 11 } },
        { 127, { 0, 0, 0, 0, 23, 18, 46 } },
        { 30, { 0, 0, 0, 0, 27, 18, 54 } }
    };

    if (SpecialGlyph::isSpecialIDGlyph(glyph_index)) {
        auto fakeShapedGlyph = mfl::shaped_glyph{
            .index = glyph_index,
            .size = mfl::points(32)
        };

        auto glyph = SpecialGlyph::create(fakeShapedGlyph);
        auto info = glyph->getGlyphInfo();
        info.width = u(info.width);
        info.height = u(info.height);
        info.depth = u(info.depth);
        info.accent_hpos = u(info.accent_hpos);
        info.italic_correction = u(info.italic_correction);
        info.glyph_index = glyph_index;

        return info;
    }

    if (!bigFontShit.contains(glyph_index)) {
        auto label = geode::Label::create("x", "bigFont.fnt");
        label->setScale(m_size);
        return mfl::math_glyph_info{
            .glyph_index = glyph_index,
            .width = u(label->getContentWidth()),
            .height = u(label->getContentHeight())
        };
    }

    auto& data = bigFontShit.at(glyph_index);
    auto ret = mfl::math_glyph_info{
        .glyph_index = glyph_index,
        .width = u(data[6]),
        .height = u(32.f - data[5]),
        .depth = -u(32.f - (data[5] + data[3])),
        .italic_correction = u(0),
        .accent_hpos = u(data[4] + data[2] / 2.f)
    };

    ret.width *= m_size;
    ret.height *= m_size;
    ret.depth *= m_size;
    ret.accent_hpos *= m_size;

    return ret;
}

size_t BigFontMath::glyph_index_from_code_point(const mfl::code_point char_code, const bool use_large_variant) const {
    // normal stuff
    if ((char_code >= L' ' && char_code <= L'~') || char_code == L'•') {
        return char_code;
    }

    // https://en.wikipedia.org/wiki/Mathematical_Alphanumeric_Symbols#Chart_for_the_Mathematical_Alphanumeric_Symbols_block
    // reserved special bits
    switch (char_code) {
        case 0x212C: return 'B';
        case 0x212D:
        case 0x2102: return 'C';
        case 0x2130: return 'E';
        case 0x2131: return 'F';
        case 0x210B:
        case 0x210C:
        case 0x210D: return 'H';
        case 0x2110:
        case 0x2111: return 'I';
        case 0x2112: return 'L';
        case 0x2133: return 'M';
        case 0x2115: return 'N';
        case 0x2119: return 'P';
        case 0x211A: return 'Q';
        case 0x211B:
        case 0x211C:
        case 0x211D: return 'R';
        case 0x2128:
        case 0x2124: return 'Z';
        case 0x212F: return 'e';
        case 0x210A: return 'g';
        case 0x210E: return 'h';
        case 0x2134: return 'o';
        case 0x1D6A4: return 'i'; // i with no dot
        case 0x1D6A5: return 'j'; // j with no dot
    }

    // else remap
    if (char_code >= 0x1D400 && char_code <= 0x1D6A3) {
        char remapped = ((char_code - 0x1D400) % 52) + 0x41;
        return remapped <= 'Z' ? remapped : remapped + 6;
    }


    // everything else
    switch (char_code) {
        case 0x2212: return '-';

        case 0x21D0: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::ImpliedBy);
        case 0x21D2: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Implies);
        case 0x21D4: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Equivalent);

        case 0x221E: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Infinity);
        case 0x1D70B: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Pi);

        case 0x221A: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Root);

        case 0x2211: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Summation);
        case 0x222B: return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Integral);
    }

    return SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Unknown);
}

std::vector<mfl::size_variant> BigFontMath::horizontal_size_variants(const mfl::code_point char_code) const {
    return {};
}

std::vector<mfl::size_variant> BigFontMath::vertical_size_variants(const mfl::code_point char_code) const {
    std::vector<mfl::size_variant> ret;
    ret.reserve(100);

    for (int i = 0; i < 100; i++) {
        switch (char_code) {
            default: return {};

            case 0x221A: {
                ret.push_back({
                    .glyph_index = SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType::Root, i),
                    .size = u(i)
                });
            } break;
        }
    }

    return ret;
}

std::optional<mfl::glyph_assembly> BigFontMath::horizontal_assembly(const mfl::code_point char_code) const {
    return {};
}

std::optional<mfl::glyph_assembly> BigFontMath::vertical_assembly(const mfl::code_point char_code) const {
    return {};
}

void BigFontMath::set_size(const mfl::points size) {
    m_size = size.value() / 32.0;
}
