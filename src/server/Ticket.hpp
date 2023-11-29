#ifndef TICKET_H_
#define TICKET_H_
#include <iostream>
enum State {
  AL,AK, AZ, AR, CA, CO, CT, DE, FL, GA, HI,
  ID, IL, IN, IA, KS, KY, LA, ME, MD, MA, MI,
  MN, MS, MO, MT, NE, NV, NH, NJ, NM, NY, NC,
  ND, OH, OK, OR, PA, RI, SC, SD, TN, TX, UT,
  VT, VA, WA, WV, WI, WY
};

enum Model {
  FORD,
  TOYOTA,
  CHEVY,
  HONDA,
  HYUND,
  JEEP,
  NISSAN,
  KIA,
  SUBARU,
  RAM,
  TESLA,
  GMC,
  BENZ,
  BMW,
  MAZDA,
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

class Ticket {
  private:
  State _state;
  Model _model;
  Color _color;
  Make _make;
  char* _time;

  public:
  Ticket(State state, Model model, Color color, Make make, std::string time)
    : _state(state), _model(model), _color(color), _make(make) {
    _time = new char[3];
    _time[0] = (char) std::stoi(time.substr(0,2));
    _time[1] = (char) std::stoi(time.substr(2,2));
    _time[2] = (char) time[5];
  }
  ~Ticket() {
    delete _time;
  }
};

#endif // TICKET_H_
