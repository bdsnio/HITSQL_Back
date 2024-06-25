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
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

#include "handlers/staticHandler.hpp"
#include "handlers/templateHandler.hpp"
#include "handlers/xmlHandler.hpp"
#include "handlers/badHandler.hpp"
#include "handlers/postHandler.hpp"

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

        if (req.getMethod() == Poco::Net::HTTPServerRequest::HTTP_POST) {
            return new postHandler(srvName.value(), siteRoot.value());
        }
        if (req.getMethod() == Poco::Net::HTTPServerRequest::HTTP_GET) {
            if (result == "staticHandler") {
                return new staticHandler(srvName.value(), siteRoot.value());
            }
            if (result == "templateHandler") {
                return new templateHandler(srvName.value(), templateRoot.value());
            }
            if (result == "xmlHandler") {
                return new xmlHandler(srvName.value(), siteRoot.value());
            }
        }

        return new badHandler(srvName.value(), siteRoot.value());
    }

    mainHTTPRequestHandlerFactory(std::string name) :
        srvName(name), siteRoot("www/") {
        setConfig();
    }

private:

    /// this.siteRoot-->(config.server.root)
    ///
    /// this.definiteMap-->(config.server.rules.defMap)
    ///
    /// this.ruleMap-->(config.server.rules.ruleMap)
    void setConfig();

    std::string findMatch(const std::string & text);

    std::optional<std::string> srvName;
    std::optional<std::filesystem::path> siteRoot;
    std::optional<std::filesystem::path> templateRoot;

    /// special(string) <--> string
    std::map<std::string, std::string> specialMap;
    /// resource name <--> handler
    std::map<std::string, std::string> definiteMap;
    /// rule(string)  <--> handler
    std::map<std::string, std::string> ruleMap;
};

#endif // !MAINFACTORY_HPP