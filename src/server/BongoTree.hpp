#ifndef BONGOTREE_HPP
#define BONGOTREE_HPP
#include "Ticket.hpp"
#include <vector>
#include <map>
#include <set>

class BongoTree {
  private:
  size_t _size;
  std::map<State,std::set<Ticket*>> _states;
  std::map<Model,std::set<Ticket*>> _models;
  std::map<Color,std::set<Ticket*>> _colors;
  std::map<Make,std::set<Ticket*>>  _makes;
  std::map<Time,std::set<Ticket*>>  _times;
  public:
  BongoTree() {}
  void insert(Ticket* temp) {
    _states[temp->_state].insert(temp);
    _models[temp->_model].insert(temp);
    _colors[temp->_color].insert(temp);
    _makes[temp->_make].insert(temp);
    _times[temp->_time].insert(temp);
  }
};

#endif
