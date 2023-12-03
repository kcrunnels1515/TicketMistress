#ifndef TICKET_H_
#define TICKET_H_
#include <iostream>
enum State {
  AL = 0, AK, AZ, AR, CA, CO, CT, DE, FL, GA,
  HI, ID, IL, IN, IA, KS, KY, LA, ME, MD, MA,
  MI, MN, MS, MO, MT, NE, NV, NH, NJ, NM, NY,
  NC, ND, OH, OK, OR, PA, RI, SC, SD, TN, TX,
  UT, VT, VA, WA, WV, WI, WY, NOWHERE
};

enum Make {
  ACURA = 0, ALPINA, ALFAROM, AUDI, BENZ, BMW, BUICK, CHEVY, FORD, GMC, HONDA, HYUND,
  NISSAN, RAM, SUBARU, TESLA, TOYOTA, VOLKS, CHRYS, DODGE, FIAT, GM, ISUZU, CADDIE,
  INTERNATL, JAG, KWORTH, LAMBO, LEXUS, LINCOLN, ROVER, MACK, MASR, MERC, MINI, MITSU,
  PORSCE, PONTIAC, SATURN, SMART, SUZUKU, UD, VOLVO, WORKHORS, OTHER, JEEP, KIA, MAZDA,
  VEHICLE
};

enum Color {
  RED = 0, ORANGE, YELLOW,
  GREEN, BLUE, PURPLE,
  BLACK, GREY, UNKNOWN,
  BROWN, GOLD, WHITE,
  LIGHT, NAVY, PINK,
  REDORANGE, SILVER,
  TAN
};

enum Model {
  MOTORCYCLE = 0,
  SPORT,
  SUBN,
  SEDAN4D,
  SUV,
  ELECTRIC,
  MINIVAN,
  PICKUP,
  BUS,
  DUMP,
  FLATBED,
  MOPED,
  SEDAN2D,
  TAXI,
  TRACTOR,
  TRAILER,
  UTILITY,
  VAN,
  SEMI,
  FWD,
  TWD,
  CONV,
  DIM3
};

typedef int Time;
typedef int Year;

struct Ticket {
  State _state; // map to set of elements with same state ps, don't use unordered set,
                // you can't do set intersection
  Model _model;
  Color _color;
  Make _make;
  Year _year;
  Ticket() {}
  Ticket(State state, Make make, Color color, Model model, Year year)
    : _state(state), _model(model), _color(color), _make(make), _year(year) {}
  ~Ticket() {}
};

#endif // TICKET_H_
