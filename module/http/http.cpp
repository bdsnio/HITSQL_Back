#include "http.hpp"
#include <ostream>

void WebRequestHandler::handleRequest(
    HTTPServerRequest &req, HTTPServerResponse &resp) {
    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/html");

    std::ostream & out = resp.send();
    out << "Poco success";
    out.flush(); 
}

int ServerApp::main(const std::vector<std::string> &) {
    HTTPServer server(
        new WebRequestHandlerFactory,
        ServerSocket(9090),
        new HTTPServerParams
    );

    server.start();

    waitForTerminationRequest();

    server.stop();
    return Application::EXIT_OK;
}