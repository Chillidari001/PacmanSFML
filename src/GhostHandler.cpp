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

  srand(time(NULL));
}

bool GhostHandler::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << "failed to load";
  }
  sprite->setTexture(texture);
  sprite->setOrigin((sf::Vector2f)texture.getSize() / 2.f);

  return true;
}

sf::Sprite* GhostHandler::getSprite()
{
  return sprite;
}

void GhostHandler::ghostStateChange()
{
//  int sleepTimerCheck = sleepTimer.getElapsedTime().asSeconds();
//  if(sleepTimerCheck >= 5)
//  {
//    if(ghostCurrentState == GhostHandler::SLEEP)
//    {
//      ghostCurrentState = GhostHandler::CHASE;
//    }
//  }
}

void GhostHandler::ghostMovement()
{
  switch(ghostMovementState)
  {
    case MOVE_LEFT:
      if(block_left == false)
      {
        ghost_speed_x = -1.5f;
        ghost_speed_y = 0.0f;
        sprite->move(ghost_speed_x,ghost_speed_y);
        //      sprite->setRotation(180.0f);
        //std::cout << "Player move left" << std::endl;
      }
      break;
    case MOVE_RIGHT:
      ghost_speed_x = 1.5f;
      ghost_speed_y = 0.0f;
      sprite->move(ghost_speed_x,ghost_speed_y);
//      sprite->setRotation(0.f);
      //std::cout << "Player move right" << std::endl;
      break;
    case MOVE_UP:
      ghost_speed_x = 0.0f;
      ghost_speed_y = -1.5f;
      sprite->move(ghost_speed_x,ghost_speed_y);
//      sprite->setRotation(-90.f);
      //std::cout << "Player move up" << std::endl;
      break;
    case MOVE_DOWN:
      if(block_down == false)
      {
        ghost_speed_x = 0.0f;
        ghost_speed_y = 1.5f;
        sprite->move(ghost_speed_x,ghost_speed_y);
        //      sprite->setRotation(90.f);
        //std::cout << "Player move down" << std::endl;
      }
      break;
    case MOVE_STATIONARY:
      ghost_speed_x = 0.0f;
      ghost_speed_y = 0.0f;
      sprite->move(ghost_speed_x,ghost_speed_y);
      //std::cout << "Player stationary" << std::endl;
      break;
  }
  //std::cout << std::to_string(playerSprite.getLocalBounds());
}

void GhostHandler::initialMovement()
{
  if(initial_x)
  {
    if(sprite->getPosition().x < 548)
    {
      ghostMovementState = GhostHandler::MOVE_RIGHT;
    }
    if(sprite->getPosition().x > 552)
    {
      ghostMovementState = GhostHandler::MOVE_LEFT;
    }
    if(sprite->getPosition().x >= 549 && sprite->getPosition().x <= 551)
    {
      initial_x = false;
      initial_y = true;
    }
  }

  if(initial_y)
  {
    ghostMovementState = GhostHandler::MOVE_UP;
    if(sprite->getPosition().y >= 180 && sprite->getPosition().y <= 189)
    {
      initial_y = false;
      ghostMovementState = GhostHandler::MOVE_STATIONARY;
    }
  }

  if(initial_x == false && initial_y == false)
  {
    initial_complete = true;
  }
}

//handles the blocking of each movement state if collided in and makes ghost choose another randomly.
//helps handle the AI without the I. PLan to have direction chosen dependent on certain conditions instead
//of pure rng maybe?
void GhostHandler::blockHandler(bool collided)
{
  if(collided && ghostMovementState == GhostHandler::MOVE_LEFT)
  {
    sf::Clock block_timer;
    block_timer.restart();
    block_left = true;
    int randBlockNum = (rand() % 3) + 1;
    if(randBlockNum == 1)
    {
      ghostMovementState = GhostHandler::MOVE_RIGHT;
    }

    if(randBlockNum == 2)
    {
      ghostMovementState = GhostHandler::MOVE_UP;
    }

    if(randBlockNum == 3)
    {
      ghostMovementState = GhostHandler::MOVE_DOWN;
    }

    sf::Time block_timer_elapsed = block_timer.restart();
    if(block_timer_elapsed.asSeconds() >= 1)
    {
      block_left = false;
    }
  }

  if(collided && ghostMovementState == GhostHandler::MOVE_DOWN)
  {
    sf::Clock block_timer;
    block_timer.restart();
    block_down       = true;
    int randBlockNum = (rand() % 3) + 1;
    if (randBlockNum == 1)
    {
      ghostMovementState = GhostHandler::MOVE_UP;
    }

    if (randBlockNum == 2)
    {
      ghostMovementState = GhostHandler::MOVE_LEFT;
    }

    if (randBlockNum == 3)
    {
      ghostMovementState = GhostHandler::MOVE_RIGHT;
    }

    sf::Time block_timer_elapsed = block_timer.restart();
    if (block_timer_elapsed.asSeconds() >= 1)
    {
      block_down = false;
    }
  }
}

//first movement pattern for one of the ghost, plan is to have different patterns for each ghost to mimic the original
//pacman which gave each ghost a different target and such to add extra personality and difficulty.
void GhostHandler::ghostMovementPattern1(int player_x, int player_y, bool collided)
{
  blockHandler(collided);
//  std::cout << sprite->getPosition().x << " " << sprite->getPosition().y << "\n";
float distance_x = sqrt(
        powf(
          player_x -
            sprite->getPosition().x,
          2));
float distance_y= sqrt(
          powf(
            player_y -
              sprite->getPosition().y,
            2));

  if (initial_complete == false)
  {
    initialMovement();
  }
  else
  {
    if(distance_x > distance_y)
    {
      std::cout << "X" << "\n";
      if(player_x > sprite->getPosition().x)
      {
        ghostMovementState = GhostHandler::MOVE_RIGHT;
      }
      if(player_x < sprite->getPosition().x)
      {
        ghostMovementState = GhostHandler::MOVE_LEFT;
      }
    }

    if(distance_y > distance_x)
    {
      std::cout << "Y" << "\n";
      if(player_y > sprite->getPosition().y)
      {
        ghostMovementState = GhostHandler::MOVE_DOWN;
      }
      if(player_y < sprite->getPosition().y)
      {
        ghostMovementState = GhostHandler::MOVE_UP;
      }
    }
  }

//  std::cout << ghostMovementState;
//  std::cout << initial_x;
//  std::cout << sprite->getPosition().x << "\n";
//  std::cout << initial_y;
//  std::cout << sprite->getPosition().y << "\n";
}

void GhostHandler::ghostStateHandler(int player_x, int player_y, int ghost_num, bool collided)
{
  switch(ghostCurrentState)
  {
    case SLEEP:
      //std::cout << "Ghost Sleeping" << "\n";
      break;
    case CHASE:
      if(ghost_num == 1)
      {
        ghostMovementPattern1(player_x, player_y, collided);
      }
      break;
    case SCATTER:
      break;
  }
}
