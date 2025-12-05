//
// Created by Aidan on 10/21/2025.
//

#include "Deck.h"

bool Deck::sortArray(const int index, int *arr, const int arraySize) const {
    if (cards != nullptr && index >= 0 && index < size) {
        cards[index].sortArray(arr, arraySize);
        return true;
    }
    return false;
}

string Deck::jsonify() const {
    if (cards == nullptr) return "{\"cards\":[]}";
    string ret = "{\"cards\":[";
    for (int i = 0; i < size; i++) {
        ret += cards[i].jsonify();
        if (i < size - 1) ret += ",";
    }
    return ret + "]}";
}

