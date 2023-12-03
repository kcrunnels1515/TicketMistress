#ifndef BONGOTREE_HPP
#define BONGOTREE_HPP
#include "Ticket.hpp"
#include <vector>
#include <map>
#include <set>
#include <algorithm>

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
    _size++;
  }
  void query(State state, Model model, Color color,
             Make make, Time time, char indep_vars) {
    // first 5 chars mark state, model, color, make, time
    // complement of

    std::set<Ticket*>& selected_data = {};
    std::set_intersection(_states[state].begin(), _states[state].end(),
                          _models[model].begin(), _models[model].end(),
                          std::inserter(selected_data, selected_data.begin()));
    if ((indep_vars & 32) == 32) {

    }
  }
};

#endif
