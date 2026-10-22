#include "ParentalGateLayer.hpp"
#include "../MathBox.hpp"
#include <asp/iter.hpp>

bool HookedParentalGateLayer::init() {
    if (!ParentalGateLayer::init()) return false;
    auto fields = m_fields.self();

    auto background = m_mainLayer->getChildByType<cocos2d::extension::CCScale9Sprite*>();
    if (!background) return true;
    background->setContentSize({ 360.f, background->getContentHeight() + 30.f });

    for (auto [ i, button ] : asp::iter::enumerate(m_buttonMenu->getChildrenExt())) {
        if (i == 0) {
            // close button
            button->setPosition(button->getPosition() + cocos2d::CCPoint{ -45.f, 15.f });
        } else {
            // keypad digits
            button->setPosition(button->getPosition() + cocos2d::CCPoint{ 0.f, -15.f });

            // backspace
            if (button->getTag() == 10) {
                auto threeButton = m_buttonMenu->getChildByTag(3);
                if (!threeButton) continue;

                button->setPosition(threeButton->getPosition() + cocos2d::CCPoint{ 60.f, 0.f });
            }
        }
    }

    auto decimalPoint = CCMenuItemSpriteExtra::create(ButtonSprite::create(".", 30.f, 30.f, 1.f, true, "bigFont.fnt", "GJ_button_01.png", 40.f), this, menu_selector(HookedParentalGateLayer::onDecimalPoint));
    auto sevenButton = m_buttonMenu->getChildByTag(7);
    auto zeroButton = m_buttonMenu->getChildByTag(0);
    if (!sevenButton || !zeroButton) return true;
    decimalPoint->setPosition({ sevenButton->getPositionX(), zeroButton->getPositionY() });
    m_buttonMenu->addChild(decimalPoint);

    auto title = m_mainLayer->getChildByType<cocos2d::CCLabelBMFont*>(0);
    if (!title) return true;
    title->setPositionY(title->getPositionY() + 18.f);

    auto input = m_mainLayer->getChildByType<cocos2d::CCLabelBMFont*>(1);
    if (!input) return true;

    m_inputLabel->setPositionY(m_inputLabel->getPositionY() - 25.f);
    m_inputLabel->setScale(.6f);
    m_inputLabel->setString("x = ");
    m_prefixString = "x = ";

    m_minimum = 1;
    m_maximum = 5;

    fields->box = nullptr;
    this->addMathBox();

    return true;
}

void HookedParentalGateLayer::onDone(cocos2d::CCObject* sender) {
    auto fields = m_fields.self();

    auto input = geode::utils::numFromString<double>(m_inputString);
    if (input.isErr()) {
        this->onIncorrect();
        return;
    }

    auto solution = input.unwrap();
    if (solution != fields->solution) {
        this->onIncorrect();
        return;
    }

    // :tada:
    ParentalOptionsLayer::create()->show();
    this->onClose(nullptr);
}

// TODO: get from api
void HookedParentalGateLayer::addMathBox() {
    auto fields = m_fields.self();
    if (fields->box) fields->box->removeFromParent();

    auto winSize = cocos2d::CCDirector::get()->getWinSize();
    fields->box = MathBox::create(R"(\int_{0}^{x}(\frac{d}{dt}[t^{3}]+\frac{12t}{\pi^{2}}\sum_{k=1}^{\infty}\frac{1}{k^{2}})dt = \frac{24}{\sqrt{\pi}}\int_{0}^{\infty}e^{-s^{2}}ds \cdot \lim_{n\to\infty}(1+\frac{1}{n})^{n}e^{-1} \cdot \frac{2}{\pi}\int_{0}^{\pi}\sin^{2}\theta d\theta)");
    fields->box->setPosition({ winSize.width / 2.f, 262.f });
    fields->box->setScale(std::min(0.6f, 320.f / fields->box->getContentWidth()));
    m_mainLayer->addChild(fields->box);

    fields->solution = 2.f;
}

void HookedParentalGateLayer::onDecimalPoint(cocos2d::CCObject* sender) {
    if (m_inputString.length() == m_maximum) return;
    if (m_inputString.contains(".")) return;
    m_inputString += ".";
    this->updateNumberState();
}

void HookedParentalGateLayer::onIncorrect() {
    this->addChild(TextAlertPopup::create("Wrong answer!", .8f, .6f, 150, "bigFont.fnt"));
    m_inputString = "";
    this->updateNumberState();
    this->addMathBox();
}
