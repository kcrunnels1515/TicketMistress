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

float BongoTree::query(Ticket input_match, unsigned char indep_vars) {
    // first 5 chars mark state, model, color, make, year
    // complement of

    // intersect fn intersect()
    std::set<Ticket*> numerator_set;  // this should contain the intersections
                                      // of all bongotree sets the correspond
                                      // to inputted values
    std::set<Ticket*> denominator_set; // this should contain the intersection between
                                      // the inputted value sets, and a set containing
                                      // the values of the free variables

    numerator_set = _states[input_match._state];
    numerator_set = intersect(numerator_set, _models[input_match._model]);
    numerator_set = intersect(numerator_set, _colors[input_match._color]);
    numerator_set = intersect(numerator_set, _makes[input_match._make]);
    numerator_set = intersect(numerator_set, _years[input_match._year]);


    // STATES
    if ((indep_vars & 16) == 16) {
      for (auto it = _states.begin(); it != _states.end(); ++it) {
        denominator_set.insert(it->second.begin(), it->second.end());
      }
    } else {
      denominator_set = _states[input_match._state];
    }

    // MODELS
    if ((indep_vars & 8) == 8) {
      if (denominator_set.empty()) {
        for (auto it = _models.begin(); it != _models.end(); ++it) {
          denominator_set.insert(it->second.begin(), it->second.end());
        }
      }
      else {
        std::set<Ticket*> temp;
        for (auto it = _models.begin(); it != _models.end(); ++it) {
          temp.insert(it->second.begin(), it->second.end());
        }
      }
    } else {
      denominator_set = intersect(denominator_set, _models[input_match._model]);
    }

    // COLORS
    if ((indep_vars & 4) == 4) {
      if (denominator_set.empty()) {
        for (auto it = _colors.begin(); it != _colors.end(); ++it) {
          denominator_set.insert(it->second.begin(), it->second.end());
        }
      }
      else {
        std::set<Ticket*> temp;
        for (auto it = _colors.begin(); it != _colors.end(); ++it) {
          temp.insert(it->second.begin(), it->second.end());
        }
      }
    } else {
      denominator_set = intersect(denominator_set, _colors[input_match._color]);
    }

    // MAKES
    if ((indep_vars & 2) == 2) {
      if (denominator_set.empty()) {
        for (auto it = _makes.begin(); it != _makes.end(); ++it) {
          denominator_set.insert(it->second.begin(), it->second.end());
        }
      }
      else {
        std::set<Ticket*> temp;
        for (auto it = _models.begin(); it != _models.end(); ++it) {
          temp.insert(it->second.begin(), it->second.end());
        }
      }
    } else {
      denominator_set = intersect(denominator_set, _models[input_match._model]);
    }

    free_vars_sel = intersect(free_vars_sel, _makes[input_match._make]);

    // YEARS
    if ((indep_vars & 1) == 1) {
      if (dep_var_set.empty()) dep_var_set = _years[input_match._year];
      else {
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
