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

int main(int argc,char* argv[]) {
  if (argc < 3) {
    std::cout << "Input: ./server [port] [csv file]" << std::endl;
    return -1;
  }
  int port;
  try {
    port = std::stoi(argv[1]);
  } catch (std::invalid_argument) {
    std::cout << "Not a number" << std::endl;
  }
  std::ifstream file(argv[2]);
  if(!file.is_open()){
     std::cout << "File not found" << std::endl;
     return -1;
  }

  BongoTree ds_1;
  LoadingWindow loading_window;
  loading_window.start(ds_1, argv[2]);


  Window test = Window();
  test.start(ds_1);

  return 0;
}


