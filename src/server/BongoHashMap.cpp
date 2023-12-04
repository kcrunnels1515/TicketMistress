#include "BongoHashMap.h"

#define NAME_OF( v ) #v

BongoHashMap::BongoHashMap(){
    capacity = 2;
    size = 0;
//    hashArray.reserve(capacity);
};

void BongoHashMap::resizeArr(){
    unordered_map<int, vector<Ticket*>> newArr;
    auto iter = hashArray.begin();
    while(iter != hashArray.end()){
        cout << iter->second.size();
        for(int i = 0; i < iter->second.size(); i++){
            int hashVal = hashFunction(iter->second[i]->_state, iter->second[i]->_make, iter->second[i]->_model, iter->second[i]->_color, iter->second[i]->_year);
            int index = hashVal % capacity;
            newArr[index].push_back(iter->second[i]);
        }
        iter++;
    }
};

void BongoHashMap::addCase(State state, Make make, Model model, Color color, int year){

    if((float)size/(float)capacity >= maxLoadFactor){
        capacity *= 2;
        cout << " Need to Resize" << endl;
        resizeArr();
    }

    std::cout << state << " " << make << " " << model << " " << color << " " << year << "\n";
    std::cout << state << (int)make << model << color << "\n";
    int hashVal = hashFunction(state, make, model, color, year);
    int index = hashVal % capacity;
    std::cout << hashVal << " " << index;
    hashArray[index].push_back(new Ticket(state, make, color, model, year));
    size++;
};
vector<vector<string>> BongoHashMap::getCase(State state, Make make, Model model, Color color, Year year){
    vector<vector<string>> vec;
    int hashVal = hashFunction(state, make, model, color, year);
    int index = hashVal % capacity;
    for(int i = 0; i < hashArray[index].size(); i++){
        bool stateBool = false, makeBool = false, modelBool = false, colorBool = false, yearBool = false;
        if(hashArray[index][i]->_state == state){
            stateBool = true;
        }
        if(hashArray[index][i]->_make == make){
            makeBool = true;
        }
        if(hashArray[index][i]->_model == model){
            modelBool = true;
        }
        if(hashArray[index][i]->_color == color){
            colorBool = true;
        }
        if(hashArray[index][i]->_year == year){
            yearBool = true;
        }

        if(stateBool && makeBool && modelBool && colorBool && yearBool){
            cout << "result found" << endl;
            vector<string> infoVec;
            infoVec.push_back(to_string(hashArray[index][i]->_state));
            infoVec.push_back(to_string(hashArray[index][i]->_make));
            infoVec.push_back(to_string(hashArray[index][i]->_model));
            infoVec.push_back(to_string(hashArray[index][i]->_color));
            infoVec.push_back(to_string(hashArray[index][i]->_year));
            vec.push_back(infoVec);
        }
    }
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