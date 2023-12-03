#include <iostream>
#include <string>
#include "BongoHashMap.h"
#include "Window.h"

int main() {
    std::cout << "hello world";
    BongoHashMap hashMap = BongoHashMap();
    hashMap.addCase("AL", "ALPINA", "ORANGE", "SUBN", "1230");
    hashMap.addCase("AK", "ALPINA", "ORANGE", "SUBN", "1230");
    std::cout << "end of Data Structure";
//    Window test = Window();
//    vector<string> output;
//    output = test.start();

//    for(int i = 0; i < output.size(); i++){
//        std::cout << output[i] << std::endl;
//    }
}