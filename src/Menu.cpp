//
// Created by a2-noori on 14/10/2022.
//

#include "Menu.h"

Menu::~Menu()
{

}

Menu::Menu(float win_x, float win_y)
{
  window_x = win_x;
  window_y = win_y;

  if (!menu_font.loadFromFile("Data/Fonts/OpenSans-Italic.ttf"))
  {
    std::cout << "Menu font not loaded" << std::endl;
  }

  menu_text.setFont(menu_font);
  menu_text.setString("PACMAN");
  menu_text.setCharacterSize(80);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);

  play_text.setFont(menu_font);
  play_text.setString("PLAY");
  play_text.setCharacterSize(60);
  play_text.setFillColor(sf::Color::White);
  play_text.setPosition(window_x/3.1 - play_text.getGlobalBounds().width/2, window_y/2 - play_text.getGlobalBounds().height/2);

  options_text.setFont(menu_font);
  options_text.setString("OPTIONS");
  options_text.setCharacterSize(40);
  options_text.setFillColor(sf::Color::White);
  options_text.setPosition(window_x/2.2 - options_text.getGlobalBounds().width/6, window_y/2 - options_text.getGlobalBounds().height/2);

  exit_text.setFont(menu_font);
  exit_text.setString("EXIT");
  exit_text.setCharacterSize(40);
  exit_text.setFillColor(sf::Color::White);
  exit_text.setPosition(window_x/1.5 - exit_text.getGlobalBounds().width/10, window_y/2 - exit_text.getGlobalBounds().height/2);

  placeholder_text.setFont(menu_font);
  placeholder_text.setString("PLACEHOLDER");
  placeholder_text.setCharacterSize(80);
  placeholder_text.setFillColor(sf::Color::White);
  placeholder_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);
}

void Menu::inputSwitch(int on)
{
  if (on == 1)
  {
    menu_text.setFont(menu_font);
    menu_text.setString("PACMAN");
    menu_text.setCharacterSize(80);
    menu_text.setFillColor(sf::Color::White);
    menu_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);


    play_text.setFont(menu_font);
    play_text.setString("PLAY");
    play_text.setCharacterSize(60);
    play_text.setFillColor(sf::Color::White);
    play_text.setPosition(window_x/3.1 - play_text.getGlobalBounds().width/3, window_y/2 - play_text.getGlobalBounds().height/2);

    options_text.setFont(menu_font);
    options_text.setString("OPTIONS");
    options_text.setCharacterSize(40);
    options_text.setFillColor(sf::Color::White);
    options_text.setPosition(window_x/2.2 - options_text.getGlobalBounds().width/6, window_y/2 - options_text.getGlobalBounds().height/2);

    exit_text.setFont(menu_font);
    exit_text.setString("EXIT");
    exit_text.setCharacterSize(40);
    exit_text.setFillColor(sf::Color::White);
    exit_text.setPosition(window_x/1.5 - exit_text.getGlobalBounds().width/10, window_y/2 - exit_text.getGlobalBounds().height/2);
  }

  if (on == 2)
  {
    menu_text.setFont(menu_font);
    menu_text.setString("PACMAN");
    menu_text.setCharacterSize(80);
    menu_text.setFillColor(sf::Color::White);
    menu_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);

    play_text.setFont(menu_font);
    play_text.setString("PLAY");
    play_text.setCharacterSize(40);
    play_text.setFillColor(sf::Color::White);
    play_text.setPosition(window_x/3.1 - play_text.getGlobalBounds().width/3, window_y/2 - play_text.getGlobalBounds().height/2);

    options_text.setFont(menu_font);
    options_text.setString("OPTIONS");
    options_text.setCharacterSize(60);
    options_text.setFillColor(sf::Color::White);
    options_text.setPosition(window_x/2.2 - options_text.getGlobalBounds().width/6, window_y/2 - options_text.getGlobalBounds().height/2);


    exit_text.setFont(menu_font);
    exit_text.setString("EXIT");
    exit_text.setCharacterSize(40);
    exit_text.setFillColor(sf::Color::White);
    exit_text.setPosition(window_x/1.5 - exit_text.getGlobalBounds().width/10, window_y/2 - exit_text.getGlobalBounds().height/2);
  }

  if (on == 3)
  {
    menu_text.setFont(menu_font);
    menu_text.setString("PACMAN");
    menu_text.setCharacterSize(80);
    menu_text.setFillColor(sf::Color::White);
    menu_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);

    play_text.setFont(menu_font);
    play_text.setString("PLAY");
    play_text.setCharacterSize(40);
    play_text.setFillColor(sf::Color::White);
    play_text.setPosition(window_x/3.1 - play_text.getGlobalBounds().width/3, window_y/2 - play_text.getGlobalBounds().height/2);

    options_text.setFont(menu_font);
    options_text.setString("OPTIONS");
    options_text.setCharacterSize(40);
    options_text.setFillColor(sf::Color::White);
    options_text.setPosition(window_x/2.2 - options_text.getGlobalBounds().width/6, window_y/2 - options_text.getGlobalBounds().height/2);

    exit_text.setFont(menu_font);
    exit_text.setString("EXIT");
    exit_text.setCharacterSize(60);
    exit_text.setFillColor(sf::Color::White);
    exit_text.setPosition(window_x/1.5 - exit_text.getGlobalBounds().width/10, window_y/2 - exit_text.getGlobalBounds().height/2);
  }
}

void Menu::settingsSwitch(int on)
{
  if (on == 0)
  {
    placeholder_text.setFont(menu_font);
    placeholder_text.setString("PLACEHOLDER");
    placeholder_text.setCharacterSize(80);
    placeholder_text.setFillColor(sf::Color::White);
    placeholder_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);
  }
  if(on == 1)
  {
    placeholder_text.setFont(menu_font);
    placeholder_text.setString("PLACEHOLDER");
    placeholder_text.setCharacterSize(80);
    placeholder_text.setFillColor(sf::Color::Red);
    placeholder_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);
  }
  if(on == 2)
  {
    placeholder_text.setFont(menu_font);
    placeholder_text.setString("PLACEHOLDER");
    placeholder_text.setCharacterSize(80);
    placeholder_text.setFillColor(sf::Color::Blue);
    placeholder_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);
  }
  if(on == 3)
  {
    placeholder_text.setFont(menu_font);
    placeholder_text.setString("PLACEHOLDER");
    placeholder_text.setCharacterSize(80);
    placeholder_text.setFillColor(sf::Color::Green);
    placeholder_text.setPosition(window_x/2 - menu_text.getGlobalBounds().width/2, window_y/2 - menu_text.getGlobalBounds().height*6);
  }
}