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
  ghost2 = std::make_unique<GhostHandler>();

  ghost->initialiseSprite(pink_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\PinkGhost.png)");
  ghost->getSprite()->setPosition(window.getSize().x/1.7, window.getSize().y/2.5);
  ghost->getSprite()->setScale(0.025f, 0.025f);

  ghost2->initialiseSprite(blue_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\BlueGhost.png)");
  ghost2->getSprite()->setPosition(window.getSize().x/2.2, window.getSize().y/2.5);
  ghost2->getSprite()->setScale(0.025f, 0.025f);

  player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);

  if (!game_font.loadFromFile("Data/Fonts/OpenSans-Italic.ttf"))
  {
    std::cout << "Game font not loaded" << std::endl;
  }

  score_text.setFont(game_font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(0, 0);

  score_text_int.setFont(game_font);
  score_text_int.setCharacterSize(30);
  score_text_int.setFillColor(sf::Color::White);
  score_text_int.setPosition(0, 30);

  score = 0;

  return true;
}

void Game::collisionHandler()
{
  for (int a = 0; a < 23; ++a)
  {
    for (int b = 0; b < 21; ++b)
    {
//      float distance = sqrt(
//        powf(
//          tileHandler->tilesSprites[a][b].GetSprite()->getPosition().x -
//            player->playerSprite.getPosition().x,
//          2) *
//        powf(
//          tileHandler->tilesSprites[a][b].GetSprite()->getPosition().y -
//            player->playerSprite.getPosition().y,
//          2));

      if (tileHandler->tilesSprites[a][b].tileID == 394)
      {
        if (player->playerSprite.getGlobalBounds().intersects(
              tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
        {
          // std::cout << "COLLIDED WITH WALL" << "\n";
          if(player->speed_x < 0 && player->speed_y == 0)
          {
            player->playerSprite.move(2.0f, 0.0f);
          }
          if(player->speed_x > 0 && player->speed_y == 0)
          {
            player->playerSprite.move(-2.0f, 0.0f);
          }
          if(player->speed_y < 0 && player->speed_x == 0)
          {
            player->playerSprite.move(0.0f, 2.0f);
          }
          if(player->speed_y > 0 && player->speed_x == 0)
          {
            player->playerSprite.move(0.0f, -2.0f);
          }
        }
//        std::cout << player->playerBlockState;
      }

      if (tileHandler->tilesSprites[a][b].tileID == 3075)
      {
        if (player->playerSprite.getGlobalBounds().intersects(
              tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
        {
            // std::cout << "COLLIDED WITH COIN" << "\n";
            tileHandler->tilesSprites[a][b].GetSprite()->setTextureRect(
              sf::IntRect(0, 0, 0, 0));
            score = score + 10;
        }
      }
    }
  }
}

bool Game::ghostCollisionHandler()
{
  for (int a = 0; a < 23; ++a)
  {
    for (int b = 0; b < 21; ++b)
    {
      float distance = sqrt(
        powf(
          tileHandler->tilesSprites[a][b].GetSprite()->getPosition().x -
            ghost->getSprite()->getPosition().x,
          2) *
        powf(
          tileHandler->tilesSprites[a][b].GetSprite()->getPosition().y -
            ghost->getSprite()->getPosition().y,
          2));

      if (tileHandler->tilesSprites[a][b].tileID == 394)
      {
        if(distance < 150)
        {
          if (ghost->getSprite()->getGlobalBounds().intersects(
                tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
          {
            std::cout << "ghost collision";
            return ghost_collided = true;
          }
          else
          {
            return ghost_collided = false;
          }
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
      ghostCollisionHandler();
      ghost->ghostStateChange();
      ghost2->ghostStateChange();
      ghost->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 1, ghost_collided);
      ghost2->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 2, ghost_collided);
      ghost->ghostMovement();
      ghost2->ghostMovement();
      player->playerInput(inputTimer);
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
        for(int i = 0; i < 23; ++i)
        {
          for(int j = 0; j < 21; ++j)
          {
            window.draw(*tileHandler->tilesSprites[i][j].GetSprite());
          }
        }
        window.draw(player->playerSprite);
        window.draw(*ghost->getSprite());
        window.draw(*ghost2->getSprite());
        score_text.setString("SCORE: ");
        score_text_int.setString(std::to_string(score));
        window.draw(score_text);
        window.draw(score_text_int);
      break;
    case PAUSE_SCREEN:
      window.draw(player->playerSprite);
      window.draw(*ghost->getSprite());
      window.draw(*ghost2->getSprite());
      //range based for loop
      for(int i = 0; i < 23; ++i)
      {
        for(int j = 0; j < 21; ++j)
        {
          window.draw(*tileHandler->tilesSprites[i][j].GetSprite());
        }
      }
      window.draw(score_text);
      window.draw(score_text_int);
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