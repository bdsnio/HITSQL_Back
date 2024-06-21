/*************************
* @date: 2024.6.7        *
* @modif: 2024.6.21      *
* @author: Guo Yangfan   *
* @file: mainFactory.cpp *
*************************/

#include "mainFactory.hpp"
#include "../config/config.hpp"
#include "handlerBase.hpp"
#include <regex>
#include <string>

std::unique_ptr<std::map<std::string, std::string>> requestHandlerBase::ruleMap = nullptr;

void mainHTTPRequestHandlerFactory::setConfig() {

    using namespace Poco;

    auto config = Config::getInstance().getConfig();

    siteRoot = config["server"]["root"].value<std::string>();
    templateRoot = config["server"]["template"].value<std::string>();

    // special rules
    auto config_specMap = config.get_as<toml::array>("specMap");
    for (auto &&pair : *config_specMap) {
      auto tbl = *pair.as_table();
      auto rules = tbl.get_as<toml::array>("rule");
      for (auto &&ele : *rules) {
        auto keyValueMap = *ele.as_table();
        specialMap[keyValueMap["from"].value<std::string>().value()] =
            keyValueMap["to"].value<std::string>().value();
      }
    }
    requestHandlerBase::ruleMap.reset(&specialMap);

    // definite rules
    auto config_defMap = config.get_as<toml::array>("defMap");
    for (auto &&pair : *config_defMap) {
      auto tbl = *pair.as_table();
      std::string handler = tbl["handler"].value<std::string>().value();
      auto rules = tbl.get_as<toml::array>("rule");
      for (auto &&ele : *rules) {
        definiteMap[ele.value<std::string>().value()] = handler;
      }
    }

    // regrex rules, repeat code above.
    auto config_ruleMap = config.get_as<toml::array>("ruleMap");
    for (auto &&pair : *config_ruleMap) {
      auto tbl = *pair.as_table();
      std::string handler = tbl["handler"].value<std::string>().value();
      auto rules = tbl.get_as<toml::array>("rule");
      for (auto &&ele : *rules) {
        ruleMap[ele.value<std::string>().value()] = handler;
      }
    }
}

std::string mainHTTPRequestHandlerFactory::findMatch(const std::string &text) {

  std::string text2 = (specialMap[text].empty()) ? text : specialMap[text];

  for (auto &pattern : definiteMap) {
    if (text2 == pattern.first) {
      return pattern.second;
    }
  }
  for (auto &pattern : ruleMap) {
    if (std::regex_match(text2, std::regex(pattern.first))) {
      return pattern.second;
    }
  }

  return "No Match";
}
