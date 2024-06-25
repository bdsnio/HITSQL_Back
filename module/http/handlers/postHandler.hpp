#ifndef POSTHANDLER_HPP
#define POSTHANDLER_HPP

#include "../handlerBase.hpp"
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/XML/XMLException.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

class postHandler : public requestHandlerBase {
public:
  postHandler(std::string srvName, std::string root)
      : srvName(srvName), webroot(root) {}

protected:
  void processRequest(Poco::Net::HTTPServerRequest &req,
                      Poco::Net::HTTPServerResponse &resp) override {
    using namespace Poco::JSON;
    using namespace Poco::XML;

    std::string requestBody;
    Poco::StreamCopier::copyToString(req.stream(), requestBody);

    if (req.getContentType() == "application/json") {
      processJsonPost(requestBody);
    }
    if (req.getContentType() == "application/xml") {
      processXmlPost(requestBody);
    }

    // static
    std::string resName = std::string(Poco::URI(req.getURI()).getPath());
    std::filesystem::path resPath(webroot);
    checkUri(resName);
    resPath += resName;

    std::cout << resPath << std::endl;
    std::ifstream resource(resPath);

    if (resource) {
      resp.setContentType(getFileMIME(resPath.c_str()));
      resp.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
      std::string fileContent((std::istreambuf_iterator<char>(resource)),
                              std::istreambuf_iterator<char>());
      resp.send() << fileContent;
    } else {
      resp.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      resp.send() << " Not found " << resPath;
      return;
    }
  }

private:
  std::string srvName;
  std::string webroot;

private:
  auto processJsonPost(std::string requestBody) -> void {
    // JSON parser
    Poco::JSON::Parser parser;
    auto json = parser.parse(requestBody).extract<Poco::JSON::Object::Ptr>();
    Poco::JSON::Stringifier stringifier;
    std::ostringstream oss;
    stringifier.stringify(*json, oss);
    std::cout << oss.str() << std::endl;
  }

  auto processXmlPost(std::string requestBody) -> void {
    Poco::XML::DOMParser parser;
    try {
      auto xmlDocument = parser.parseString(requestBody);
    } catch (Poco::XML::XMLException &e) {
      std::cerr << std::format("[[ERROR]] : {} {}", e.message(), requestBody) << std::endl;
    }
  }
};

#endif // !POSTHANDLER_HPP