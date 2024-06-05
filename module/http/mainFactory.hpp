#ifndef MAINFACTORY_HPP
#define MAINFACTORY_HPP

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/URI.h>
#include "indexHandler.hpp"
#include "dataHandler.hpp"

class mainHTTPRequestHandlerFactory : public
Poco::Net::HTTPRequestHandlerFactory {

public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& req
    ) {
        Poco::URI uri(req.getURI());
        if (uri.getPath() == "/") {
            return new indexHandler(srvName);
        }
        else {
            return new dataHandler(srvName);
        }
    }

    mainHTTPRequestHandlerFactory(std::string name) : srvName(name) {}

private:
    std::string srvName;
};

#endif // !MAINFACTORY_HPP