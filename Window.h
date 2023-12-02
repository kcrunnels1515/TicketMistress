//
// Created by micha on 12/1/2023.
//

#ifndef SFML_TEST_WINDOW_H
#define SFML_TEST_WINDOW_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
using namespace std;

using namespace std;

class Window {
    string name;

public:
    Window();
    sf::RectangleShape setRectangle(sf::Vector2f s,float x, float y, float o_x, float o_y, sf::Color color);
    void printText(string txt, bool u, float x, float y, sf::RenderWindow *window, int f_size, bool w, bool bold);
    string start();
};


#endif //SFML_TEST_WINDOW_H
