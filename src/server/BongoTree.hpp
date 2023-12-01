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
  void insert(State state, Model model, Color color, Make make, Time time) {
    Ticket* temp = new Ticket(state,model,color,make,time);
    _states[state].insert(temp);
    _models[model].insert(temp);
    _colors[color].insert(temp);
    _makes[make].insert(temp);
    _times[time].insert(temp);
  }
};

#endif
