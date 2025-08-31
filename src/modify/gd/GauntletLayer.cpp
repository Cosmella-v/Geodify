#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/GauntletLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-GauntletLayer")	
class $modify(MyGauntletLayer, GauntletLayer) {
	bool init(GauntletType p) {
		if (!GauntletLayer::init(p)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/GauntletLayer")){
			auto bg = typeinfo_cast<CCNode*>(this->getChildren()->objectAtIndex(0));
			bg->setVisible(false);
			
			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-2);
			

			this->addChild(swelvyBG);
		}
		return true;
	}
};