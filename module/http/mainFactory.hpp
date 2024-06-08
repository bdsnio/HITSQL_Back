/*************************
* @date: 2024.6.7        *
* @author: Guo Yangfan   *
* @file: mainFactory.hpp *
*************************/
#ifndef MAINFACTORY_HPP
#define MAINFACTORY_HPP

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/URI.h>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include "handlers/staticHandler.hpp"
#include "handlers/templateHandler.hpp"
#include "handlers/xmlHandler.hpp"
#include "handlers/badHandler.hpp"

/// Factory for handling all file request, including .html and .css file
/// In this class, the factory will generate the handlers when clients 
/// require files to this server.
///
class mainHTTPRequestHandlerFactory : public
Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& req
    ) {
        Poco::URI uri(req.getURI());

        std::string result = findMatch(uri.getPath());
        std::cout << uri.getPath() << " : " << result << std::endl;

        if (result == "staticHandler") {
            return new staticHandler(srvName, siteRoot);
        }
        if (result == "templateHandler") {
            return new templateHandler(srvName, templateRoot);
        }
        if (result == "xmlHandler") {
            return new xmlHandler(srvName, siteRoot);
        }

        return new badHandler(srvName, siteRoot);
    }

    mainHTTPRequestHandlerFactory(std::string name) :
        srvName(name), siteRoot("www/") {
        setConfig(
            std::filesystem::current_path() /
            std::filesystem::path("config/config.json")
        );
    }

private:

    /// this.siteRoot-->(config.server.root)
    ///
    /// this.definiteMap-->(config.server.rules.defMap)
    ///
    /// this.ruleMap-->(config.server.rules.ruleMap)
    void setConfig(std::filesystem::path filePath);

    std::string findMatch(const std::string & text);

    std::string srvName;
    std::filesystem::path siteRoot;
    std::filesystem::path templateRoot;

    /// resource name <--> handler
    std::map<std::string, std::string> definiteMap;
    /// rele(string)  <--> handler
    std::map<std::string, std::string> ruleMap;
};

#endif // !MAINFACTORY_HPP