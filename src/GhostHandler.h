//
// Created by awseb on 19/11/2022.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef PACMANSFML_GHOSTHANDLER_H
#define PACMANSFML_GHOSTHANDLER_H

class GhostHandler
{
 public:
  GhostHandler();
  ~GhostHandler();
  void ghostStateHandler(int player_x, int player_y, int ghost_num, bool collided);
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  void ghostStateChange();
  void ghostMovementPattern1(int player_x, int player_y, bool collided);
  void ghostMovement();
  void initialMovement();
  void blockHandler(bool collided);

  bool block_left = false;
  bool block_right = false;
  bool block_up = false;
  bool block_down = false;

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
  enum ghostState ghostCurrentState = CHASE;

  sf::Clock sleepTimer;

  bool initial_x = true;
  bool initial_y = false;
  bool initial_complete = false;

 private:
  sf::Sprite* sprite = nullptr;
  sf::Texture ghostTexture;

  float ghost_speed_x;
  float ghost_speed_y;
};

#endif // PACMANSFML_GHOSTHANDLER_H
