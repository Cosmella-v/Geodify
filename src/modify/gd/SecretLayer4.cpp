#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/SecretLayer4.hpp>

using namespace geode::prelude;
ADD_TAG("gd-SecretLayer4")
class $modify(MySecretLayer4, SecretLayer4) {
	bool init() {
		if (!SecretLayer4::init()) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/SecretLayer4")){
			if (auto bg = this->getChildByID("background")) {
				bg->setVisible(false);
				auto swelvyBG = SwelvyBG::create();
				swelvyBG->setZOrder(-3);
				
	
				this->addChild(swelvyBG);				
			}
		}
		return true;
	}
};
