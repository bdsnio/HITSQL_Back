#ifndef INDEXHANDLER_HPP
#define INDEXHANDLER_HPP

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/URI.h>
#include <Poco/Path.h>
#include <fstream>
#include <iterator>
#include <string>

class indexHandler : public
Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(
        Poco::Net::HTTPServerRequest& req,
        Poco::Net::HTTPServerResponse& resp
    ) {
        resp.setContentType("text/html");

        Poco::Path webroot("./webroot/");
        Poco::Path indexPath("index.html");

        std::fstream fstr;
        fstr.open(webroot.toString()+indexPath.toString());
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
            << webroot.toString()+indexPath.toString();
            return;
        }
    }
};

#endif // !INDEXHANDLER_HPP