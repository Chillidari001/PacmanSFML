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

//void Game::tileHandler()
//{
//  //if statement loads spritesheet used in tiled and checks if it loads
//  if(!tileMap.loadFromFile("E:\\Learning Projects\\PacmanSFML\\Data\\tileAssets\\kennytileset.png"))
//  {
//    std::cout << "FAILED TO LOAD TILEMAP" << std::endl;
//  }
//  //if statement loads tilemap generated from tiled and checks if loaded
//  if(!map.load("E:\\Learning Projects\\PacmanSFML\\Data\\tileAssets\\kennyMap.tmx"))
//  {
//    std::cout << "FAILED TO LOAD TMX MAP" << std::endl;
//  }
//
//  //this code is responsible for accessing layers in the map, single layer within layers
//  //and finally all the tiles within a layer
//  const auto& layers = map.getLayers();
//  const auto layer = layers[0]->getLayerAs<tmx::TileLayer>(); //layer is -1 from tmx layer
//  const auto& tiles = layer.getTiles();
//
//  //this for loop iterates through the vector storing all tiles
//  //and assigns a position based on their index. since all sprites
//  //are using the same texture sheet it also adjusted which part of
//  //the spritesheet is rendered based on the tiles ID
//  int idx = 0;
//  int idy = 0;
//
//  for (int j = 0; j < tiles.size(); ++j)
//  {
//    idx = j / 21;
//    idy = j % 21;
//    tilesSprites[idx][idy].setTexture(tileMap);
//    tilesSprites[idx][idy].setPosition(idy * 20, idx * 20);
//
//    switch(tiles[j].ID)
//    {
//      case 394:
//      {
//        tilesSprites[idx][idy].setTextureRect(sf::IntRect(160, 60, 20, 20));
//        break;
//      }
//
//      case 663:
//      {
//        tilesSprites[idx][idy].setTextureRect(sf::IntRect(440, 100, 20, 20));
//        break;
//      }
//
//      default:
//      {
//        tilesSprites[idx][idy].setTextureRect(sf::IntRect(0, 0, 20, 20));
//        break;
//      }
//    }
//  }
//}

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