#pragma once
#include <Geode/modify/ParentalGateLayer.hpp>

class $modify(HookedParentalGateLayer, ParentalGateLayer) {
    bool init();
    void onDone(cocos2d::CCObject* sender);
};
