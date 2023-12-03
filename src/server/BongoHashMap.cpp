#include "BongoHashMap.h"

BongoHashMap::BongoHashMap(){
    capacity = 2;
    size = 0;
    hashArray = new Ticket*[capacity];

    for(int i = 0; i < capacity; i++){
        hashArray[i] = NULL;
    }
//    tate state, Make make, Color color, Model model, Time time, Year year
    temp = new Ticket(AL, ACURA, BLUE, SUV, 2003);
};

BongoHashMap::~BongoHashMap(){
    delete hashArray;
    delete temp;
}

void BongoHashMap::addCase(State state, Make make, Model model, Color color, int year){
    std::cout << state << " " << make << " " << model << " " << color << " " << year << "\n";
    std::cout << state << (int)make << model << color << "\n";
    int hashVal = hashFunction(state, make, model, color, year);
    int index = hashVal % capacity;
    std::cout << hashVal << " " << index;

    if(hashArray[index] == NULL){
        hashArray[index] = new Ticket(state, make, color, model, year);
    }
    size += 1;

    if((float)size/(float)capacity >= maxLoadFactor){
        capacity *= 2;
//        resizeArr(hashArray);
    }
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
int BongoHashMap::hashFunction(State state, Make make, Model model, Color color, int year){
    int hashVal = 0;

    hashVal += (int)state;
    hashVal += (int)make * numStates;
    hashVal += (int)model * numMakes * numStates;
    hashVal += (int)color * numModels * numMakes * numStates;
    hashVal += (int)year * numColors * numModels * numMakes * numStates;

    return hashVal;
};

int BongoHashMap::sizeOfMap() {
    return size;
};
bool BongoHashMap::isEmpty(){
    if(size == 0){
        return true;
    }
    return false;
};