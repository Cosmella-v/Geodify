#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/CreatorLayer.hpp>

using namespace geode::prelude;

ADD_TAG("gd-CreatorLayer")
class $modify(MyCreatorLayer, CreatorLayer) {
	bool init() {
		if (!CreatorLayer::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/CreatorLayer")){
			if (auto bg = this->getChildByID("background")){
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};