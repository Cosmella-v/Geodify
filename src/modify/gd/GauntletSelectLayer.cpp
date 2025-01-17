#include "../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletSelectLayer.hpp>

using namespace geode::prelude;

class $modify(MyGauntletSelectLayer, GauntletSelectLayer) {
	bool init(int p0) {
		if (!GauntletSelectLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/GauntletSelectLayer")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};