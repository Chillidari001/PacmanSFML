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
#include "Tile.h"

class TileHandler
{
 public:
  TileHandler(sf::RenderWindow& window);
  ~TileHandler();
  Tile tilesSprites[23][21];
  std::vector<std::vector<std::unique_ptr<Tile>>> TILE_MAP;

  tmx::Map map;

 private:
  sf::Texture tileMap;
  //::unique_ptr<sf::Texture> tileMap = std::make_unique<sf::Texture>();
  sf::RenderWindow& window;
};

#endif // PACMANSFML_TILEHANDLER_H
