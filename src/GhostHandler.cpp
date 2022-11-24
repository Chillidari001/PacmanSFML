//
// Created by awseb on 19/11/2022.
//

#include "GhostHandler.h"
GhostHandler::GhostHandler()
{
  sprite =  new sf::Sprite();

}
GhostHandler::~GhostHandler()
{
  delete sprite;
  sprite = nullptr;
}

bool GhostHandler::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << "failed to load";
  }
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GhostHandler::getSprite()
{
  return sprite;
}

void GhostHandler::ghostMovement()
{
  switch(ghostCurrentState)
  {
    case SLEEP:
      //std::cout << "Ghost Sleeping" << "\n";
      break;
    case CHASE:
      break;
    case SCATTER:
      break;
  }
}
