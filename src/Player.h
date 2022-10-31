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
  void playerInput();
  sf::Texture playerTexture;
  sf::Sprite playerSprite;
 private:
  //sf::Texture playerTexture;
  //sf::Sprite playerSprite;
  enum playerMovement
  {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_STATIONARY
  };
  enum playerMovement playerMovementState = MOVE_STATIONARY;

  sf::Vector2f newOrigin;
};

#endif // PACMANSFML_PLAYER_H
