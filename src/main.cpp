#include <Geode/modify/MenuLayer.hpp>
#include <mfl/layout.hpp>
#include "MathBox.hpp"

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        this->removeAllChildrenWithCleanup(false);
        this->addChild(m_menuGameLayer);
        for (auto child : m_menuGameLayer->getChildrenExt()) {
            if (auto cast = geode::cast::exact_cast<cocos2d::CCSprite*>(child)) cast->setOpacity(255);
            else child->setVisible(false);
        }

        this->load();

        return true;
    }

    void keyDown(cocos2d::enumKeyCodes key, double timestamp) {
        this->load();
    }

    void load() {
        for (auto child : this->getChildrenExt()) { if (geode::cast::exact_cast<MathBox*>(child)) child->setTag(69); }
        for (int i = 0; i < 500; i++) this->removeChildByTag(69);

        MathBox* box = nullptr;

        // box = MathBox::create(R"(x^2)");
        // box->setZOrder(20);
        // box->setPosition(36.f, 28.f);
        // this->addChild(box);

        // box = MathBox::create(R"((x)^2)");
        // box->setZOrder(20);
        // box->setPosition(98.f, 28.f);
        // this->addChild(box);

        // box = MathBox::create(R"(f(x)=-\frac{123}{234\pi})");
        // box->setZOrder(20);
        // box->setPosition(413.f, 43.f);
        // this->addChild(box);

        box = MathBox::create(R"(\frac{d}{{dx}}x^n  = nx^{\left( {n - 1} \right)})");
        box->setZOrder(20);
        box->setPosition(128.f, 285.f);
        this->addChild(box);

        box = MathBox::create(R"(u(n) \Leftrightarrow \frac{1}{{(1 - e^{ - j\omega } )}} + \sum\limits_{k =  - \infty }^\infty  {\pi \delta (\omega  + 2\pi k)})");
        box->setScale(.7f);
        box->setZOrder(20);
        box->setPosition({ 220.f, 40.f });
        this->addChild(box);

        box = MathBox::create(R"(\int(123 \sqrt[3\pi]{\frac{\infty}{4\pi}} 123)dx)");
        box->setZOrder(20);
        box->setPosition(this->getContentSize() / 2.f);
        this->addChild(box);

        // box = MathBox::create(R"(\int_{\frac{1}{\frac{2}{\frac{3}{\frac{4}{\frac{5}{\frac{6}{\frac{7}{8}}}}}}}}^{\frac{1}{\frac{2}{\frac{3}{\frac{4}{\frac{5}{\frac{6}{\frac{\frac{6}{\frac{7}{7}}}{8}}}}}}}})");
        // box->setZOrder(20);
        // box->setPosition(this->getContentSize() / 2.f);
        // this->addChild(box);

        box = MathBox::create(R"(x_{123}^{123})");
        box->setZOrder(20);
        box->setPosition({ 403.f, 285.f });
        this->addChild(box);
    }
};
