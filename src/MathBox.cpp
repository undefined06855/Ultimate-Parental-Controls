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
#ifdef _DEBUG
    if (!CCLayerColor::initWithColor({ 120, 120, 120, 255 })) return false;
#else
    if (!CCLayerColor::initWithColor({ 0, 0, 0, 80 })) return false;
#endif

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
    sprite->setZOrder(5);
    this->addChild(sprite);

#ifdef _DEBUG
    auto rect = cocos2d::CCLayerColor::create({ 0, 255, 255, 80 });
    rect->setContentSize({ this->toCocos(line.length), this->toCocos(line.thickness) });
    rect->setPosition({ this->toCocos(line.x), this->toCocos(line.y) });
    rect->setZOrder(10);
    this->addChild(rect);
#endif
}

void MathBox::addGlyph(mfl::shaped_glyph glyph) {
    cocos2d::CCNode* node = nullptr;

    if (SpecialGlyph::isSpecialIDGlyph(glyph.index)) {
        node = SpecialGlyph::create(glyph);
    } else {
        node = geode::Label::create(std::string(1, glyph.index), "bigFont.fnt");
        node->setScale(this->toCocos(glyph.size) / node->getContentHeight());
        node->setAnchorPoint({ 0.f, 0.f });
    }

    if (glyph.family == mfl::font_family::italic) {
        node->setSkewX(10.f);
    }

    node->setPosition({ this->toCocos(glyph.x), this->toCocos(glyph.y) });
    node->setZOrder(5);
    this->addChild(node);

#ifdef _DEBUG
    auto rect = cocos2d::CCLayerColor::create({ 255, 0, 255, 180 });
    rect->setContentSize({ 2.f, 2.f });
    rect->setPosition({ this->toCocos(glyph.x), this->toCocos(glyph.y) });
    rect->setZOrder(10);
    this->addChild(rect);
#endif
}
