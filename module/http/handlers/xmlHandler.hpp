#ifndef XMLHANDLER_HPP
#define XMLHANDLER_HPP

#include <Poco/File.h>
#include <Poco/URI.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <filesystem>
#include <fstream>
#include <string>

#include "../handlerBase.hpp"

class xmlHandler : public requestHandlerBase {
public:
    xmlHandler(std::string srvName_, std::string root) :
        srvName(srvName_), webroot(root) {}
protected:
    void processRequest(
        Poco::Net::HTTPServerRequest &req,
        Poco::Net::HTTPServerResponse &resp
    ) override {
        std::string resName = std::string(Poco::URI(req.getURI()).getPath());
        std::filesystem::path resPath(
            std::filesystem::path(webroot) / resName);
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

private:
    std::string srvName;
    std::string webroot;
};

#endif // !XMLHANDLER_HPP