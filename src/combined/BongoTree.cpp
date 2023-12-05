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

std::pair<float,std::vector<Ticket*>> BongoTree::query(Ticket input_match, unsigned char indep_vars) {
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
        for (auto it = _makes.begin(); it != _makes.end(); ++it) {
          temp.insert(it->second.begin(), it->second.end());
        }
      }
    } else {
      denominator_set = intersect(denominator_set, _makes[input_match._make]);
    }

    // YEARS
    if ((indep_vars & 1) == 1) {
      if (denominator_set.empty()) {
        for (auto it = _years.begin(); it != _years.end(); ++it) {
          denominator_set.insert(it->second.begin(), it->second.end());
        }
      }
      else {
        std::set<Ticket*> temp;
        for (auto it = _years.begin(); it != _years.end(); ++it) {
          temp.insert(it->second.begin(), it->second.end());
        }
      }
    } else {
      denominator_set = intersect(denominator_set, _years[input_match._year]);
    }

    auto it = numerator_set.begin();
    std::vector<Ticket*> result_vec;
    for (int i = 0; i < 8; i++) {
      result_vec.push_back(*it);
      ++it;
      if (it == numerator_set.end()) break;
    }

    return make_pair(((float) numerator_set.size() / (float) denominator_set.size()), result_vec);
  }
