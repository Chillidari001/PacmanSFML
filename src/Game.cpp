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

  ghost->ghostSprite.setPosition(window.getSize().x/2.3, window.getSize().y/2.5);
  player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
  return true;
}

void Game::collisionHandler()
{
//  for (const auto& tile:tileHandler->TILE_MAP[0])
//  {
//    float distance = sqrt(powf(tile->GetSprite()->getPosition().x - player->playerSprite.getPosition().x, 2)
//                            * powf(tile->GetSprite()->getPosition().y - player->playerSprite.getPosition().y, 2));
//
//    if(distance < 300)
//    {
//      if(player->playerSprite.getGlobalBounds().intersects(tile->GetSprite()->getGlobalBounds()))
//      {
//        if(tile->GetID() != (3075))
//        {
//          player->playerMovementState = Player::playerMovement::MOVE_STATIONARY;
//          std::cout << "COLLIDED WITH A WALL" << std::endl;
//        }
//      }
//    }
//  }

  for(int a = 0; a < 23; ++a)
  {
    for(int b = 0; b < 21; ++b)
    {
      //std::cout << tileHandler->tilesSprites[a][b].GetID() << "\n";
      float distance = sqrt(powf(tileHandler->tilesSprites[a][b].GetSprite()->getPosition().x - player->playerSprite.getPosition().x, 2)
                            * powf(tileHandler->tilesSprites[a][b].GetSprite()->getPosition().y - player->playerSprite.getPosition().y, 2));
//      if(distance < 150)
//      {
        if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
        {
          if(tileHandler->tilesSprites[a][b].tileID == 394)
          {
            if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
            {
//              if(player->playerMovementState == Player::MOVE_LEFT)
//              {
//                player->playerBlockState = Player::BLOCK_LEFT;
//              }
              //std::cout << "COLLIDED WITH A WALL" << "\n";
            }
//            else
//            {
//              player->playerBlockState = Player::BLOCK_NONE;
//            }
          }
        }
//        if(tileHandler->tilesSprites[a][b].tileID == 3075)
//        {
//          if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
//          {
//            //std::cout << "COLLIDED WITH COIN" << "\n";
//            tileHandler->tilesSprites[a][b].GetSprite()->setTextureRect(sf::IntRect(0,0,0,0));
//          }
//        }
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
      player->playerBlockUpdate();
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
      //range based for loop
//      for(const auto& layer:tileHandler->TILE_MAP)
//      {
//        for(const auto& tile : layer)
//        {
//          if(tile->GetID() != 0)
//          {
//            window.draw(*tile->GetSprite());
//          }
//        }
//      }
//      for(auto & tilesSprite : tileHandler->tilesSprites)
//      {
//        for(const auto & j : tilesSprite)
//        {
//          window.draw(tileHandler->tilesSprites.Get);
//        }
//      }
        for(int i = 0; i < 23; ++i)
        {
          for(int j = 0; j < 21; ++j)
          {
            window.draw(*tileHandler->tilesSprites[i][j].GetSprite());
          }
        }

        window.draw(player->playerSprite);
        window.draw(ghost->ghostSprite);

      break;
    case PAUSE_SCREEN:
      window.draw(player->playerSprite);
      window.draw(ghost->ghostSprite);
      //range based for loop
      for(int i = 0; i < 23; ++i)
      {
        for(int j = 0; j < 21; ++j)
        {
          window.draw(*tileHandler->tilesSprites[i][j].GetSprite());
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