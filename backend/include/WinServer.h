//
// Created by Aidan on 10/9/2025.
//

#ifndef INC_220FINALMYVERSION_WINSERVER_H
#define INC_220FINALMYVERSION_WINSERVER_H

// 💡 These must come BEFORE including winsock2/windows headers - prevent overhead bloat
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOBYTE

#include <winsock2.h>
#include <string>

#include "WebRequests.h"
#pragma comment(lib, "ws2_32.lib")

using std::string;

class Game;

class WinServer {
    Game* game;
    WebRequests* webRequests;
    SOCKET serverSocket{};
    sockaddr_in clientAddr{};
    int clientAddrSize{};
    int testCount{};
    int port;
    void start();
    void stop() const;
public:
    explicit WinServer(int port, Game* game);
    void poll();
    ~WinServer();
};


#endif //INC_220FINALMYVERSION_WINSERVER_H