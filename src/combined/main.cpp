//
// Created by micha on 12/1/2023.
//
#include <iostream>
#include <string>
#include "Window.h"
#include <fstream>
#include <iostream>
#include <map>
#include "../lib/csv.hpp"
#include "BongoTree.hpp"
#include "Ticket.hpp"
#include "IdiotCopRectifier.hpp"

Year interpret_year(std::string year);

int main(int argc,char* argv[]) {
  if (argc < 2) {
    std::cout << "Input: ./server [csv file]" << std::endl;
    return -1;
  }
  std::ifstream file(argv[1]);
  if(!file.is_open()){
     std::cout << "File not found" << std::endl;
     return -1;
  }

  BongoTree ds_1;
  //LoadingWindow loading_window;
  //loading_window.start(ds_1, argv[2]);
  std::map<std::string,Make> makes_map;
  make_names(makes_map);
  std::map<std::string,Model> model_map;
  model_names(model_map);
  std::map<std::string,Color> color_map;
  colors_names(color_map);
  std::map<std::string,State> state_map;
  state_names(state_map);

  io::CSVReader<5> in(argv[1]);
  in.read_header(io::ignore_extra_column, "reg_state","v_body_type","v_make","color","year");
  std::string reg_state, v_body_type, v_make, color, year;
  std::cout << "Building database..." << std::endl;
  while(in.read_row(reg_state, v_body_type, v_make, color, year)){
      Ticket* temp = new Ticket;
      if (auto search = state_map.find(reg_state); search != state_map.end()) {
          temp->_state = search->second;
      } else {
          temp->_state = NOWHERE;
      }
      if (auto search = makes_map.find(v_make); search != makes_map.end()) {
          temp->_make = search->second;
      } else {
          temp->_make = VEHICLE;
      }
      if (auto search = color_map.find(color); search != color_map.end()) {
          temp->_color = search->second;
      } else {
          temp->_color = UNKNOWN;
      }
      if (auto search = model_map.find(v_body_type); search != model_map.end()) {
          temp->_model = search->second;
      } else {
          temp->_model = DIM3;
      }
      temp->_year = interpret_year(year);
      ds_1.insert(temp);
  }
  std::cout << "Finished!" << std::endl;
  Window test = Window();
  test.start(ds_1);

  return 0;
}

Year interpret_year(std::string year) {
    if (year == "") return 0;
    else {
        Year y = 0;
        try {
            y = std::stoi(year);
        } catch (std::invalid_argument) {
            return 0;
        }
        if (y >= 1922 && y <= 2023) return y;
        else return 0;
    }
}
