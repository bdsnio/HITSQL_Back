#ifndef TEMPLATEHANDLER_HPP
#define TEMPLATEHANDLER_HPP

#include "../handlerBase.hpp"
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>

#include "../../../include/inja.hpp"

class templateHandler : public requestHandlerBase {
public:
    templateHandler(std::string srvName_, std::string root) :
        srvName(srvName_), webroot(root) {}
protected:
    void processRequest(
        Poco::Net::HTTPServerRequest &req,
        Poco::Net::HTTPServerResponse &resp
    ) override {
        std::string resName = std::string(Poco::URI(req.getURI()).getPath());
        std::regex pattern(R"(^/([^/]+)/(\d+).*$)");
        std::smatch matches;

        std::string type;
        int id;
        if (std::regex_search(resName, matches, pattern)) {
            if (matches.size() == 3) {
                type = matches[1];
                id = std::stoi(matches[2]);
            }
            std::string temName("/" + type + "_template.html");
            std::filesystem::path resPath(webroot);
            resPath += temName;

            std::ifstream resource(resPath);
            if (resource) {
                resp.setContentType(getFileMIME(resPath.c_str()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                std::string fileContent(
                    (std::istreambuf_iterator<char>(resource)),
                    std::istreambuf_iterator<char>());

                // get Template
                inja::json data = {
                        {"title", "My Page"},
                        {"header", "Welcome to My Page"},
                        {"content", "This is a simple example of using inja."},
                        {"footer", "© 2024 My Page"}
                    };
                // render Template
                resp.send() << inja::render(fileContent, data);
            }
            else {
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                resp.send() << " Not found " << resPath;
                return;
            }
        }
        else {
            std::filesystem::path resPath(webroot);
            resPath += "/../404.html";
            std::ifstream resource(resPath);
            if (resource) {
                resp.setContentType(getFileMIME(resPath.c_str()));
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                std::string fileContent(
                    (std::istreambuf_iterator<char>(resource)),
                    std::istreambuf_iterator<char>());
                resp.send() << fileContent;
            }
            else {
                resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                resp.send() << " Not found " << resPath;
                return;
            }
        }
    }

private:
    std::string srvName;
    std::string webroot;
};

#endif // !TEMPLATEHANDLER_HPP