/*************************
* @date: 2024.6.7        *
* @modif: 2024.6.21      *
* @author: Guo Yangfan   *
* @file: mainFactory.cpp *
*************************/

#include "mainFactory.hpp"
#include "../config/config.hpp"
#include <regex>
#include <string>

void mainHTTPRequestHandlerFactory::setConfig() {

    using namespace Poco;

    auto config = Config::getInstance().getConfig();

        siteRoot = config["server"]["root"].value<std::string>();
        templateRoot = config["server"]["template"].value<std::string>();

        // definite rules
        auto config_defMap = config.get_as<toml::array>("defMap");
        for (auto&& pair : *config_defMap) {
            auto tbl = *pair.as_table();
            std::string handler = tbl["handler"].value<std::string>().value();
            auto rules = tbl.get_as<toml::array>("rule");
            for (auto&& ele : *rules) {
                definiteMap[ele.value<std::string>().value()] = handler;
            }
        }

        // regrex rules, repeat code above.
        auto config_ruleMap = config.get_as<toml::array>("ruleMap");
        for (auto&& pair : *config_ruleMap) {
            auto tbl = *pair.as_table();
            std::string handler = tbl["handler"].value<std::string>().value();
            auto rules = tbl.get_as<toml::array>("rule");
            for (auto&& ele : *rules) {
                ruleMap[ele.value<std::string>().value()] = handler;
            }
        }
}

std::string mainHTTPRequestHandlerFactory::findMatch(const std::string& text) {

    for (auto & pattern : definiteMap) {
        if (text == pattern.first) {
            return pattern.second;
        }
    }
    for (auto & pattern : ruleMap) {
        if (std::regex_match(text, std::regex(pattern.first))) {
            return pattern.second;
        }
    }

    return "No Match";
}
