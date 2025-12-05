//
// Created by Aidan on 10/9/2025.
//

#include "WinServer.h"
#include "WebRequests.h"
#include <iostream>

using std::cout;
using std::endl;

WinServer::WinServer(const int port, Game* game) {
    this->port = port;
    this->game = game;
    this->webRequests = new WebRequests(game);
    start();
}

void WinServer::start() {

#if defined(_WIN32)
    // ------- WINDOWS STARTUP -------
    WSADATA wsaData{};
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    sockaddr_in serverAddr{};
    clientAddrSize = sizeof(clientAddr);

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        return;
    }

    // Allow immediate reuse of the port (avoid “Address already in use”)
    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&opt), sizeof(opt));

    // Setup server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Issue Binding Port" << endl;
        return;
    }

    listen(serverSocket, 5);
    cout << "Server running on http://localhost:" << port << endl;
}

void WinServer::stop() const {
#if defined(_WIN32)
    closesocket(serverSocket);
    WSACleanup();
#else
    close(serverSocket);
#endif
}

void WinServer::poll() {
    SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);

    if (clientSocket == INVALID_SOCKET)
        return;

    char buffer[2048];

    int bytesReceived =
        recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';

        const string requestStr(buffer);
        const int code = webRequests->handleRequest(requestStr);
        const string res = webRequests->response(code);

        send(clientSocket, res.c_str(), res.size(), 0);
    }

#if defined(_WIN32)
    closesocket(clientSocket);
#else
    close(clientSocket);
#endif
}

WinServer::~WinServer() {
    stop();
}
