//
// Created by Aidan on 10/12/2025.
//

#ifndef INC_220FINALMYVERSION_GAME_H
#define INC_220FINALMYVERSION_GAME_H

#include "Constants.h"
#include "WinServer.h"
#include "Card.h"
#include "Deck.h"

class Game {
    friend class WebRequests;
    string gameState = MainMenu;
    WinServer* winServer;
    Deck* deck;
    int* sortArray{};
    int sortArraySize = 10, cardSize = 6, minVal = -20, maxVal = 20, turns = 0, points = 0;
    bool running = true;
    bool playing = false;
    Card *cards{};
    void setup();
    void setupPlay();
    void run();
    void createCards();
    void restart();
public:
    Game();
    ~Game();
};

#endif //INC_220FINALMYVERSION_GAME_H