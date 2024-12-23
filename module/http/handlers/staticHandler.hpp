#ifndef STATICHANDLER_HPP
#define STATICHANDLER_HPP

#include <Poco/File.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>

#include "../handlerBase.hpp"

class staticHandler : public requestHandlerBase {
public:
  staticHandler(std::string srvName_, std::string root)
      : srvName(srvName_), webroot(root) {}

protected:
  void processRequest(Poco::Net::HTTPServerRequest &req,
                      Poco::Net::HTTPServerResponse &resp) override {
    std::string resName = std::string(Poco::URI(req.getURI()).getPath());
    std::filesystem::path resPath(webroot);
    checkUri(resName);
    resPath += resName;

    std::cout << std::format("\033[34mstatic handler : {}\033[0m",
                             resPath.c_str())
              << std::endl;
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
};

#endif // !STATICHANDLER_HPP