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
  ghost3 = std::make_unique<GhostHandler>();
  ghost4 = std::make_unique<GhostHandler>();

  //should have used array or vector to spawn multiple ghost entities, rushed implementation
  ghost->initialiseSprite(pink_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\PinkGhost.png)");
//  ghost->getSprite()->setPosition(window.getSize().x/1.7, window.getSize().y/2.5);

  ghost2->initialiseSprite(blue_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\BlueGhost.png)");

  ghost3->initialiseSprite(orange_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\OrangeGhost.png)");

  ghost4->initialiseSprite(green_ghost_texture, R"(E:\Learning Projects\PacmanSFML\Data\Images\GreenGhost.png)");

  if (!game_font.loadFromFile("Data/Fonts/OpenSans-Italic.ttf"))
  {
    std::cout << "Game font not loaded" << std::endl;
  }

  if(!fruitTexture.loadFromFile(R"(E:\Learning Projects\PacmanSFML\Data\Images\orangefruit.png)"))
  {
    std::cout << "Fruit texture not loaded" << std::endl;
  }

  fruitSprite.setTexture(fruitTexture);
  fruitSprite.setScale(0.040f, 0.040f);

  fruitSprite2.setTexture(fruitTexture);
  fruitSprite2.setScale(0.040f, 0.040f);

  score_text.setFont(game_font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(0, 0);

  score_text_int.setFont(game_font);
  score_text_int.setCharacterSize(30);
  score_text_int.setFillColor(sf::Color::White);
  score_text_int.setPosition(0, 30);

  lives_text.setFont(game_font);
  lives_text.setCharacterSize(30);
  lives_text.setFillColor(sf::Color::White);
  lives_text.setPosition(0, 70);

  lives_text_int.setFont(game_font);
  lives_text_int.setCharacterSize(30);
  lives_text_int.setFillColor(sf::Color::White);
  lives_text_int.setPosition(0, 100);

  lose_text.setFont(game_font);
  lose_text.setCharacterSize(77);
  lose_text.setFillColor(sf::Color::White);
  lose_text.setPosition(window.getSize().x / 3, window.getSize().y / 4);
  lose_text.setString("YOU LOSE");

  retry_text.setFont(game_font);
  retry_text.setCharacterSize(30);
  retry_text.setFillColor(sf::Color::White);
  retry_text.setPosition(window.getSize().x / 6 , window.getSize().y / 2);
  retry_text.setString("Press ENTER to try again or ESCAPE to return to the menu");

  win_text.setFont(game_font);
  win_text.setCharacterSize(77);
  win_text.setFillColor(sf::Color::White);
  win_text.setPosition(window.getSize().x / 3, window.getSize().y / 4);
  win_text.setString("YOU WIN");

  completion_score_text.setFont(game_font);
  completion_score_text.setCharacterSize(30);
  completion_score_text.setFillColor(sf::Color::White);
  completion_score_text.setPosition(window.getSize().x / 6 , window.getSize().y / 2);

  gameInit();

  return true;
}

bool Game::gameInit()
{
  ghost->getSprite()->setPosition(230, 673);
  ghost->getSprite()->setScale(0.025f, 0.025f);

  ghost2->getSprite()->setPosition(810, 673);
  ghost2->getSprite()->setScale(0.030f, 0.030f);

  ghost3->getSprite()->setPosition(380, 175);
  ghost3->getSprite()->setScale(0.065f, 0.065f);

  ghost4->getSprite()->setPosition(600, 175);
  ghost4->getSprite()->setScale(0.080f, 0.080f);

  player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);

  fruitSprite.setPosition(220, 660);
  fruitSprite2.setPosition(window.getSize().x / 2.05, window.getSize().y / 2.6);

  ghost->movementTime.restart();

  player->playerMovementState = Player::MOVE_STATIONARY;

  score = 0;

  pellets_collected = 0;

  lives = 3;

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
            pellets_collected++;
        }
      }
    }
  }
  //absolutely awful but the last implemented features (power ups, ghost spawns, etc. have been an absolute rush job. horrible and dirty implementation
  if(player->playerSprite.getGlobalBounds().intersects(fruitSprite.getGlobalBounds()))
  {
    fruitSprite.setTextureRect(sf::IntRect(0,0,0,0));
    powered_timer.restart();
    powered = true;
    std::cout << "Fruit 1 Eaten" << "\n";
  }
  if(player->playerSprite.getGlobalBounds().intersects(fruitSprite2.getGlobalBounds()))
  {
    fruitSprite2.setTextureRect(sf::IntRect(0,0,0,0));
    powered_timer.restart();
    powered = true;
    std::cout << "Fruit 2 Eaten" << "\n";
  }

  if(player->playerSprite.getGlobalBounds().intersects(ghost->getSprite()->getGlobalBounds()))
  {
    if(powered == false)
    {
      lives = --lives;
      player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
      player->playerMovementState = Player::MOVE_STATIONARY;
    }
    if(powered == true)
    {
      score = score + 20;
      ghost->getSprite()->setTextureRect(sf::IntRect(0,0,0,0));
    }
  }

  if(player->playerSprite.getGlobalBounds().intersects(ghost2->getSprite()->getGlobalBounds()))
  {
    if(powered == false)
    {
      lives = --lives;
      player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
      player->playerMovementState = Player::MOVE_STATIONARY;
    }
    if(powered == true)
    {
      score = score + 20;
      ghost2->getSprite()->setTextureRect(sf::IntRect(0,0,0,0));
    }
  }

  if(player->playerSprite.getGlobalBounds().intersects(ghost3->getSprite()->getGlobalBounds()))
  {
    if(powered == false)
    {
      lives = --lives;
      player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
      player->playerMovementState = Player::MOVE_STATIONARY;
    }
    if(powered == true)
    {
      score = score + 20;
      ghost3->getSprite()->setTextureRect(sf::IntRect(0,0,0,0));
    }
  }

  if(player->playerSprite.getGlobalBounds().intersects(ghost4->getSprite()->getGlobalBounds()))
  {
    if(powered == false)
    {
      lives = --lives;
      player->playerSprite.setPosition(window.getSize().x/2, window.getSize().y/2);
      player->playerMovementState = Player::MOVE_STATIONARY;
    }
    if(powered == true)
    {
      score = score + 20;
      ghost4->getSprite()->setTextureRect(sf::IntRect(0,0,0,0));
    }
  }
}

void Game::playerStateManager()
{
  if(powered)
  {
    float powered_timer_elapsed = powered_timer.getElapsedTime().asSeconds();;
    if(powered_timer_elapsed >= 5)
    {
      powered = false;
    }
    player->playerSprite.setColor(sf::Color::Red);
  }
  else
  {
    player->playerSprite.setColor(sf::Color::Yellow);
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
//            std::cout << "ghost collision";
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
  stateManager();
  switch(game_state)
  {
    case GAME_SCREEN:
      collisionHandler();
      //ghostCollisionHandler();
      ghost->ghostStateChange();
      ghost2->ghostStateChange();
      ghost3->ghostStateChange();
      ghost4->ghostStateChange();
      //player coords are actually never used, could not finish/get functional custom "pathfinding" solution.
      ghost->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 1, ghost_collided);
      ghost2->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 2, ghost_collided);
      ghost3->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 2, ghost_collided);
      ghost4->ghostStateHandler(player->playerSprite.getPosition().x, player->playerSprite.getPosition().y, 1, ghost_collided);
      ghost->ghostMovement();
      ghost2->ghostMovement();
      ghost3->ghostMovement();
      ghost4->ghostMovement();
      player->playerInput(inputTimer);
      player->playerBlockUpdate();
      player->playerMovement();
      playerStateManager();
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
        window.draw(*ghost3->getSprite());
        window.draw(*ghost4->getSprite());

        window.draw(fruitSprite);
        window.draw(fruitSprite2);

        score_text.setString("SCORE: ");
        score_text_int.setString(std::to_string(score));
        window.draw(score_text);
        window.draw(score_text_int);

        lives_text.setString("LIVES: ");
        lives_text_int.setString(std::to_string(lives));
        window.draw(lives_text);
        window.draw(lives_text_int);
      break;
    case PAUSE_SCREEN:
      window.draw(player->playerSprite);
      window.draw(*ghost->getSprite());
      window.draw(*ghost2->getSprite());
      window.draw(*ghost3->getSprite());
      window.draw(*ghost4->getSprite());
      //range based for loop
      for(int i = 0; i < 23; ++i)
      {
        for(int j = 0; j < 21; ++j)
        {
          window.draw(*tileHandler->tilesSprites[i][j].GetSprite());
        }
      }

      window.draw(fruitSprite);
      window.draw(fruitSprite2);

      window.draw(score_text);
      window.draw(score_text_int);

      window.draw(lives_text);
      window.draw(lives_text_int);
      break;
    case WIN_SCREEN:
      window.draw(win_text);
      completion_score_text.setString("Your score was " + std::to_string(score) + "! Press ESCAPE to return to the menu");
      window.draw(completion_score_text);
      break;
    case LOSE_SCREEN:
      window.draw(lose_text);
      window.draw(retry_text);
      break;
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

//  //lose condition test
//  if(game_state == gameScreen::GAME_SCREEN)
//  {
//    if (event.key.code == sf::Keyboard::K)
//    {
//      lives = 0;
//    }
//  }
//
//  //win condition test
//  if(game_state == gameScreen::GAME_SCREEN)
//  {
//    if (event.key.code == sf::Keyboard::L)
//    {
//      pellets_collected = 87;
//    }
//  }

  if(game_state == gameScreen::LOSE_SCREEN)
  {
    if(event.key.code == sf::Keyboard::Escape)
    {
      lives = 3;
      game_state = gameScreen::MENU_SCREEN;
    }
    if(event.key.code == sf::Keyboard::Enter)
    {
      init();
      game_state = gameScreen::GAME_SCREEN;
    }
  }

  if(game_state == gameScreen::WIN_SCREEN)
  {
    if(event.key.code == sf::Keyboard::Escape)
    {
      pellets_collected = 0;
      game_state = gameScreen::MENU_SCREEN;
    }
  }
}

void Game::stateManager()
{
  if (lives == 0)
  {
    game_state = gameScreen::LOSE_SCREEN;
  }

  if(pellets_collected == 87)
  {
    game_state = gameScreen::WIN_SCREEN;
  }
}
