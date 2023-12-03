#ifndef PERSONALGITFRONT_BONGOHASHMAP_H
#define PERSONALGITFRONT_BONGOHASHMAP_H

#include <iostream>
#include <string>
#include <vector>
#include "Ticket.hpp"

using namespace std;

class BongoHashMap {
private:
    int numStates = 50, numMakes = 49, numModels = 23, numColors = 18;
    Ticket** hashArray;
    int capacity;
    int size;
    Ticket* temp;
    float maxLoadFactor = 0.05f;

public:
    BongoHashMap();
    ~BongoHashMap();

    void addCase(State state, Make make, Model model, Color color, int year);
    vector<int> getCase();
    vector<vector<int>> getAllCases();
    int hashFunction(State state, Make make, Model model, Color color, int year);
    int sizeOfMap();
    bool isEmpty();

};


#endif //PERSONALGITFRONT_BONGOHASHMAP_H
