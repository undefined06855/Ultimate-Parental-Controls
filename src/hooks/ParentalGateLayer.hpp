#pragma once
#include <Geode/modify/ParentalGateLayer.hpp>
#include "../MathBox.hpp"

class $modify(HookedParentalGateLayer, ParentalGateLayer) {
    struct Fields {
        MathBox* box;
        double solution;
    };

    bool init();
    void onDone(cocos2d::CCObject* sender);

    void addMathBox();
    void onDecimalPoint(cocos2d::CCObject* sender);
    void onIncorrect();
};
