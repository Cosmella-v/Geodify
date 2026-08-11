#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class FakePopup : public FLAlertLayer {
  public:
	static FakePopup *create(CCLayer *fake) {
		auto ret = new FakePopup();
		if (ret->init(fake)) {
			ret->autorelease();
			return ret;
		}
		delete ret;
		return nullptr;
	}
	void close() {
		setKeypadEnabled(false);
		setKeyboardEnabled(false);
		setTouchEnabled(false);
		removeFromParent();
	}

  protected:
	bool FakePopup::init(CCLayer *layer) {
		if (!FLAlertLayer::init(150))
			return false;

		setID("FakeLayerWrapper");

		m_noElasticity = true;

		if (m_mainLayer)
			m_mainLayer->removeFromParent();

		m_mainLayer = layer;
		addChild(layer);
		return true;
	};
    void registerWithTouchDispatcher() {
        CCTouchDispatcher::get()->addTargetedDelegate(this, -500, true);
    }

    void keyDown(enumKeyCodes key, double timestamp) {
        m_mainLayer->keyDown(key, timestamp);
    }
};

class GYSettingSelectLayer : public CCLayer {
  public:
	virtual void keyBackClicked();
	static CCScene *scene();
	static GYSettingSelectLayer *create();
	static FakePopup *popup();
	bool init();
	void settingsBtn(CCObject *sender);
	void colorPopup(CCObject *sender);
	void backWrapper(CCObject *sender);
	void openNormalSettings(CCObject *sender);

  protected:
	bool m_isPopup = false;
};