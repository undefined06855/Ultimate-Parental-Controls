#pragma once
#include <mfl/layout.hpp>

class MathBox : public cocos2d::CCLayerColor {
public:
    static MathBox* create(geode::ZStringView equation);
    bool init(geode::ZStringView equation);

    float toCocos(mfl::points points);

    void addLine(mfl::line line);
    void addGlyph(mfl::shaped_glyph glyph);
};
