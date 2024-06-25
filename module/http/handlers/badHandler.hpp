#ifndef BADHANDLER_HPP
#define BADHANDLER_HPP

#include "../handlerBase.hpp"
#include <Poco/File.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/URI.h>
#include <filesystem>
#include <fstream>
#include <string>

class badHandler : public requestHandlerBase {
public:
  badHandler(std::string srvName, std::string root)
      : srvName(srvName), webroot(root) {}

protected:
  void processRequest(Poco::Net::HTTPServerRequest &req,
                      Poco::Net::HTTPServerResponse &resp) override {
    std::string resName = std::string("404.html");
    std::filesystem::path resPath(std::filesystem::path(webroot) / resName);
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

#endif // !BADHANDLER_HPP