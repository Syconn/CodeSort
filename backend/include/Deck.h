//
// Created by Aidan on 10/21/2025.
//

#ifndef INC_220FINALMYVERSION_HAND_H
#define INC_220FINALMYVERSION_HAND_H
#include "Card.h"

class Deck {
    Card* cards;
    int size;
public:
    explicit Deck(Card* cards, const int size): cards(cards), size(size) {}
    bool sortArray(int index, int* arr, int arraySize) const;
    [[nodiscard]] string jsonify() const;
};

#endif //INC_220FINALMYVERSION_HAND_H