//
// Created by awseb on 31/10/2022.
//

#ifndef PACMANSFML_TILEHANDLER_H
#define PACMANSFML_TILEHANDLER_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "tmxlite/Map.hpp"
#include "tmxlite/TileLayer.hpp"

class TileHandler
{
 public:
  TileHandler();
  ~TileHandler();
  sf::Sprite tilesSprites[23][21];

 private:
  sf::Texture tileMap;
  tmx::Map map;
};

#endif // PACMANSFML_TILEHANDLER_H
