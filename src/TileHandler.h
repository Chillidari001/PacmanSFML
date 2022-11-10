//
// Created by awseb on 31/10/2022.
//

#ifndef PACMANSFML_TILEHANDLER_H
#define PACMANSFML_TILEHANDLER_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"
#include "Player.h"

class TileHandler
{
 public:
  TileHandler(sf::RenderWindow& window);
  ~TileHandler();
  sf::Sprite tilesSprites[23][21];
  std::unique_ptr<Player> player;

  tmx::Map map;

 private:
  sf::Texture tileMap;
  sf::RenderWindow& window;
};

#endif // PACMANSFML_TILEHANDLER_H
