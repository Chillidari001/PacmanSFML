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
  player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);

  tileHandler = std::make_unique<TileHandler>();
  //std::unique_ptr<Menu> menu(new Menu(window.getSize().x, window.getSize().y));  smart pointer attempt

  return true;
}

void Game::collisionHandler()
{

}

void Game::update(float dt)
{
  switch(game_state)
  {
    case GAME_SCREEN:
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
      //std::unique_ptr<Menu> menu(new Menu(window.getSize().x, window.getSize().y));  smart pointer attempt
      window.draw(menu->play_text);
      window.draw(menu->menu_text);
      window.draw(menu->options_text);
      window.draw(menu->exit_text);
      break;
    case GAME_SCREEN:
      window.draw(player->playerSprite);

      //iterate through array of sprites and render them on screen

//          for(int i = 0; i < 23; ++i)
//          {
//            for(int j = 0; j < 21; ++j)
//            {
//              window.draw(tileHandler->tilesSprites[i][j]);
//            }
//          }

      //range based for loop
      for(auto & tilesSprite : tileHandler->tilesSprites)
      {
        for(const auto & j : tilesSprite)
        {
          window.draw(j);
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
    else if (menu_selected == 2 && event.key.code == sf::Keyboard::Right)
    {
      menu_selected = 3;
      std::cout << menu_selected;
      menu->inputSwitch(menu_selected);
    }
    if (menu_selected == 2 && event.key.code == sf::Keyboard::Left)
    {
      menu_selected = 1;
      std::cout << menu_selected;
      menu->inputSwitch(menu_selected);
    }
    if (menu_selected == 3 && event.key.code == sf::Keyboard::Left)
    {
      menu_selected = 2;
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
      if(menu_selected == 3)
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
}