#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <macros.hpp>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

#define MERGE_JSON "geodeify.json"
#define OUTPUT_JSON "mod.json"

std::string replaceUnderscores(std::string value) {
    for (char& character : value) {
        if (character == '_') {
            character = ' ';
        }
    }

    return value;
}

int main() {
    try {
        std::cout << "Creating mod.json for geode!\n";

        const std::regex commentPattern(
            R"(//\[\[omgrod\.geodify/TAG\]\]\s*([^\s:]+))"
        );

        const std::regex macroPattern(
            "ADD_TAG\\s*\\(\\s*\"([^\"]*)\"\\s*\\)"
        );

        json tagSettings = json::object();

        if (!fs::exists(SOURCE_DIRECTORY)) {
            std::cerr<< "Error: Mod's code folder doesn't exist?"<< SOURCE_DIRECTORY<< '\n';
            return 1;
        }

        for (const auto& entry :
             fs::recursive_directory_iterator(SOURCE_DIRECTORY)) {

            if (!entry.is_regular_file()) {
                continue;
            }

            if (entry.path().extension() != ".cpp") {
                continue;
            }

            std::ifstream file(entry.path());

            if (!file) {
                std::cerr<< "Warning: failed to open "<< entry.path().string()<< '\n';
                continue;
            }
            std::string line;
            while (std::getline(file, line)) {
                std::smatch match;

                bool found = std::regex_search(
                    line,
                    match,
                    commentPattern
                );
                if (!found) {
                    found = std::regex_search(
                        line,
                        match,
                        macroPattern
                    );
                }

                if (!found) {
                    continue;
                }

                const std::string name = match[1].str();

                const std::size_t separator = name.rfind('-');

                std::string beforeLast;
                std::string afterLast;

                if (separator == std::string::npos) {
                    afterLast = name;
                } else {
                    beforeLast = name.substr(0, separator);
                    afterLast = name.substr(separator + 1);
                }

                std::string key;

                if (!beforeLast.empty()) {
                    key = beforeLast + "/" + afterLast;
                } else {
                    key = afterLast;
                }

                if (tagSettings.contains(key)) {
                    continue;
                }

                tagSettings[key] = {
                    {
                        "name",
                        replaceUnderscores(afterLast)
                    },
                    {
                        "description",
                        afterLast
                    },
                    {
                        "type",
                        "bool"
                    },
                    {
                        "default",
                        false
                    }
                };

                std::cout
                    << "Found tag: "
                    << name
                    << " -> "
                    << key
                    << '\n';
            }
        }

        json modData = json::object();

        if (fs::exists(MERGE_JSON)) {
            std::ifstream input(MERGE_JSON);

            if (!input) {
                std::cerr
                    << "Error: failed to open "
                    << MERGE_JSON
                    << '\n';

                return 1;
            }

            try {
                input >> modData;
            } catch (const json::parse_error& error) {
                std::cerr
                    << "Error: failed to parse "
                    << MERGE_JSON
                    << ":\n"
                    << error.what()
                    << '\n';

                return 1;
            }
        }

        if (!modData.contains("settings") ||
            !modData["settings"].is_object()) {

            modData["settings"] = json::object();
        }

        json& existingSettings = modData["settings"];
        json newSettings = json::object();

        bool inserted = false;

        for (auto& [key, value] : existingSettings.items()) {
            if (key == "other-title" && !inserted) {
                for (auto& [newKey, newValue] : tagSettings.items()) {
                    if (!existingSettings.contains(newKey)) {
                        newSettings[newKey] = newValue;
                    }
                }

                inserted = true;
            }

            newSettings[key] = value;
        }

        if (!inserted) {
            for (auto& [newKey, newValue] : tagSettings.items()) {
                if (!existingSettings.contains(newKey)) {
                    newSettings[newKey] = newValue;
                }
            }
        }

        modData["settings"] = std::move(newSettings);

        std::ofstream output(OUTPUT_JSON);

        if (!output) {
            std::cerr
                << "Error: failed to create "
                << OUTPUT_JSON
                << '\n';

            return 1;
        }

        output << modData.dump(4) << '\n';

        std::cout
            << "Processed "
            << tagSettings.size()
            << " tags and generated "
            << OUTPUT_JSON
            << '\n';

        return 0;
    }

    catch (const fs::filesystem_error& error) {
        std::cerr
            << "Filesystem error: "
            << error.what()
            << '\n';

        return 1;
    }

    catch (const json::exception& error) {
        std::cerr
            << "JSON error: "
            << error.what()
            << '\n';

        return 1;
    }

    catch (const std::exception& error) {
        std::cerr
            << "Error: "
            << error.what()
            << '\n';

        return 1;
    }
}