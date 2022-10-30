#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceHandler.h"
#include "Menu.h"
#include <memory>
#include "Player.h"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"//multipled "multiple definition" errors on home pc, clueless as to why.
#include <vector>

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
  void tileHandler();

 private:
  sf::RenderWindow& window;
  //std::unique_ptr<ResourceHandler> resources;

  //Menu* menu;
  std::unique_ptr<Player> player;
  std::unique_ptr<Menu> menu;
  int menu_selected = 1;

  sf::Texture tileMap;
  tmx::Map map;
  sf::Sprite tilesSprites[23][21];

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