
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "ResourceHandler.h"
#include "Menu.h"
#include <memory>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);

 private:
  sf::RenderWindow& window;
  //std::unique_ptr<ResourceHandler> resources;

  Menu* menu;
  int menu_selected = 1;

  enum gameScreen
  {
    MENU_SCREEN,
    SETTINGS_SCREEN,
    GAME_SCREEN,
    PAUSE_SCREEN,
    WIN_SCREEN,
    LOSE_SCREEN
  };

  enum gameScreen game_state = gameScreen::MENU_SCREEN;

  enum activeLevel
  {
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
  };
};

#endif // PLATFORMER_GAME_H
