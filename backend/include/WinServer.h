//
// Created by Aidan on 10/9/2025.
//

#ifndef INC_220FINALMYVERSION_WINSERVER_H
#define INC_220FINALMYVERSION_WINSERVER_H

// ---------- PLATFORM DETECTION ----------
#if defined(_WIN32) || defined(_WIN64)

// Windows / WinSock
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOBYTE
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else

// ---------- macOS & Linux (POSIX sockets) ----------
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>         // close()
#include <arpa/inet.h>      // inet_ntoa, etc.
#include <cstring>

typedef int SOCKET;         // WinSock compatibility
#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1

#endif

#include <string>
#include "WebRequests.h"

using std::string;

class Game;

class WinServer {
    Game* game;
    WebRequests* webRequests;
    SOCKET serverSocket{};
    sockaddr_in clientAddr{};
    #if defined(_WIN32)
    int clientAddrSize;
    #else
    socklen_t clientAddrSize;
    #endif

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