#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include <Geode/ui/LazySprite.hpp>
#include <string>

using namespace geode::prelude;

class GYScreenshotPopup : public geode::Popup {
protected:
    Ref<LazySprite> m_sprite;

    std::string m_layerName;

    enum class PreviewType {
        SwelvyBG,
        Sapphire
    };

    PreviewType m_previewType = PreviewType::SwelvyBG;

    std::string getPreviewURL();
    void reloadPreview();

    bool init(int const& layer);
    void onDownloadFail();

    Ref<CCMenuItemSpriteExtra> m_swelvyBtn;
    Ref<CCMenuItemSpriteExtra> m_sapphireBtn;

    CCSize m_spriteTargetSize;

    void createToggleButtons();
    void removeToggleButtons();
    void fixSpriteSize();

public:
    static GYScreenshotPopup* create(int const& text);
    std::string extractLastSegment(const std::string& input);
};
