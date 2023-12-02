#ifndef TICKET_H_
#define TICKET_H_
#include <iostream>
enum State {
  AL = 0, AK, AZ, AR, CA, CO, CT, DE, FL, GA, HI,
  ID, IL, IN, IA, KS, KY, LA, ME, MD, MA, MI,
  MN, MS, MO, MT, NE, NV, NH, NJ, NM, NY, NC,
  ND, OH, OK, OR, PA, RI, SC, SD, TN, TX, UT,
  VT, VA, WA, WV, WI, WY
};

enum Model {
  BENZ,
  BMW,
  BUICK,
  CHEVY,
  FORD,
  GMC,
  HONDA,
  HYUND,
  JEEP,
  KIA,
  MAZDA,
  NISSAN,
  RAM,
  SUBARU,
  TESLA,
  TOYOTA,
  VOLKS,
  OTHER
};

enum Color {
  RED,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  PURPLE,

};

enum Make {
  SEDAN,
  SUV,
  ELECTRIC,
  MINIVAN,
  PICKUP
};

enum Time {
  MIDNIGHT,
};

struct Ticket {
  State _state; // map to set of elements with same state ps, don't use unordered set,
                // you can't do set intersection
  Model _model;
  Color _color;
  Make _make;
  Time _time;
  Ticket(State state, Model model, Color color, Make make, Time time)
    : _state(state), _model(model), _color(color), _make(make), _time(time) {}
  ~Ticket() {}
};

#endif // TICKET_H_
