//
// Created by awseb on 19/11/2022.
//
#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef PACMANSFML_GHOSTHANDLER_H
#define PACMANSFML_GHOSTHANDLER_H

class GhostHandler
{
 public:
  GhostHandler();
  ~GhostHandler();
  void ghostMovement();
  sf::Sprite ghostSprite;

  enum ghostState
  {
    SLEEP,
    CHASE,
    SCATTER
  };

  enum ghostMovement
  {
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_STATIONARY
  };
  enum ghostMovement ghostMovementState = MOVE_STATIONARY;
  enum ghostState ghostCurrentState = SLEEP;

 private:
  //sf::Texture playerTexture;
  //sf::Sprite playerSprite;
  sf::Texture ghostTexture;
};

#endif // PACMANSFML_GHOSTHANDLER_H
