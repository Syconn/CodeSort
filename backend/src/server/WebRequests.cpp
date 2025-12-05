//
// Created by Aidan on 10/12/2025.
//

#include "WebRequests.h"
#include "Constants.h"
#include "Game.h"
#include "ArrayUtil.h"

int WebRequests::handleRequest(const string &request) {
    data = getBodyValue(request);

    // GET Requests
    if (request.find("OPTIONS") != string::npos) return OPTIONS;
    if (request.find("GET /page") != string::npos) return PAGE;
    if (request.find("GET /status") != string::npos) return STATUS;
    if (request.find("GET /array") != string::npos) return ARRAY;
    if (request.find("GET /deck") != string::npos) return CARDS;

    // POST Requests
    if (request.find("POST /cardClicked") != string::npos) return CLICK_CARD;
    if (request.find("POST /setPage") != string::npos) return SET_PAGE;
    if (request.find("POST /restart") != string::npos) return RESTART;

    return NO_RET;
}

string WebRequests::response(const int code) const {
    if (code == OPTIONS) { // Setup Content Allocation
        return "HTTP/1.1 204 No Content\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
            "Access-Control-Allow-Headers: Content-Type\r\n"
            "\r\n";
    }

    if (code == PAGE) return sendContent(R"({"page": ")" + game->gameState + "\"}");
    if (code == ARRAY) return sendContent(jsonifyArray(game->sortArray, game->sortArraySize));
    if (code == CARDS) return sendContent(game->deck->jsonify());
    if (code == STATUS) return sendResult(true);

    if (code == SET_PAGE) {
        game->gameState = data;
        return sendResult(true);
    }
    if (code == RESTART) {
        game->restart();
        return sendResult(true);
    }
    if (code == CLICK_CARD) return sendResult(game->deck->sortArray(stoi(data), game->sortArray, game->sortArraySize));

    // Error route
    return "HTTP/1.1 404 Not Found\r\n"
           "Content-Type: text/plain\r\n"
           "Access-Control-Allow-Origin: *\r\n"
           "\r\n"
           "Route not found.";
}

string WebRequests::sendContent(const string& body) {
    return "HTTP/1.1 200 OK\r\n"
               "Content-Type: application/json\r\n"
               "Access-Control-Allow-Origin: *\r\n"
               "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
               "Access-Control-Allow-Headers: Content-Type\r\n"
               "\r\n" +
               body;
}

string WebRequests::sendResult(const bool success) {
    return "HTTP/1.1 200 OK\r\n"
               "Content-Type: application/json\r\n"
               "Access-Control-Allow-Origin: *\r\n"
               "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
               "Access-Control-Allow-Headers: Content-Type\r\n"
               "\r\n"
               "{\"success\":" + to_string(success) + "}";
}

string getBodyValue(const string& data) {
    if (const auto startIndex = data.find("\"body\""); startIndex != string::npos) {
        size_t valueIndex = data.find(':', startIndex);
        if (valueIndex == string::npos) return "";
        valueIndex++; // move past ':'
        while (valueIndex < data.size() && isspace(data[valueIndex])) valueIndex++;
        if (data[valueIndex] == '\"') {
            valueIndex++; // skip quote
            const size_t endIndex = data.find('\"', valueIndex);
            return data.substr(valueIndex, endIndex - valueIndex);
        }
        const size_t endIndex = data.find_first_of(",}", valueIndex);
        return data.substr(valueIndex, endIndex - valueIndex);
    }
    return "";
}
