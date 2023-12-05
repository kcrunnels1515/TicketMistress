#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Ticket.hpp"
#include "BongoTree.hpp"
#include "BongoHashMap.h"
#include "../lib/csv.hpp"
#include "IdiotCopRectifier.hpp"
using namespace std;

using namespace std;

class Window {
    string name;
    std::vector<std::pair<State, std::string>> statesList;
    std::vector<std::pair<Make,std::string>> makesList;
    std::vector<std::pair<Model,std::string>> modelsList;
    std::vector<std::pair<Color,std::string>> colorsList;

public:
    Window();
    sf::RectangleShape setRectangle(sf::Vector2f s,float x, float y, float o_x, float o_y, sf::Color color);
    void printText(string txt, bool u, float x, float y, sf::RenderWindow *window, int f_size, bool w, bool bold);
    vector<string> start(BongoTree& btree, BongoHashMap& hmap);
    void SecondScreen(Ticket input_match, sf::RenderWindow& window, BongoTree& btree, BongoHashMap& hmap, unsigned char indep_vars, bool tree_or_map);
    bool pickScreen();
};



Year interpret_year(std::string year);
