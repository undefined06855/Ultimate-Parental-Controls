#include "ParentalGateLayer.hpp"

bool HookedParentalGateLayer::init() {
    if (!ParentalGateLayer::init()) return false;

    geode::log::info("unk {}", m_inputtedValue);
    geode::log::info("unk2 {}", (cocos2d::CCObject*)m_unknown);
    geode::log::info("solution {}", m_solution);

    return true;
}

void HookedParentalGateLayer::onDone(cocos2d::CCObject* sender) {
    this->retain();
    ParentalGateLayer::onDone(sender);

    geode::log::info("unk {}", m_inputtedValue);
    geode::log::info("unk2 {}", (cocos2d::CCObject*)m_unknown);
    geode::log::info("solution {}", m_solution);
    this->release();
}
