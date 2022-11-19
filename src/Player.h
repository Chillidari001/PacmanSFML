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
  sf::Sprite playerSprite;

  enum playerMovement
  {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_STATIONARY
  };
  enum playerMovement playerMovementState = MOVE_STATIONARY;

  enum playerBlock
  {
    BLOCK_LEFT,
    BLOCK_RIGHT,
    BLOCK_UP,
    BLOCK_DOWN,
    BLOCK_NONE
  };

  void playerBlockUpdate();

  enum playerBlock playerBlockState = BLOCK_NONE;

 private:
  //sf::Texture playerTexture;
  //sf::Sprite playerSprite;
  sf::Texture playerTexture;
};

#endif // PACMANSFML_PLAYER_H
