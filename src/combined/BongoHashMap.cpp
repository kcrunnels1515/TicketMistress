#include "BongoHashMap.h"

#define NAME_OF( v ) #v

BongoHashMap::BongoHashMap(){
    capacity = 2;
    size = 0;
    hashArray.reserve(capacity);
};

void BongoHashMap::resizeArr(){
    vector<Ticket*> temp_arr;
    for (vector<Ticket*>& i : hashArray) {
        for (Ticket* t : i)
        temp_arr.push_back(t);
    }

};

void BongoHashMap::addCase(Ticket* input_ticket){
    if((float)size/(float)capacity >= maxLoadFactor){
        capacity *= 2;
        cout << " Need to Resize" << endl;
        resizeArr();
    }

    //std::cout << state << " " << make << " " << model << " " << color << " " << year << "\n";
    //std::cout << state << (int)make << model << color << "\n";
    int hashVal = hashFunction(*input_ticket);
    int index = hashVal % capacity;
    std::cout << hashVal << " " << index;
    hashArray[index].push_back(input_ticket);
    size++;
};

vector<Ticket*> BongoHashMap::getCase(Ticket input_ticket){
    vector<Ticket*> vec;
    int hashVal = hashFunction(input_ticket);
    int index = hashVal % capacity;
    for(int i = 0; i < hashArray[index].size(); i++){
        bool stateBool = false, makeBool = false, modelBool = false, colorBool = false, yearBool = false;
        if(hashArray[index][i]->_state == input_ticket._state){
            stateBool = true;
        }
        if(hashArray[index][i]->_make == input_ticket._make){
            makeBool = true;
        }
        if(hashArray[index][i]->_model == input_ticket._model){
            modelBool = true;
        }
        if(hashArray[index][i]->_color == input_ticket._color){
            colorBool = true;
        }
        if(hashArray[index][i]->_year == input_ticket._year){
            yearBool = true;
        }

        if(stateBool && makeBool && modelBool && colorBool && yearBool){
            //cout << "result found" << endl;
            vec.push_back(hashArray[index][i]);
        }
    }
    return vec;
};

vector<Ticket*> BongoHashMap::getAllCases(Ticket input_ticket, unsigned char indep_vars){
    vector<Ticket*> vecContainer;
    for (vector<Ticket*> v : hashArray) {
        for (Ticket* i : v) {
            bool stateBool = false, makeBool = false, modelBool = false,
                colorBool = false, yearBool = false;
            if ((indep_vars & 16) == 16) {
                stateBool = true;
            } else if (i->_state == input_ticket._state) {
                stateBool = true;
            }

            if ((indep_vars & 8) == 8) {
                makeBool = true;
            } else if (i->_make == input_ticket._make) {
                makeBool = true;
            }

            if ((indep_vars & 4) == 4) {
                modelBool = true;
            } else if (i->_model == input_ticket._model) {
                modelBool = true;
            }

            if ((indep_vars & 2) == 2) {
                colorBool = true;
            } else if (i->_color == input_ticket._color) {
                colorBool = true;
            }

            if ((indep_vars & 1) == 1) {
                yearBool = true;
            } else if (i->_state == input_ticket._state) {
                yearBool = true;
            }
            if (stateBool && makeBool && modelBool && colorBool && yearBool) {
                vecContainer.push_back(i);
            }
        }
    }
    return vecContainer;
};

pair<float, vector<Ticket*>> BongoHashMap::getStats(Ticket input_ticket, unsigned char indep_vars) {
    vector<Ticket*> other = getAllCases(input_ticket, indep_vars);
    vector<Ticket*> other_top = vector(other.begin(), other.begin() + 8);
    return make_pair((float) getCase(input_ticket).size() / (float) other.size(), other_top);
};

int BongoHashMap::hashFunction(Ticket input_ticket){
    int hashVal = 0;

    hashVal += (int)input_ticket._state;
    hashVal += (int)input_ticket._make * numStates;
    hashVal += (int)input_ticket._model * numMakes * numStates;
    hashVal += (int)input_ticket._color * numModels * numMakes * numStates;
    hashVal += (int)input_ticket._year * numColors * numModels * numMakes * numStates;

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
