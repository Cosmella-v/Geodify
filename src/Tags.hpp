#pragma once

#include <Geode/Geode.hpp>
#include <unordered_map>
#include <string_view>

using namespace geode::prelude;
class Tags {
public:
    inline static int gm_id = 0;
    static inline std::unordered_map<std::string, int> gm_tagMap;
    static inline std::unordered_map<int, std::string> gm_stringMap;
    static const inline std::vector<std::string> modData = {
        "gd",
        "geode.loader",
        "arcticwoof.rated_layouts",
        "cvolton.betterinfo",
        "dankmeme.globed2",
        "geode.texture-loader",
        "hiimjustin000.integrated_demonlist",
        "km7dev.gdps-switcher",
        "limegradient.betterachievements",
        "minemaker0430.gddp_integration",
        "omgrod.garage_plus",
        "omgrod.gdstream",
        "omgrod.geodify",
        "thesillydoggo.newgrounds_explorer",
        "uproxide.textures",
        "teamtcm.geometry-dash-odyssey",
        "gdutilsdevs.gdutils",
        "lblazen.gdps_hub",
        "gdcpteam.challenge-list",
        "alphalaneous.random_tab",
        "omgrod.geometry-dash-surge",
        "timestepyt.secretlayer6",
        "abb2k.gdwt",
        "omgrod.thatdarncoin",
        "delivel.level-grind",
    };
    static void addTag(std::string name) {
        int value = gm_id;
        gm_id+=1;
        log::debug("{} {}",name, value);
        gm_tagMap.emplace(name, value);
        gm_stringMap.emplace(value, name);
    }

     int getTagFromString(std::string name) {
        auto it = gm_tagMap.find(name);
        if (it != gm_tagMap.end()) {
            log::debug("Found tag: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", name);
        return -1;
    }

    std::string getStringFromTag(int tag) {
        auto it = gm_stringMap.find(tag);
        if (it != gm_stringMap.end()) {
            log::debug("Found string: {}", it->second);
            return it->second;
        }
        log::error("Unknown tag: {}", tag);
        return "Unknown";
    }
};

#define __CONCAT_DETAIL(x, y) x##y
#define __CONCAT(x, y) __CONCAT_DETAIL(x, y)

#define ADD_TAG(name) \
    namespace { \
        struct __CONCAT(AutoRegisterTag_, __LINE__) { \
            __CONCAT(AutoRegisterTag_, __LINE__)() { \
                Tags::addTag(name); \
            } \
        } __CONCAT(autoRegisterTag_, __LINE__); \
    } \
    static_assert(true, "")

