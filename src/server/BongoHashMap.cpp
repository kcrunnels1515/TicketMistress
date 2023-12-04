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
    hashArray.clear();
    hashArray = newArr;
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

vector<vector<string>> BongoHashMap::getCaseInt(int state, int make, int model, int color, int year){
    vector<vector<string>> vec;
    int hashVal = hashFunctionInt(state, make, model, color, year);
    int index = hashVal % capacity;
    for(int i = 0; i < hashArray[index].size(); i++){
        bool stateBool = false, makeBool = false, modelBool = false, colorBool = false, yearBool = false;
        if((int)hashArray[index][i]->_state == state){
            stateBool = true;
        }
        if((int)hashArray[index][i]->_make == make){
            makeBool = true;
        }
        if((int)hashArray[index][i]->_model == model){
            modelBool = true;
        }
        if((int)hashArray[index][i]->_color == color){
            colorBool = true;
        }
        if((int)hashArray[index][i]->_year == year){
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

vector<vector<string>> BongoHashMap::getAllCases(State state, Make make, Model model, Color color, Year year){
    vector<vector<string>> vecContainer;
    int stateStart = 0, stateEnd = numStates;
    int makeStart = 0, makeEnd = numMakes;
    int modelStart = 0, modelEnd = numModels;
    int colorStart = 0, colorEnd = numColors;
//    Time Range 1922 - 2023
    int yearStart = 1922, yearEnd = 2024;

    if(state != NOWHERE){
        stateStart = (int)state;
        stateEnd = (int)state + 1;
    }
    if(make != VEHICLE){
        makeStart = (int)make;
        makeEnd = (int)make + 1;
    }
    if(model == DIM3){
        modelStart = (int)model;
        modelEnd = (int)model + 1;
    }
    if(color == UNKNOWN){
        colorStart = (int)color;
        colorEnd = (int)color + 1;
    }
    if(year == 0){
        yearStart = year;
        yearEnd = year + 1;
    }

    for(int a = stateStart; a < stateEnd; a++){
        for(int b = makeStart; b < makeEnd; b++){
            for(int c = modelStart; c < modelEnd; c++){
                for(int d = colorStart; d < colorEnd; d++){
                    for(int e = yearStart; e < yearEnd; e++){
                        vector<vector<string>> out = getCaseInt(a,b,c,d,e);
                        for(int i = 0; i < out.size(); i++){
                            vecContainer.push_back(out[i]);
                        }
                    }
                }
            }
        }
    }

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

int BongoHashMap::hashFunctionInt(int state, int make, int model, int color, int year) {
    int hashVal = 0;

    hashVal += state;
    hashVal += make * numStates;
    hashVal += model * numMakes * numStates;
    hashVal += color * numModels * numMakes * numStates;
    hashVal += year * numColors * numModels * numMakes * numStates;

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