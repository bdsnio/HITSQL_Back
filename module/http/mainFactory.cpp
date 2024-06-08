/*************************
* @date: 2024.6.7        *
* @author: Guo Yangfan   *
* @file: mainFactory.cpp *
*************************/

#include "mainFactory.hpp"
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <regex>
#include <string>

void mainHTTPRequestHandlerFactory::setConfig(std::filesystem::path filePath) {

    using namespace Poco;
    std::fstream fstr(filePath);
    if (fstr.is_open()) {
        std::string fileContent(
            (std::istreambuf_iterator<char>(fstr)),
            std::istreambuf_iterator<char>()
        );

        JSON::Parser jsonParser;
        Dynamic::Var result = jsonParser.parse(fileContent);

        JSON::Object::Ptr pObject = result.extract<JSON::Object::Ptr>();
        JSON::Object::Ptr pObject_srv = pObject->getObject("server");

        siteRoot = pObject_srv->getValue<std::string>("root");
        templateRoot = pObject_srv->getValue<std::string>("template");
        JSON::Object::Ptr pObject_r = pObject_srv->getObject("rules");

        // definite rules
        JSON::Array::Ptr pArray_defMap =
            pObject_r->get("defMap").extract<Poco::JSON::Array::Ptr>();
        for (const auto & map : *pArray_defMap) {
            auto pObject_rule =
                map.extract<Poco::JSON::Object::Ptr>();
            std::string handler = pObject_rule->getValue<std::string>("handler");
            auto pArray_rule =
                pObject_rule->get("rule").extract<Poco::JSON::Array::Ptr>();
            for (const auto & element : *pArray_rule) {
                definiteMap[element.toString()] = handler;
            }
        }

        // regrex rules, repeat code above.
        JSON::Array::Ptr pArray_ruleMap =
            pObject_r->get("ruleMap").extract<Poco::JSON::Array::Ptr>();
        for (const auto & map : *pArray_ruleMap) {
            auto pObject_rule =
                map.extract<Poco::JSON::Object::Ptr>();
            std::string handler = pObject_rule->getValue<std::string>("handler");
            auto pArray_rule =
                pObject_rule->get("rule").extract<Poco::JSON::Array::Ptr>();
            for (const auto & element : *pArray_rule) {
                ruleMap[element.toString()] = handler;
            }
        }

        fstr.close();
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
