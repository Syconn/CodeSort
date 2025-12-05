//
// Created by Aidan on 10/6/2025.
//

#ifndef INC_220FINALMYVERSION_CARD_H
#define INC_220FINALMYVERSION_CARD_H
#include <string>
#include <utility>
#include <functional>
#include <iostream>

using std::string;
using std::function;

class Card {
    string name;
    string desc;
    string img;
    function<void(int[], int)> func;
public:
    Card() : func(nullptr) {}
    Card(string name, string img, string desc, const function<void(int[], int)> &func): name(std::move(name)), desc(std::move(desc)), img(std::move(img)), func(func) {}
    void sortArray(int arr[], int size) const;
    string jsonify() const;
};


#endif //INC_220FINALMYVERSION_CARD_H