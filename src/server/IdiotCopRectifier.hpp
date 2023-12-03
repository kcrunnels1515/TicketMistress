#ifndef IDIOTCOPRECTIFIER_H_
#define IDIOTCOPRECTIFIER_H_

#include <map>
#include "Ticket.hpp"

void make_names(std::map<std::string,Make> &total);
void state_names(std::map<std::string,State>& states);
void colors_names(std::map<std::string,Color>& colors);
void model_names(std::map<std::string,Model>& bodies);

#endif // IDIOTCOPRECTIFIER_H_
