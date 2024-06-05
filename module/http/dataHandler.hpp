#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <fstream>
#include <iterator>
#include <string>
#include <iostream>

class dataHandler : public
Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(
        Poco::Net::HTTPServerRequest& req,
        Poco::Net::HTTPServerResponse& resp
    ) {
        Poco::Path webroot("./webroot/");
        Poco::Path filePath(Poco::URI(req.getURI()).getPath());
        Poco::Path combinedPath(webroot.toString()+filePath.toString());

        std::fstream fstr;
        fstr.open(combinedPath.toString());
        if (fstr.is_open()) {
            resp.setContentType(getFileMIME(combinedPath));
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            std::string fileContent(
                (std::istreambuf_iterator<char>(fstr)),
                std::istreambuf_iterator<char>());
            resp.send() << fileContent;
        }
        else {
            resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            resp.send() << Poco::URI(req.getURI()).getPath() + "not found"
            << combinedPath.toString();
            return;
        }
        std::cout << Poco::URI(req.getURI()).getPath() << std::endl;
        return;
    }

private:
    std::string getFileMIME(const Poco::Path & path) {

        if (path.getExtension() == "html") {
            return "text/html";
        }
        if (path.getExtension() == "css") {
            return "text/css";
        }
        if (path.getExtension() == "js") {
            return "application/javascript";
        }
        if (path.getExtension() == "jpeg" || 
            path.getExtension() == "jpg") {
            return "image/jpeg";
        }
        if (path.getExtension() == "png") {
            return "image/png";
        }

        return "text/html";
    }
};

#endif // !DATAHANDLER_HPP