#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "Ticket.hpp"
#include "BongoTree.hpp"
using namespace std;

using namespace std;

class Window {
    string name;

public:
    Window();
    sf::RectangleShape setRectangle(sf::Vector2f s,float x, float y, float o_x, float o_y, sf::Color color);
    void printText(string txt, bool u, float x, float y, sf::RenderWindow *window, int f_size, bool w, bool bold);
    vector<string> start(BongoTree& btree);
    void SecondScreen(Ticket input_match, sf::RenderWindow& window, BongoTree& btree);
};
