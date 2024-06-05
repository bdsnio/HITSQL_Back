#ifndef FROMHANDLER_HPP
#define FROMHANDLER_HPP

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <Poco/Foundation.h>
#include <fstream>
#include <string>

#include "../../log/log.hpp"

class formHandler : public
Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(
        Poco::Net::HTTPServerRequest& req,
        Poco::Net::HTTPServerResponse& resp
    ) {
        resp.setContentType("text/html");

        Poco::Path webroot("./webroot/");
        Poco::Path indexPath("index.html");
        Poco::Path combinedPath(webroot.toString()+indexPath.toString());

        std::string logStr = "[[INFO]] : " + 
            req.clientAddress().host().toString() +  ":" + 
            std::to_string(req.clientAddress().port()) +
            " requires file " + combinedPath.toString();
        writeToLog(serverName+".log", logStr);

        std::fstream fstr;
        fstr.open(combinedPath.toString());
        if (fstr.is_open()) {
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
    }

    formHandler(std::string srvName) : serverName(srvName) {}

private:
    std::string serverName;

};

#endif // !FROMHANDLER_HPP