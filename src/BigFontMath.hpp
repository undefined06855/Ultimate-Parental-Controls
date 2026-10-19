#pragma once
#include <mfl/abstract_font_face.hpp>

class BigFontMath : public mfl::abstract_font_face {
public:
    static std::unique_ptr<BigFontMath> create(const mfl::font_family font);

    double m_size;

    virtual mfl::math_constants constants() const override;
    virtual mfl::math_glyph_info glyph_info(const size_t glyph_index) const override;
    virtual size_t glyph_index_from_code_point(const mfl::code_point char_code, const bool use_large_variant) const override;
    virtual std::vector<mfl::size_variant> horizontal_size_variants(const mfl::code_point char_code) const override;
    virtual std::vector<mfl::size_variant> vertical_size_variants(const mfl::code_point char_code) const override;
    virtual std::optional<mfl::glyph_assembly> horizontal_assembly(const mfl::code_point char_code) const override;
    virtual std::optional<mfl::glyph_assembly> vertical_assembly(const mfl::code_point char_code) const override;
    virtual void set_size(const mfl::points size) override;
};
