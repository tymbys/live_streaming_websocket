#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"


#include <iostream>
#include <cstdio>
#include <chrono>
#include <cstdlib>
#include <getopt.h>
#include <memory>
#include <cstring>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>


using namespace std::chrono;
using namespace seasocks;
using namespace std;

class MyServer : public Server {
public:
    using Server::Server;
private:

    virtual void checkThread() const override {

    };
};

class MyHandler : public WebSocket::Handler {
public:

    explicit MyHandler(MyServer* server);

    virtual void onConnect(WebSocket* connection);

    virtual void onData(WebSocket* connection, const char* data);
    virtual void onDisconnect(WebSocket* connection);

    void setCanvas(string imgBase64); // noexcept;

    void setCanvas(const uint8_t* data, size_t length);



private:
    set<WebSocket*> _connections;
    Server* _server;
    int _currentValue;
    string _currentSetValue;
    std::mutex _mutex;

    void setValue(int value);
};


#endif /* WEBSERVER_H */

