//
// Created by awseb on 14/11/2022.
//

#include "Player.h"
#include "TileHandler.h"
#include "Game.h"


#ifndef PACMANSFML_COLLISIONHANDLER_H
#define PACMANSFML_COLLISIONHANDLER_H

class CollisionHandler
{
 public:
  CollisionHandler(sf::Window);
  sf::RenderWindow& window;

 private:
  ~CollisionHandler();
  std::unique_ptr<Player> player;
  std::unique_ptr<TileHandler> tileHandler;
};

#endif // PACMANSFML_COLLISIONHANDLER_H
