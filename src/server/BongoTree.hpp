#ifndef BONGOTREE_HPP
#define BONGOTREE_HPP
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
  void insert(Ticket* temp) {
    _states[temp->_state].insert(temp);
    _models[temp->_model].insert(temp);
    _colors[temp->_color].insert(temp);
    _makes[temp->_make].insert(temp);
    _years[temp->_year].insert(temp);
    _size++;
  }
  void sizes() {
    for (auto it = _states.begin(); it != _states.end(); ++it) {
      std::cout << it->first << ": " << it->second.size() << std::endl;
    }
    for (auto it = _models.begin(); it != _models.end(); ++it) {
      std::cout << it->first << ": " << it->second.size() << std::endl;
    }
    for (auto it = _colors.begin(); it != _colors.end(); ++it) {
      std::cout << it->first << ": " << it->second.size() << std::endl;
    }
    for (auto it = _makes.begin(); it != _makes.end(); ++it) {
      std::cout << it->first << ": " << it->second.size() << std::endl;
    }
    for (auto it = _years.begin(); it != _years.end(); ++it) {
      std::cout << it->first << ": " << it->second.size() << std::endl;
    }
  }
  float query(State state, Model model, Color color,
             Make make, Year year, unsigned char dep_vars) {
    // first 5 chars mark state, model, color, make, year
    // complement of

    /////////////////////////////////////////////////////////////////////////////////
    // std::set<Ticket*> selected_data;                                            //
    // std::set_intersection(_states[state].begin(), _states[state].end(),         //
    //                       _models[model].begin(), _models[model].end(),         //
    //                       std::inserter(selected_data, selected_data.begin())); //
    // if ((dep_vars & 32) == 32) {                                              //
    // }                                                                           //
    /////////////////////////////////////////////////////////////////////////////////

    // intersect fn intersect()
    std::set<Ticket*> dep_var_set;
    std::set<Ticket*> free_vars_all;
    std::set<Ticket*> free_vars_sel;

    // build sets
    // intersect(dep_vars, free_vars_sel)  <- set of matching selected tickets
    // intersect(free_vars_all, dep_vars); <- set of matching tickets with varied free vars

    //dep_var_set = intersect(_states[state], _models[model]);
    //dep_var_set = intersect(dep_var_set, _colors[color]);
    //dep_var_set = intersect(dep_var_set, _makes[make]);
    //dep_var_set = intersect(dep_var_set, _years[year]);

    if ((dep_vars & 16) == 16) {
      dep_var_set = _states[state];
    } else {
      for (auto it = _states.begin(); it != _states.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }
    //std::cout << "dep_var_set_size: " << dep_var_set.size() << std::endl;
    free_vars_sel = _states[state];

    if ((dep_vars & 8) == 8) {
      if (dep_var_set.empty()) dep_var_set = _models[model];
      else {
        dep_var_set = intersect(dep_var_set, _models[model]);
      }
    } else {
      for (auto it = _models.begin(); it != _models.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _models[model]);

    if ((dep_vars & 4) == 4) {
      if (dep_var_set.empty()) dep_var_set = _colors[color];
      else {
        dep_var_set = intersect(dep_var_set, _colors[color]);
      }
    } else {
      for (auto it = _colors.begin(); it != _colors.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _models[model]);

    if ((dep_vars & 2) == 2) {
      if (dep_var_set.empty()) dep_var_set = _makes[make];
      else {
        dep_var_set = intersect(dep_var_set, _makes[make]);
      }
    } else {
      for (auto it = _makes.begin(); it != _makes.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _makes[make]);

    if ((dep_vars & 1) == 1) {
      if (dep_var_set.empty()) dep_var_set = _years[year];
      else {
        dep_var_set = intersect(dep_var_set, _years[year]);
      }
    } else {
      for (auto it = _years.begin(); it != _years.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }
    free_vars_sel = intersect(free_vars_sel, _years[year]);
    float dep_var_size = (float) intersect(dep_var_set, free_vars_sel).size();
    float everything_else = (float) intersect(free_vars_all,free_vars_sel).size();
    return dep_var_size / everything_else;
  }
};

std::set<Ticket*> intersect(std::set<Ticket*>& set1, std::set<Ticket*>& set2) {
  std::set<Ticket*> results;
  if (set1.size() < set2.size()) {
    for (Ticket* i : set1) {
      if (set2.find(i) != set2.end())
        results.insert(i);
    }
  } else {
    for (Ticket* i : set2) {
      if (set1.find(i) != set1.end())
        results.insert(i);
    }
  }
  return results;
}

#endif
