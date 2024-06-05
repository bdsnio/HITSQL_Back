#ifndef MAINFACTORY_HPP
#define MAINFACTORY_HPP

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/URI.h>
#include "handlers/indexHandler.hpp"
#include "handlers/dataHandler.hpp"
#include "handlers/formHandler.hpp"
#include "handlers/badHandler.hpp"

/// Factory for handling all file request, including .html and .css file
/// In this class, the factory will generate the handlers when clients 
/// require files to this server.
///
/// The program is: if the request path is "/", server responses the 
/// <index.html>. If the clients require others, server responses that 
/// file by invoking dataHandler().
class mainHTTPRequestHandlerFactory : public
Poco::Net::HTTPRequestHandlerFactory {

public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(
        const Poco::Net::HTTPServerRequest& req
    ) {
        Poco::URI uri(req.getURI());
        // GET
        if (req.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
            if (uri.getPath() == "/") {
                return new indexHandler(srvName);
            }
            else {
                return new dataHandler(srvName);
            }
        }
        // POST
        if (req.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
            return new formHandler(srvName);
        }
        return new badHandler(srvName);
    }

    mainHTTPRequestHandlerFactory(std::string name) : srvName(name) {}

private:
    std::string srvName;
};

#endif // !MAINFACTORY_HPP