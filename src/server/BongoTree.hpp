#ifndef BONGOTREE_HPP
#define BONGOTREE_HPP
#include "Ticket.hpp"
#include <vector>

struct StateContainer {
  State _state;
  StateContainer(State state) : _state(state) {}
};

class BongoTree {
  private:
  StateContainer* _states[50];
  public:
  BongoTree() {
    StateContainer* temp;
    for (int i = 0; i < 50; i++) {
      temp = new StateContainer((State)i);
      _states[i] = temp;
    }
  }
};

#endif
