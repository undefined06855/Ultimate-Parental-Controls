#include "SpecialGlyph.hpp"

static size_t s_firstSpecialGlyphID = 10000;
static std::unordered_map<size_t, SpecialGlyphType> s_specialGlyphs;

size_t SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType charCode) {
    size_t id = s_firstSpecialGlyphID;
    while (s_specialGlyphs.contains(id)) id++;

    s_specialGlyphs[id] = charCode;

    return id;
}

bool SpecialGlyph::isSpecialIDGlyph(size_t index) {
    return index >= s_firstSpecialGlyphID && s_specialGlyphs.contains(index);
}

SpecialGlyph* SpecialGlyph::create(mfl::shaped_glyph glyph) {
    auto ret = new SpecialGlyph;
    if (ret->init(glyph)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool SpecialGlyph::init(mfl::shaped_glyph glyph) {
    if (!CCNode::init()) return false;
    if (!SpecialGlyph::isSpecialIDGlyph(glyph.index)) return false;

    auto charCode = s_specialGlyphs[glyph.index];

    cocos2d::CCNode* child = nullptr;
    switch (charCode) {
        case SpecialGlyphType::Unknown: {
            auto wrapper = cocos2d::CCLayerColor::create({ 255, 0, 0, 120 });
            wrapper->setContentSize({ (float)glyph.size.value(), (float)glyph.size.value() });
            wrapper->setAnchorPoint({ .5f, .5f });
            wrapper->ignoreAnchorPointForPosition(false);

            auto unknown = geode::Label::create("?", "bigFont.fnt");
            unknown->setLimitLabelSize(wrapper->getContentSize() - 5.f);
            wrapper->addChildAtPosition(unknown, geode::Anchor::Center);

            child = wrapper;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Integral: {
            auto integral = geode::NineSlice::create("integral.png"_spr);
            integral->setContentHeight(glyph.size.value());
            child = integral;
            this->setAnchorPoint({ 0.f, .5f });
        } break;

        case SpecialGlyphType::Summation: {
            auto summation = cocos2d::CCSprite::create("summation.png"_spr);
            child = summation;
            this->setAnchorPoint({ .25f, .1f });
        } break;

        case SpecialGlyphType::Pi: {
            auto pi = cocos2d::CCSprite::create("pi.png"_spr);
            pi->setScale(glyph.size.value() / pi->getContentHeight());
            child = pi;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Infinity: {
            auto infinity = cocos2d::CCSprite::create("infinity.png"_spr);
            infinity->setScale((glyph.size.value() - 12.f) / infinity->getContentHeight());
            child = infinity;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Equivalent: {
            auto equivalent = cocos2d::CCSprite::create("equivalent.png"_spr);
            equivalent->setScale((glyph.size.value() - 15.f) / equivalent->getContentHeight());
            child = equivalent;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Implies: {
            auto implies = cocos2d::CCSprite::createWithSpriteFrameName("d_sign_img_02_001.png");
            implies->setScale((glyph.size.value() - 15.f) / implies->getContentHeight());
            child = implies;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::ImpliedBy: {
            auto impliedBy = cocos2d::CCSprite::createWithSpriteFrameName("d_sign_img_02_001.png");
            impliedBy->setScale((glyph.size.value() - 15.f) / impliedBy->getContentHeight());
            impliedBy->setFlipX(true);
            child = impliedBy;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;
    }

    if (child) {
        this->setContentSize(child->getScaledContentSize());
        this->addChildAtPosition(child, geode::Anchor::Center);
    }

    return true;
}
