//
// Created by Aidan on 10/6/2025.
//

#include "Card.h"

void Card::sortArray(int arr[], const int size) const {
    func(arr, size);
}

string Card::jsonify() const {
    return "{\"name\":\"" + name + "\", \"image\":\"" + img + "\", \"description\":\"" + desc + "\"}";
}


