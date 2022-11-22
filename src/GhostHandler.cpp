//
// Created by awseb on 19/11/2022.
//

#include "GhostHandler.h"
GhostHandler::GhostHandler()
{
  if(!ghostTexture.loadFromFile(R"(E:\Learning Projects\PacmanSFML\Data\Images\PinkGhost.png)"))
  {
    std::cout << "Ghost texture not loaded" << std::endl;
  }
  ghostSprite.setTexture(ghostTexture);
  ghostSprite.setScale(0.025f, 0.025f);
  ghostSprite.setOrigin((sf::Vector2f)ghostTexture.getSize() / 2.f);

}
GhostHandler::~GhostHandler()
{

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
