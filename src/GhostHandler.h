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
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

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
  sf::Sprite* sprite = nullptr;
  sf::Texture ghostTexture;
};

#endif // PACMANSFML_GHOSTHANDLER_H
