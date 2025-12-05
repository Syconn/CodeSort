//
// Created by Aidan on 10/12/2025.
//

#include "Game.h"

#include "ArrayUtil.h"
#include "SortUtil.h"

Game::Game() {
    setup();
    run();
}

void Game::setup() {
    winServer = new WinServer(8080, this); // Start Web Server
    srand(time(nullptr));
    createCards();
}

void Game::setupPlay() {
    playing = true; // Signal Playing
    turns = 0;
    points = 0;

    sortArray = new int[sortArraySize]; // Create Array
    int count = 0;
    while (count < sortArraySize) { // Ignore Duplicates
        if (const int num = rand() % (maxVal - minVal + 1) + minVal; !contains(sortArray, count, num)) sortArray[count++] = num;
    }

    deck = new Deck(new Card[4] {cards[0], cards[1], cards[2], cards[3]}, 4);
}

void Game::restart() {
    delete[] deck;
    delete[] sortArray;

    setupPlay();
}


void Game::createCards() {
    cards = new Card[cardSize];
    cards[0] = Card("Selection Sort", "selection.png", "Inserts each new element into its correct position among the already-sorted elements", selectionSort);
    cards[1] = Card("Bubble Sort", "bubble.png", "Compares each pair of adjacent elements and swaps them if they are out of order.", bubbleSort);
    cards[2] = Card("Insertion Sort", "insertion.png", "Finds the smallest element from the unsorted portion and swaps it with the first unsorted element", insertionSort);
    cards[3] = Card("Quick Sort", "quick.png", "Divides the array into two parts using a pivot, placing smaller elements before it and larger ones after, then recursively sorts each part", quickSort);
    cards[4] = Card("Merge Sort", "", "", mergeSort);
    cards[5] = Card("Bucket Sort", "", "", bucketSort);
}


void Game::run() {
    while (running) {
        winServer->poll();
        if (!playing && gameState == GameLoop) setupPlay();
    }
}

Game::~Game() {
    delete winServer;
    delete[] sortArray;
    delete[] cards;
}


