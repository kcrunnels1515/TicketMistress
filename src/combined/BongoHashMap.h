#ifndef PERSONALGITFRONT_BONGOHASHMAP_H
#define PERSONALGITFRONT_BONGOHASHMAP_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include "Ticket.hpp"

using namespace std;

class BongoHashMap {
private:
    int numStates = 50, numMakes = 49, numModels = 23, numColors = 18;
    vector<vector<Ticket*>> hashArray;
    int capacity;
    int size;
    float maxLoadFactor = 0.75f;

public:
    BongoHashMap();
    void addCase(Ticket *input_ticket);
    vector<Ticket*> getCase(Ticket input_ticket);
    vector<Ticket*> getAllCases(Ticket input_ticket, unsigned char indep_vars);
    pair<float, vector<Ticket*>> getStats(Ticket input_ticket, unsigned char indep_vars);
    int hashFunction(Ticket input_ticket);
    int sizeOfMap();
    bool isEmpty();
    void resizeArr();
};


#endif //PERSONALGITFRONT_BONGOHASHMAP_H
