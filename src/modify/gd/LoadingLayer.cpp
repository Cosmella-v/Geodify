#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-LoadingLayer");
class $modify(MyLoadingLayer, LoadingLayer) {
	bool init(bool p0) {
		if (!LoadingLayer::init(p0)) return false;

		if (Mod::get()->getSettingValue<bool>("gd/LoadingLayer")) {
			if (auto bg = this->getChildByID("bg-texture")) {
				bg->setVisible(false);
			}

			auto winSize = CCDirector::sharedDirector()->getWinSize();

			/*if (Mod::get()->getSettingValue<std::string>("background-type") == "Sapphire") {
				CCTextureCache::sharedTextureCache()->addImage("sapphire-bg.png"_spr, false);
				auto background = LazySprite::create(winSize, false);
				background->initWithFile("sapphire-bg.png"_spr);
				background->setZOrder(-999);
				this->addChild(background);
			} else {
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-999);
				this->addChild(swelvyBG);
			}*/

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-999);
			this->addChild(swelvyBG);
		}

		return true;
	}
};
