#include "../../SwelvyBG.hpp"
#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>

using namespace geode::prelude;
ADD_TAG("gd-LoadingLayer")
class $modify(MyLoadingLayer, LoadingLayer) {
	bool init(bool p0) {
		if (!LoadingLayer::init(p0)) {
			return false;
		}
		if (Mod::get()->getSettingValue<bool>("gd/LoadingLayer")) {
			if (auto bg = this->getChildByID("bg-texture")) {
				bg->setVisible(false);
			}

			auto swelvyBG = SwelvyBG::create();
			swelvyBG->setZOrder(-3);
			

			this->addChild(swelvyBG);
		}

		return true;
	}
};