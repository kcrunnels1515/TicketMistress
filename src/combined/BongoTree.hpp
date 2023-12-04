#ifndef BONGOTREE_HPP
#define BONGOTREE_HPP
#pragma once
#include "Ticket.hpp"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

std::set<Ticket*> intersect(std::set<Ticket*>& set1, std::set<Ticket*>& set2);

class BongoTree {
  private:
  size_t _size;
  std::map<State,std::set<Ticket*>> _states;
  std::map<Model,std::set<Ticket*>> _models;
  std::map<Color,std::set<Ticket*>> _colors;
  std::map<Make,std::set<Ticket*>>  _makes;
  std::map<Year,std::set<Ticket*>>  _years;
  public:
  BongoTree() {}
  void insert(Ticket* temp);
  void sizes();
  std::pair<float,std::set<Ticket*>> query(Ticket input_match, unsigned char dep_vars);
};

#endif
