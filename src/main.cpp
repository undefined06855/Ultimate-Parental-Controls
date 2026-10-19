#include <Geode/modify/MenuLayer.hpp>
#include <mfl/layout.hpp>
#include "MathBox.hpp"

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        this->removeAllChildrenWithCleanup(false);
        this->addChild(m_menuGameLayer);
        for (auto child : m_menuGameLayer->getChildrenExt()) {
            if (!geode::cast::exact_cast<cocos2d::CCSprite*>(child)) child->setVisible(false);
        }

        auto box = MathBox::create(R"(x^2)");
        box->setZOrder(20);
        box->setPosition(36.f, 28.f);
        this->addChild(box);

        box = MathBox::create(R"((x)^2)");
        box->setZOrder(20);
        box->setPosition(98.f, 28.f);
        this->addChild(box);

        box = MathBox::create(R"(f(x)=-\frac{123}{234\pi})");
        box->setZOrder(20);
        box->setPosition(413.f, 43.f);
        this->addChild(box);

        box = MathBox::create(R"(\frac{d}{{dx}}x^n  = nx^{\left( {n - 1} \right)})");
        box->setZOrder(20);
        box->setPosition(128.f, 285.f);
        this->addChild(box);

        box = MathBox::create(R"(u(n) \Leftrightarrow \frac{1}{{(1 - e^{ - j\omega } )}} + \sum\limits_{k =  - \infty }^\infty  {\pi \delta (\omega  + 2\pi k)})");
        box->setScale(.7f);
        box->setZOrder(20);
        box->setPosition(this->getContentSize() / 2.f);
        this->addChild(box);

        return true;
    }
};
