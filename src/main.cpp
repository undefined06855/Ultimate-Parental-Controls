#include <Geode/modify/MenuLayer.hpp>

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto layer = ParentalGateLayer::create();
        layer->m_scene = this;
        layer->show();

        return true;
    }
};
