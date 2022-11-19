//
// Created by a2-noori on 14/10/2022.
//

#ifndef PLATFORMERSFML_MENU_H
#define PLATFORMERSFML_MENU_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Menu
{
 public:
  Menu(float win_x, float win_y);
  void inputSwitch(int on);
  ~Menu();
  sf::Text menu_text;
  sf::Text play_text;
  sf::Text options_text;
  sf::Text exit_text;
  sf::Text placeholder_text;
 private:
  sf::Font menu_font;
  float window_x;
  float window_y;
};


#endif // PLATFORMERSFML_MENU_H
