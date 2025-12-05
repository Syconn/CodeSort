//
// Created by Aidan on 10/12/2025.
//

#ifndef INC_220FINALMYVERSION_WEBREQUESTS_H
#define INC_220FINALMYVERSION_WEBREQUESTS_H

#include <string>
#include <iostream>

using namespace std;

class Game;

class WebRequests {
    Game* game;
    string data;
    static string sendContent(const string& body);
    static string sendResult(bool success);
public:
    explicit WebRequests(Game* game): game(game) {}
    string response(int code) const;
    int handleRequest(const string &request);
};

string getBodyValue(const string& data);

#endif //INC_220FINALMYVERSION_WEBREQUESTS_H