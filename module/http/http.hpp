/***********************
* @date: 2024.6.7      *
* @author: Guo Yangfan *
* @file: http.hpp      *
***********************/
/// The server's kernel: ServerApp class. It read and parse the config file.
///
/// The config file is a json file.
#ifndef HTTP_HPP
#define HTTP_HPP

#include <Poco/Foundation.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>
#include <filesystem>
#include <string>
#include <vector>

/// This is the main server application(which is a concept in Poco).
/// All the main "actions" are in the main function.
class ServerApp : public
Poco::Util::ServerApplication {
public:
    /// This is basic settings for the server application.
    /// They are set at main.cpp
    ServerApp() :
        port(8080), srvName("httpServer"),
        maxQueue(100), maxThread(16) {}

    /// The config file defaultly locates at program's path in config folder.
    /// 
    /// i.e.    hit-circle-backend
    ///         config/
    ///             config.json
    /// NOTE: The comment lines SHOULD NOT appear in the config file. 
    void setConfig(std::filesystem::path filePath);

protected:
    int main(const std::vector<std::string>& args);

private:
    Poco::UInt16 port;
    std::string srvName;
    int maxQueue;
    int maxThread;
};

#endif // !HTTP_HPP