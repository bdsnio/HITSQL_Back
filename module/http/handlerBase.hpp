/*************************
 * @date: 2024.6.7        *
 * @author: Guo Yangfan   *
 * @file: handlerBase.hpp *
 *************************/

#ifndef HANDLERBASE_HPP
#define HANDLERBASE_HPP

#include <Poco/File.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Path.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class requestHandlerBase : public Poco::Net::HTTPRequestHandler {

public:
  virtual void handleRequest(Poco::Net::HTTPServerRequest &req,
                             Poco::Net::HTTPServerResponse &resp) {
    try {
      processRequest(req, resp);
    } catch (const Poco::Exception &exc) {
      std::cout << "[[ERROR]] : " + exc.displayText();
    }
  }

protected:
  virtual void processRequest(Poco::Net::HTTPServerRequest &req,
                              Poco::Net::HTTPServerResponse &resp) = 0;

protected:
  std::string getFileMIME(const Poco::Path &path) {

    if (path.getExtension() == "html") {
      return "text/html";
    }
    if (path.getExtension() == "css") {
      return "text/css";
    }
    if (path.getExtension() == "js") {
      return "application/javascript";
    }
    if (path.getExtension() == "xml") {
      return "text/xml";
    }
    if (path.getExtension() == "jpeg" || path.getExtension() == "jpg") {
      return "image/jpeg";
    }
    if (path.getExtension() == "png") {
      return "image/png";
    }

    return "text/html";
  }

  void checkUri(std::string &text) {
    text = ((*ruleMap)[text].empty()) ? text : (*ruleMap)[text];
  }

public:
  static std::unique_ptr<std::map<std::string, std::string>> ruleMap;
};

#endif // !HANDLERBASE_HPP