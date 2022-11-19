#include "Game.h"

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  //resources = std::make_unique<ResourceHandler>("Data");
}

Game::~Game()
{

}

bool Game::init()
{
  menu = std::make_unique<Menu>(window.getSize().x, window.getSize().y);
  player = std::make_unique<Player>();
  tileHandler = std::make_unique<TileHandler>(window);
  ghost = std::make_unique<GhostHandler>();

  ghost->ghostSprite.setPosition(window.getSize().x/2.5, window.getSize().y/2.5);
  player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
  return true;
}

void Game::collisionHandler()
{
  for (const auto& tile:tileHandler->TILE_MAP[0])
  {
    float distance = sqrt(powf(tile->GetSprite()->getPosition().x - player->playerSprite.getPosition().x, 2)
                            * powf(tile->GetSprite()->getPosition().y - player->playerSprite.getPosition().y, 2));

    if(distance < 300)
    {
      if(player->playerSprite.getGlobalBounds().intersects(tile->GetSprite()->getGlobalBounds()))
      {
        if(tile->GetID() != (3075))
        {
          player->playerMovementState = Player::playerMovement::MOVE_STATIONARY;
          std::cout << "COLLIDED WITH A WALL" << std::endl;
        }
      }
    }
  }
}

void Game::update(float dt)
{
  switch(game_state)
  {
    case GAME_SCREEN:
      collisionHandler();
      ghost->ghostMovement();
      player->playerInput();
      player->playerMovement();
      break;
    case PAUSE_SCREEN:
      break;
    case WIN_SCREEN:
      break;
    case LOSE_SCREEN:
      break;
  }
}

void Game::render()
{
  switch (game_state)
  {
    case MENU_SCREEN:
      window.draw(menu->play_text);
      window.draw(menu->menu_text);
      window.draw(menu->exit_text);
      break;
    case GAME_SCREEN:
      window.draw(player->playerSprite);
      window.draw(ghost->ghostSprite);
      //range based for loop
      for(const auto& layer:tileHandler->TILE_MAP)
      {
        for(const auto& tile : layer)
        {
          if(tile->GetID() != 0)
          {
            window.draw(*tile->GetSprite());
          }
        }
      }
      break;
    case PAUSE_SCREEN:
      window.draw(player->playerSprite);
      window.draw(ghost->ghostSprite);
      //range based for loop
      for(const auto& layer:tileHandler->TILE_MAP)
      {
        for(const auto& tile : layer)
        {
          if(tile->GetID() != 0)
          {
            window.draw(*tile->GetSprite());
          }
        }
      }
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  if(game_state == gameScreen::MENU_SCREEN)
  {
    if (menu_selected == 1 && event.key.code == sf::Keyboard::Right)
    {
      menu_selected = 2;
      std::cout << menu_selected;
      menu->inputSwitch(menu_selected);
    }
    if (menu_selected == 2 && event.key.code == sf::Keyboard::Left)
    {
      menu_selected = 1;
      std::cout << menu_selected;
      menu->inputSwitch(menu_selected);
    }

    if(event.key.code == sf::Keyboard::Enter)
    {
      if(menu_selected == 1)
      {
        init();
        game_state = gameScreen::GAME_SCREEN;
      }
      if(menu_selected == 2)
      {
        window.close();
      }
    }
    if(event.key.code == sf::Keyboard::Escape)
    {
      window.close();
    }
  }

  if(game_state == gameScreen::GAME_SCREEN)
  {
    if(event.key.code == sf::Keyboard::Escape)
    {
      game_state = gameScreen::MENU_SCREEN;
    }

    player->playerInput();
  }
  if(game_state == gameScreen::GAME_SCREEN || game_state == gameScreen::PAUSE_SCREEN)
  {
    if(event.key.code == sf::Keyboard::P)
    {
      paused = !paused;
      if(paused)
      {
        game_state = gameScreen::PAUSE_SCREEN;
      }
      if(!paused)
      {
        game_state = gameScreen::GAME_SCREEN;
      }
    }
  }
}