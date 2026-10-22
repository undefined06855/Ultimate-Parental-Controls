#include <arc/time/Interval.hpp>
#include <asp/fs.hpp>

$on_mod(Loaded) {
    static long long writeTime = 0;
    arc::spawn([] -> arc::Future<> {
        auto interval = arc::interval(asp::Duration::fromMillis(20));
        while (true) {
            co_await interval.tick();

            long long newWriteTime = std::filesystem::last_write_time((geode::dirs::getGameDir() / "constants.json").toStdPath().unwrapOrDefault()).time_since_epoch().count();
            if (writeTime < newWriteTime) {
                writeTime = newWriteTime;
                geode::Loader::get()->queueInMainThread([] {
                    cocos2d::CCScene::get()->removeChildByID("ParentalGateLayer"_spr);

                    auto layer = ParentalGateLayer::create();
                    layer->m_noElasticity = true;
                    layer->setID("ParentalGateLayer"_spr);
                    layer->show();
                });
            }
        }
    });

    // geode::KeyboardInputEvent().listen([](const geode::KeyboardInputData& event) {
    //     if (event.key == cocos2d::enumKeyCodes::KEY_F23 && event.action == geode::KeyboardInputData::Action::Press) {
    //         cocos2d::CCScene::get()->removeChildByID("ParentalGateLayer"_spr);

    //     }
    // }).leak();
}
