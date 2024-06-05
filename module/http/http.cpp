#include "http.hpp"
#include "mainFactory.hpp"

int ServerApp::main(const std::vector<std::string>& args) {

    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
    pParams->setMaxQueued(maxQueue);
    pParams->setMaxThreads(maxThread);

    Poco::Net::ServerSocket svSocket(port);

    Poco::Net::HTTPServer srv(
        new mainHTTPRequestHandlerFactory(),
        svSocket,
        pParams
    );

    srv.start();

    waitForTerminationRequest();

    srv.stop();
    return 0;
}