#include "MathBox.hpp"
#include "BigFontMath.hpp"
#include "SpecialGlyph.hpp"
#include <mfl/units.hpp>

MathBox* MathBox::create(geode::ZStringView equation) {
    auto ret = new MathBox;
    if (ret->init(equation)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool MathBox::init(geode::ZStringView equation) {
    if (!CCLayerColor::initWithColor({ 0, 0, 0, 60 })) return false;

    this->ignoreAnchorPointForPosition(false);

    auto layout = mfl::layout(equation, mfl::points(32), BigFontMath::create);
    if (layout.error.has_value()) {
        this->setContentSize({ 300.f, 50.f });

        auto errorLabel = geode::Label::create(layout.error.value(), "bigFont.fnt");
        errorLabel->setLimitLabelSize(this->getContentSize());
        this->addChildAtPosition(errorLabel, geode::Anchor::Center);

        return true;
    }

    this->setContentSize({ this->toCocos(layout.width), this->toCocos(layout.height) });

    for (auto line : layout.lines) {
        this->addLine(line);
    }

    for (auto glyph : layout.glyphs) {
        this->addGlyph(glyph);
    }

    return true;
}

float MathBox::toCocos(mfl::points points) {
    return points.value();
    // return mfl::points_to_pixels(points, mfl::dots_per_inch(120)).value();
}

void MathBox::addLine(mfl::line line) {
    // auto label = geode::Label::create("-", "bigFont.fnt");

    // auto emWidth = label->getContentWidth();
    // label->setText(std::string(std::ceil(this->toCocos(line.length) / emWidth), '-'));
    // label->setAnchorPoint({ 0.f, .5f });

    auto sprite = geode::NineSlice::create("line.png"_spr);
    sprite->setContentWidth(this->toCocos(line.length));
    sprite->setPosition({ this->toCocos(line.x), this->toCocos(line.y) });
    sprite->setAnchorPoint({ 0.f, .5f });

    this->addChild(sprite);
}

void MathBox::addGlyph(mfl::shaped_glyph glyph) {
    cocos2d::CCNode* node = nullptr;

    if (SpecialGlyph::isSpecialIDGlyph(glyph.index)) {
        node = SpecialGlyph::create(glyph);
    } else {
        node = geode::Label::create(std::string(1, glyph.index), "bigFont.fnt");
        node->setScale((this->toCocos(glyph.size) - 2.f) / node->getContentHeight()); // small adjustment here
        node->setAnchorPoint({ 0.f, 0.f });
    }


    if (glyph.family == mfl::font_family::italic) {
        node->setSkewX(10.f);
    }

    node->setPosition({ this->toCocos(glyph.x), this->toCocos(glyph.y) });
    this->addChild(node);
}
