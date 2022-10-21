//
// Created by a2-noori on 21/10/2022.
//
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PACMANSFML_PLAYER_H
#define PACMANSFML_PLAYER_H

class Player
{
 public:
  Player();
  ~Player();
  void playerMovement();
  sf::Texture playerTexture;
  sf::Sprite playerSprite;
 private:
  sf::Texture playerTexture;
  sf::Sprite playerSprite;
}

#endif // PACMANSFML_PLAYER_H
