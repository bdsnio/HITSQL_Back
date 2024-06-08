/***********************
* @date: 2024.6.7      *
* @author: Guo Yangfan *
* @file: http.cpp      *
***********************/
#include "http.hpp"
#include "mainFactory.hpp"
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

using namespace Poco;
using namespace std::filesystem;

int ServerApp::main(const std::vector<std::string>& args) {

    setConfig(current_path() / path("config/config.json"));

    Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams;
    pParams->setMaxQueued(maxQueue);
    pParams->setMaxThreads(maxThread);
    pParams->setServerName(srvName);

    Poco::Net::ServerSocket svSocket(port);

    Poco::Net::HTTPServer srv(
        new mainHTTPRequestHandlerFactory(pParams->getServerName()),
        svSocket,
        pParams
    );

    std::cout << "[[INFO]] : Server started at port:" << port << std::endl;

    srv.start();

    waitForTerminationRequest();

    srv.stop();
    return 0;
}

void ServerApp::setConfig(std::filesystem::path filePath) {
    std::fstream fstr(filePath);
    if (fstr.is_open()) {
        std::string fileContent(
            (std::istreambuf_iterator<char>(fstr)),
            std::istreambuf_iterator<char>()
        );

        JSON::Parser jsonParser;
        Dynamic::Var result = jsonParser.parse(fileContent);

        JSON::Object::Ptr pObject = result.extract<JSON::Object::Ptr>();

        JSON::Object::Ptr pObject_website = pObject->getObject("website");

        this->srvName = pObject_website->getValue<std::string>("name");

        JSON::Object::Ptr pObject_server = pObject->getObject("server");

        this->port = pObject_server->getValue<int>("port");
        this->maxQueue = pObject_server->getValue<int>("maxQueue");
        this->maxThread = pObject_server->getValue<int>("maxThread");

        fstr.close();
    }
}