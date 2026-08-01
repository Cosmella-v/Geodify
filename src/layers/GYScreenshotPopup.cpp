#include "GYScreenshotPopup.hpp"
#include "../Tags.hpp"

bool GYScreenshotPopup::init(int const& layer) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    if (!Popup::init(winSize.width * .6f, winSize.height * .7f)) return false;

    Tags tags;
    auto layerName = tags.getStringFromTag(layer);

    if (layerName.empty()) {
        log::error("Layer name is empty for tag: {}", layer);
        return false;
    }

    std::string result = extractLastSegment(layerName);

    if (!m_mainLayer) {
        log::error("m_mainLayer is not initialized");
        return false;
    }

    this->setTitle(result);
    m_mainLayer->setContentSize({ winSize.width * 0.6f, winSize.height * 0.7f });
    m_mainLayer->updateLayout();

    std::string URL = fmt::format("https://raw.githubusercontent.com/OmgRod/Geodify/master/previews/{}Preview.png", layerName);

    CCSize spriteTargetSize{
        m_mainLayer->getContentSize().width * 0.75f,
        m_mainLayer->getContentSize().height * 0.75f
    };

    m_sprite = LazySprite::create(spriteTargetSize);
    m_sprite->setAutoResize(true);
    m_sprite->setLoadCallback([this, winSize, spriteTargetSize](Result<> res) {
        if (!res) {
            log::error("Failed to load image: {}", res.unwrapErr());
            onDownloadFail();

            // fallback texture

            auto sprite = LazySprite::create(spriteTargetSize);
            sprite->setAutoResize(true);
            sprite->loadFromFile(Mod::get()->getResourcesDir() / "noPreview.png");
            sprite->setPosition(this->m_sprite->getPosition());
            this->m_mainLayer->addChild(sprite);

            // report bug

            auto reportSpr = ButtonSprite::create("Report Bug");
            reportSpr->setScale(0.75f);
            auto reportBtn = CCMenuItemExt::createSpriteExtra(
                reportSpr,
                [this](CCObject* sender) {
                    geode::utils::web::openLinkInBrowser("https://github.com/OmgRod/Geodify/issues/new?template=bug_report.md");
                }
            );
            reportBtn->setPosition({ this->m_buttonMenu->getContentWidth() / 2, this->m_buttonMenu->getContentHeight() * 0.1f });
            this->m_buttonMenu->addChild(reportBtn);

            this->m_sprite->removeFromParent();
        }
    });

    m_sprite->loadFromUrl(URL);
    m_mainLayer->addChildAtPosition(m_sprite, Anchor::Center);

    return true;
}

void GYScreenshotPopup::onDownloadFail() {
    if (!m_sprite) return;

    m_sprite->initWithSpriteFrameName("noPreview.png"_spr);
    m_sprite->setScale(1.0f);
}

std::string GYScreenshotPopup::extractLastSegment(const std::string& input) {
    size_t lastDash = input.rfind('-');
    if (lastDash != std::string::npos) {
        return input.substr(lastDash + 1);
    }
    return input;
}

GYScreenshotPopup* GYScreenshotPopup::create(int const& text) {
    auto ret = new GYScreenshotPopup();
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    if (ret->init(text)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}
