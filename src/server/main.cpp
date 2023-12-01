#include <fstream>
#include <iostream>
#include <regex>
#include "../lib/csv.hpp"
#include "BongoTree.hpp"
#include "Ticket.hpp"

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
  io::CSVReader<6> in(argv[2]);
  in.read_header(io::ignore_extra_column, "reg_state","v_body_type","v_make","voilation_time","color","year");
  std::string reg_state, v_body_type, v_make, voi_time, color, year;
  while(in.read_row(reg_state, v_body_type, v_make, voi_time, color, year)){
    std::cout << "One line parsed" << std::endl;
  }
  return 0;
}
