#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include "../lib/csv.hpp"
#include "BongoTree.hpp"
#include "BongoHashMap.h"
#include "Ticket.hpp"
#include "IdiotCopRectifier.hpp"

Year interpret_year(std::string year);
Time interpret_time(std::string time);
//
//int main(int argc,char* argv[]) {
//  if (argc < 3) {
//    std::cout << "Input: ./server [port] [csv file]" << std::endl;
//    return -1;
//  }
//  int port;
//  try {
//    port = std::stoi(argv[1]);
//  } catch (std::invalid_argument) {
//    std::cout << "Not a number" << std::endl;
//  }
//  std::ifstream file(argv[2]);
//  if(!file.is_open()){
//     std::cout << "File not found" << std::endl;
//     return -1;
//  }
//
//  std::map<std::string,Make> makes_map;
//  make_names(makes_map);
//  std::map<std::string,Model> model_map;
//  model_names(model_map);
//  std::map<std::string,Color> color_map;
//  colors_names(color_map);
//  std::map<std::string,State> state_map;
//  state_names(state_map);
//
//  BongoTree ds_1;
//
//  io::CSVReader<6> in(argv[2]);
//  in.read_header(io::ignore_extra_column, "reg_state","v_body_type","v_make","voilation_time","color","year");
//  std::string reg_state, v_body_type, v_make, voi_time, color, year;
//  while(in.read_row(reg_state, v_body_type, v_make, voi_time, color, year)){
//    Ticket* temp = new Ticket;
//    if (auto search = state_map.find(reg_state); search != state_map.end()) {
//      temp->_state = search->second;
//    } else {
//      temp->_state = NOWHERE;
//    }
//    if (auto search = makes_map.find(reg_state); search != makes_map.end()) {
//      temp->_make = search->second;
//    } else {
//      temp->_make = VEHICLE;
//    }
//    if (auto search = color_map.find(reg_state); search != color_map.end()) {
//      temp->_color = search->second;
//    } else {
//      temp->_color = UNKNOWN;
//    }
//    if (auto search = model_map.find(reg_state); search != model_map.end()) {
//      temp->_model = search->second;
//    } else {
//      temp->_model = DIM3;
//    }
//    temp->_time = interpret_time(voi_time);
//    temp->_year = interpret_year(year);
//    ds_1.insert(temp);
//    std::cout << "State: " << reg_state << "; Body: " << v_body_type << "; Make: "
//      << v_make << "; Time of Obsv: " << voi_time << "; Color: " << color << "; Year: " << year << std::endl;
//  }
//  //std::set<Ticket*> result = std::set_difference(std::set_difference(std::set_difference(,), ),
//                                                 //std::set_difference(,));
//  return 0;
//}
//
//Year interpret_year(std::string year) {
//  if (year == "") return 0;
//  else {
//    Year y = 0;
//    try {
//      y = std::stoi(year);
//    } catch (std::invalid_argument) {
//      return 0;
//    }
//    if (y >= 1922 && y <= 2023) return y;
//    else return 0;
//  }
//}
//
//Time interpret_time(std::string time) {
//  if (time == "") return -1;
//  else {
//    Time t = -1;
//    try {
//      t = std::stoi(time.substr(0, time.size() - 1));
//    } catch (std::invalid_argument) {
//      return -1;
//    }
//    if (time[time.size() - 1] == 'A') { if (t <= 1259 && t >= 0) return t; else return -1; }
//    if (time[time.size() - 1] == 'P') { if (t + 1100 <= 2359) return (t + 1100); else return -1; }
//    else return -1;
//  }
//}

int main(){
    std::cout << "hello" << "\n";
    BongoHashMap hashMap = BongoHashMap();
    hashMap.addCase(FL, BENZ, SUBN, BLUE, 2002);
    hashMap.addCase(AK, HONDA, FWD, GREEN, 2003);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    hashMap.addCase(MA, BENZ, SUBN, TAN, 2005);
//    hashMap.getAllCases();

    vector<vector<string>> output = hashMap.getCase(AL, TOYOTA, SUBN, YELLOW, 2004);
    cout << "\n" << "\n";
    cout << "output:" << "\n";
    for(int i = 0; i < output.size(); i++){
        for(int j = 0; j < output[i].size(); j++){
            cout << output[i][j] << " ";
        }
        cout << "\n";
    }
//    cout << "i finished the code";
    return 0;
}