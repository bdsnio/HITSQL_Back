#ifndef HTTP_HPP
#define HTTP_HPP

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Path.h>
#include <string>
#include <vector>

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

/// Handler for providing html and css files
class WebRequestHandler : public HTTPRequestHandler {
public:
    void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
};

class WebRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
    HTTPRequestHandler* createRequestHandler(
        const HTTPServerRequest & request
    ) {
        return new WebRequestHandler();
    }
};

class ServerApp : public ServerApplication {
protected:
    int main(const std::vector<std::string> &);

};

#endif // !HTTP_HPP