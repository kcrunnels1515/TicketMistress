#include "BongoTree.hpp"

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

void BongoTree::insert(Ticket* temp) {
    _states[temp->_state].insert(temp);
    _models[temp->_model].insert(temp);
    _colors[temp->_color].insert(temp);
    _makes[temp->_make].insert(temp);
    _years[temp->_year].insert(temp);
    _size++;
  }

void BongoTree::sizes() {
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

float BongoTree::query(Ticket input_match, unsigned char dep_vars) {
    // first 5 chars mark state, model, color, make, year
    // complement of

    // intersect fn intersect()
    std::set<Ticket*> dep_var_set;
    std::set<Ticket*> free_vars_all;
    std::set<Ticket*> free_vars_sel;

    if ((dep_vars & 16) == 16) {
      dep_var_set = _states[input_match._state];
    } else {
      for (auto it = _states.begin(); it != _states.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }
    //std::cout << "dep_var_set_size: " << dep_var_set.size() << std::endl;
    free_vars_sel = _states[input_match._state];

    if ((dep_vars & 8) == 8) {
      if (dep_var_set.empty()) dep_var_set = _models[input_match._model];
      else {
        dep_var_set = intersect(dep_var_set, _models[input_match._model]);
      }
    } else {
      for (auto it = _models.begin(); it != _models.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _models[input_match._model]);

    if ((dep_vars & 4) == 4) {
      if (dep_var_set.empty()) dep_var_set = _colors[input_match._color];
      else {
        dep_var_set = intersect(dep_var_set, _colors[input_match._color]);
      }
    } else {
      for (auto it = _colors.begin(); it != _colors.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _colors[input_match._color]);

    if ((dep_vars & 2) == 2) {
      if (dep_var_set.empty()) dep_var_set = _makes[input_match._make];
      else {
        dep_var_set = intersect(dep_var_set, _makes[input_match._make]);
      }
    } else {
      for (auto it = _makes.begin(); it != _makes.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }

    free_vars_sel = intersect(free_vars_sel, _makes[input_match._make]);

    if ((dep_vars & 1) == 1) {
      if (dep_var_set.empty()) dep_var_set = _years[input_match._year];
      else {
        dep_var_set = intersect(dep_var_set, _years[input_match._year]);
      }
    } else {
      for (auto it = _years.begin(); it != _years.end(); ++it) {
        free_vars_all.insert(it->second.begin(), it->second.end());
      }
    }
    free_vars_sel = intersect(free_vars_sel, _years[input_match._year]);
    float dep_var_size = (float) intersect(dep_var_set, free_vars_sel).size();
    float everything_else = (float) intersect(free_vars_all,free_vars_sel).size();
    return dep_var_size / everything_else;
  }
