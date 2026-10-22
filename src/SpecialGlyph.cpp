#include "SpecialGlyph.hpp"

static size_t s_firstSpecialGlyphID = 10000;
static std::vector<std::pair<SpecialGlyphType, int>> s_glyphIDs = {};

size_t SpecialGlyph::generateSpecialGlyphID(SpecialGlyphType charCode, int variation) {
    for (int i = 0; i < s_glyphIDs.size(); i++) {
        if (s_glyphIDs[i].first == charCode && s_glyphIDs[i].second == variation) {
            return s_firstSpecialGlyphID + i;
        }
    }

    s_glyphIDs.push_back({ charCode, variation });
    return s_firstSpecialGlyphID + (s_glyphIDs.size() - 1);
}

std::pair<SpecialGlyphType, int>& SpecialGlyph::lookupSpecialGlyphID(size_t id) {
    return s_glyphIDs.at(id - s_firstSpecialGlyphID);
}

bool SpecialGlyph::isSpecialIDGlyph(size_t index) {
    return index >= s_firstSpecialGlyphID;
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

    auto& [type, variation] = SpecialGlyph::lookupSpecialGlyphID(glyph.index);
    m_type = type;

    cocos2d::CCNode* child = nullptr;
    switch (type) {
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
            integral->setContentHeight(/*glyph.size.value()*/ 50.f);
            child = integral;
            this->setAnchorPoint({ 0.f, .2f });
        } break;

        case SpecialGlyphType::Summation: {
            auto summation = cocos2d::CCSprite::create("summation.png"_spr);
            child = summation;
            this->setAnchorPoint({ .25f, .1f });
        } break;

        case SpecialGlyphType::Infinity: {
            auto infinity = cocos2d::CCSprite::create("infinity.png"_spr);
            infinity->setScale((glyph.size.value() - 12.f) / infinity->getContentHeight());
            child = infinity;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Pi: {
            auto pi = cocos2d::CCSprite::create("pi.png"_spr);
            pi->setScale(glyph.size.value() / pi->getContentHeight());
            child = pi;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Theta: {
            auto theta = cocos2d::CCSprite::create("theta.png"_spr);
            theta->setScale(glyph.size.value() / theta->getContentHeight());
            child = theta;
            this->setAnchorPoint({ 0.f, 0.f });
        } break;

        case SpecialGlyphType::Root: {
            auto root = geode::NineSlice::create("root.png"_spr);
            root->setInsetTop(10.f);
            root->setInsetBottom(14.5f);
            root->setInsetLeft(20.f);
            root->setInsetRight(3.f);
            root->setContentHeight(variation);
            child = root;
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

mfl::math_glyph_info SpecialGlyph::getGlyphInfo() {
    switch (m_type) {
        case SpecialGlyphType::Root: {
            return {
                .width = (int)this->getContentWidth() - 5,
                .height = (int)this->getContentHeight(),
                .depth = 20
            };
        }

        case SpecialGlyphType::Pi: {
            return {
                .width = (int)this->getContentWidth(),
                .height = (int)this->getContentHeight() - 5,
                .depth = -30
            };
        }

        case SpecialGlyphType::Integral: {
            return {
                .width = (int)this->getContentWidth(),
                .height = (int)this->getContentHeight() - 30,
                .depth = -10
            };
        }

        default: {
            return {
                .width = (int)this->getContentWidth(),
                .height = (int)this->getContentHeight(),
                .depth = 0
            };
        }
    }
}
