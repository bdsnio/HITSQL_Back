#ifndef HTTP_HPP
#define HTTP_HPP

#include <Poco/Foundation.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>
#include <vector>

/// This is the main server application(which is a concept in Poco).
/// All the main "actions" are in the main function.
class ServerApp : public
Poco::Util::ServerApplication {
public:
    /// This is basic settings for the server application.
    /// They are set at main.cpp
    ServerApp(Poco::UInt16 _port, int _maxQueue, int _maxThread) {
        port = _port;
        maxQueue = _maxQueue;
        maxThread = _maxThread;
    }

protected:
    int main(const std::vector<std::string>& args);

private:
    Poco::UInt16 port;
    int maxQueue;
    int maxThread;
};

#endif // !HTTP_HPP