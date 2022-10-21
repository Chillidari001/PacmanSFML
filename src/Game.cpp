
#include "Game.h"
#include <iostream>
#include "Map.cpp"

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
  //std::unique_ptr<Menu> menu(new Menu(window.getSize().x, window.getSize().y));  smart pointer attempt

  return true;
}

void Game::tileHandler()
{
  //if statement loads spritesheet used in tiled and checks if it loads
  sf::Texture tileMap;
  if(!tileMap.loadFromFile("Data/tileAssets/tilemap.png"))
  {
    std::cout << "FAILED TO LOAD TILEMAP" << std::endl;
  }
  //if statement loads tilemap generated from tiled and checks if loaded
  sf::Texture map;
  if(!map.loadFromFile("Data/tileAssets/test_map.tmx"))
  {
    std::cout << "FAILED TO LOAD TMX MAP" << std::endl;
  }

}

void Game::update(float dt)
{

}

void Game::render()
{
  if (game_state == gameScreen::MENU_SCREEN)
  {
    //std::unique_ptr<Menu> menu(new Menu(window.getSize().x, window.getSize().y));  smart pointer attempt
    window.draw(menu->play_text);
    window.draw(menu->menu_text);
    window.draw(menu->options_text);
    window.draw(menu->exit_text);
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
  }
}


