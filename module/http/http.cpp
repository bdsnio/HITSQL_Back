/***********************
 * @date: 2024.6.7      *
 * @author: Guo Yangfan *
 * @file: http.cpp      *
 ***********************/
#include "http.hpp"
#include "../config/config.hpp"
#include "mainFactory.hpp"
#include <Poco/Dynamic/Var.h>
#include <string>

using namespace Poco;
using namespace std::filesystem;

int ServerApp::main(const std::vector<std::string> &args) {

  setConfig();

  Poco::Net::HTTPServerParams *pParams = new Poco::Net::HTTPServerParams;
  pParams->setMaxQueued(maxQueue.value());
  pParams->setMaxThreads(maxThread.value());
  pParams->setServerName(srvName.value());

  Poco::Net::ServerSocket svSocket(port.value());

  Poco::Net::HTTPServer srv(
      new mainHTTPRequestHandlerFactory(pParams->getServerName()), svSocket,
      pParams);

  std::cout << "[[INFO]] : Server started at port:" << port.value()
            << std::endl;

  srv.start();

  waitForTerminationRequest();

  srv.stop();
  return 0;
}

void ServerApp::setConfig() {
  auto config = Config::getInstance().getConfig();
  this->srvName = config["website"]["name"].value<std::string>();
  this->port = config["server"]["port"].value<unsigned int>();
  this->maxQueue = config["server"]["maxQueue"].value<int>();
  this->maxThread = config["server"]["maxThread"].value<int>();
}