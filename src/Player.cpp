//
// Created by a2-noori on 21/10/2022.
//

#include "Player.h"

Player::Player()
{
  if(!playerTexture.loadFromFile("Data/Images/pacman.png"))
  {
    std::cout << "Player texture not loaded" << std::endl;
  }

  playerSprite.setTexture(playerTexture);

  playerSprite.setScale(0.040f, 0.040f);

//  auto offset = newOrigin - playerSprite.getOrigin();
//  playerSprite.setOrigin(newOrigin);
//  playerSprite.move(offset);

  playerSprite.setOrigin((sf::Vector2f)playerTexture.getSize() / 2.f);
}

Player::~Player()
{

}

void Player::playerInput(sf::Clock timer)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    sf::Time inputCooldown = timer.restart();
    if(inputCooldown > sf::seconds(1))
    {
      playerMovementState = playerMovement::MOVE_LEFT;
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    sf::Time inputCooldown = timer.restart();
    if(inputCooldown > sf::seconds(1))
    {
      playerMovementState = playerMovement::MOVE_RIGHT;
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    sf::Time inputCooldown = timer.restart();
    if(inputCooldown > sf::seconds(1))
    {
      playerMovementState = playerMovement::MOVE_UP;
    }
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
    sf::Time inputCooldown = timer.restart();
    if(inputCooldown > sf::seconds(1))
    {
      playerMovementState = playerMovement::MOVE_DOWN;
    }
  }
}

void Player::playerMovement()
{
  switch(playerMovementState)
  {
    case MOVE_LEFT:
      speed_x = -1.5f;
      speed_y = 0.0f;
      playerSprite.move(speed_x,speed_y);
      playerSprite.setRotation(180.0f);
      //std::cout << "Player move left" << std::endl;
      break;
    case MOVE_RIGHT:
      speed_x = 1.5f;
      speed_y = 0.0f;
      playerSprite.move(speed_x,speed_y);
      playerSprite.setRotation(0.f);
      //std::cout << "Player move right" << std::endl;
      break;
    case MOVE_UP:
      speed_x = 0.0f;
      speed_y = -1.5f;
      playerSprite.move(speed_x,speed_y);
      playerSprite.setRotation(-90.f);
      //std::cout << "Player move up" << std::endl;
      break;
    case MOVE_DOWN:
      speed_x = 0.0f;
      speed_y = 1.5f;
      playerSprite.move(speed_x,speed_y);
      playerSprite.setRotation(90.f);
      //std::cout << "Player move down" << std::endl;
      break;
    case MOVE_STATIONARY:
      speed_x = 0.0f;
      speed_y = 0.0f;
      playerSprite.move(speed_x,speed_y);
      //std::cout << "Player stationary" << std::endl;
      break;
  }
  //std::cout << std::to_string(playerSprite.getLocalBounds());
}

void Player::playerBlockUpdate()
{
  switch(playerBlockState)
  {
    case BLOCK_LEFT:
      if(playerMovementState == MOVE_LEFT)
      {
        playerMovementState = MOVE_STATIONARY;
      }
      break;
    case BLOCK_RIGHT:
      if(playerMovementState == MOVE_RIGHT)
      {
        playerMovementState = MOVE_STATIONARY;
      }
      break;
    case BLOCK_UP:
      if(playerMovementState == MOVE_UP)
      {
        playerMovementState = MOVE_STATIONARY;
      }
      break;
    case BLOCK_DOWN:
      if(playerMovementState == MOVE_DOWN)
      {
        playerMovementState = MOVE_STATIONARY;
      }
      break;
      break;
    case BLOCK_NONE:
      break;
  }
}
