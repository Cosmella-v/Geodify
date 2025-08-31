#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <Geode/modify/MenuLayer.hpp>
/// @todo: Fix this code - on Windows its fine, but on Android it bugs out.
/// I'm not going to work on this right now, but I'll leave it here for future reference. (@OmgRod)

#include <Geode/Geode.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>
using namespace geode::prelude;
struct FMODEngineSaved {
    gd::string name; bool shouldLoop; float fadeInTime; int channel;
}; FMODEngineSaved Saved;

class $modify(MyFMODAudioEngine, FMODAudioEngine) {
public:
    void playMusic(gd::string name, bool shouldLoop, float fadeInTime, int channel) {
        log::debug("Playing music: {}", name);
        std::string nameStr = name; 
        Saved.name = name;
        Saved.shouldLoop = shouldLoop;
        Saved.fadeInTime = fadeInTime;
        Saved.channel = channel;
        if (nameStr.find("menuLoop.mp3") != std::string::npos &&
            Mod::get()->getSettingValue<bool>("menu-loop")) 
        {
            log::debug("Changed music to: ninxout.wav");
            return FMODAudioEngine::playMusic("ninxout.wav"_spr, shouldLoop, fadeInTime, channel);
        }

        FMODAudioEngine::playMusic(name, shouldLoop, fadeInTime, channel);
    }
};

$on_mod(Loaded) {
	listenForSettingChanges("menu-loop", [](bool enabled) {
        if (Saved.name == "menuLoop.mp3") {
		    FMODAudioEngine::playMusic("menuLoop.mp3", Saved.shouldLoop, Saved.fadeInTime, Saved.channel);
        };
	});
};