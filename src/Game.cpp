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

  if (!game_font.loadFromFile("Data/Fonts/OpenSans-Italic.ttf"))
  {
    std::cout << "Game font not loaded" << std::endl;
  }

  score_text.setFont(game_font);
  score_text.setCharacterSize(30);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(0 + score_text.getGlobalBounds().width/2, 0 + score_text.getGlobalBounds().height*6);

  return true;
}

void Game::collisionHandler()
{
  for (int a = 0; a < 23; ++a)
  {
    for (int b = 0; b < 21; ++b)
    {
      float distance = sqrt(powf(tileHandler->tilesSprites[a][b].GetSprite()->getPosition().x - player->playerSprite.getPosition().x, 2)
                            * powf(tileHandler->tilesSprites[a][b].GetSprite()->getPosition().y - player->playerSprite.getPosition().y, 2));

      if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
      {
        if(tileHandler->tilesSprites[a][b].tileID == 394)
        {
          //std::cout << "COLLIDED WITH WALL" << "\n";
          if(player->playerMovementState == Player::MOVE_LEFT)
          {
            player->playerBlockState = Player::BLOCK_LEFT;
//            player->playerSprite.setPosition(tileHandler->tilesSprites[a][b].GetSprite()->getPosition().x + tileHandler->tilesSprites[a][b].GetSprite()->getTexture()->getSize().x,
//                                             tileHandler->tilesSprites[a][b].GetSprite()->getPosition().y + tileHandler->tilesSprites[a][b].GetSprite()->getTexture()->getSize().y);
          }
          if(player->playerMovementState == Player::MOVE_RIGHT)
          {

          }
          if(player->playerMovementState == Player::MOVE_UP)
          {

          }
          if(player->playerMovementState == Player::MOVE_DOWN)
          {

          }
        }

        if(tileHandler->tilesSprites[a][b].tileID == 3075)
        {
          if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()))
          {
            //std::cout << "COLLIDED WITH COIN" << "\n";
            tileHandler->tilesSprites[a][b].GetSprite()->setTextureRect(sf::IntRect(0,0,0,0));
            score++;
          }
        }
      }
      if(player->playerSprite.getGlobalBounds().intersects(tileHandler->tilesSprites[a][b].GetSprite()->getGlobalBounds()) == false && player->playerBlockState != Player::BLOCK_NONE)
      {
        std::cout << "NOT COLLIDING" << "\n";
        player->playerBlockState = Player::BLOCK_NONE;
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
      player->playerBlockUpdate();
      player->playerMovement();
      std::cout << player->playerBlockState;
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
        window.draw(ghost->ghostSprite);
        score_text.setString("SCORE: " + std::to_string(score));
        window.draw(score_text);
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