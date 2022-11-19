//
// Created by awseb on 16/11/2022.
//

#ifndef PACMANSFML_TILE_H
#define PACMANSFML_TILE_H

#include "SFML/Graphics.hpp"
#include <memory>

class Tile
{
 public:
  Tile();
  Tile(const int& ID, const sf::Texture& texture);
  ~Tile() = default;
  std::unique_ptr<sf::Sprite>& GetSprite();
  int GetID() const;
  int tileID = 0;

 private:
  std::unique_ptr<sf::Sprite> tileSprite;
};

#endif // PACMANSFML_TILE_H
