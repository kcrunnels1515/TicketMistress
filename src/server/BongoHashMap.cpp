#include "BongoHashMap.h"

BongoHashMap::BongoHashMap(){};

void BongoHashMap::addCase(string state, string make, string model, string color, string time){
    std::cout << state << make << model << color << time << "\n";
    State stateVal = state;
};
vector<int> BongoHashMap::getCase(){
    vector<int> vec;
    return vec;
};
vector<vector<int>> BongoHashMap::getAllCases(){
    vector<int> vec;
    vector<vector<int>> vecContainer;
    return vecContainer;
};
int BongoHashMap::hashFunction(int state, int make, int model, int color, int time){
    int hashVal = 0;

    hashVal += state;
    hashVal += make * numStates;
    hashVal += model * make * numStates;
    hashVal += color * model * make * numStates;
    hashVal += time * color * model * make * numStates;

    return hashVal;
};