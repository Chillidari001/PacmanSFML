//
// Created by awseb on 31/10/2022.
//

#include "TileHandler.h"
TileHandler::TileHandler(sf::RenderWindow& window) : window(window)
{
  //if statement loads spritesheet used in tiled and checks if it loads
  if(!tileMap.loadFromFile(R"(E:\Learning Projects\PacmanSFML\Data\tileAssets\kennytileset.png)"))
  {
    std::cout << "FAILED TO LOAD TILEMAP" << std::endl;
  }
  //if statement loads tilemap generated from tiled and checks if loaded
  if(!map.load(R"(E:\Learning Projects\PacmanSFML\Data\tileAssets\kennyMap2.tmx)"))
  {
    std::cout << "FAILED TO LOAD TMX MAP" << std::endl;
  }

  player = std::make_unique<Player>();

  //this code is responsible for accessing layers in the map, single layer within layers
  //and finally all the tiles within a layer
  const auto& layers = map.getLayers();
  const auto layer = layers[0]->getLayerAs<tmx::TileLayer>(); //layer is -1 from tmx layer
  const auto collisionLayer = layers[1]->getLayerAs<tmx::ObjectGroup>(); //layer is -1 from tmx layer
  const auto& tiles = layer.getTiles();

  std::vector<sf::FloatRect> bounds;
  const auto& objects = collisionLayer.getObjects();
  for (const auto& object : objects)
  {
    tmx::FloatRect rect = object.getAABB();
    bounds.push_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
  }

//  std::vector<sf::FloatRect> bounds;
//  for(const auto& layer : layers)
//  {
//    if(layer->getType() == tmx::Layer::Type::Object)
//    {
//      const auto& objects = collisionLayer.getLayerAs<tmx::ObjectGroup>().getObjects();
//      std::cout << " OBJECT WORKED" << std::endl;
//      for (const auto& object : objects)
//      {
//        tmx::FloatRect rect = object.getAABB();
//        bounds.push_back(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
//      }
//    }
//    else
//    {
//      std::cout << "BORKED" << std::endl;
//    }
//  }

//  const auto& collisionLayer = *dynamic_cast<const tmx::TileLayer*>(layers[0].get());
//  std::vector<tmx::TileLayer::Tile> cTiles = collisionLayer.getTiles();
//
//  for (tmx::TileLayer::Tile tile : cTiles)
//  {
//    //std::cout << tile.ID << std::endl;
//
//  }

  //this for loop iterates through the vector storing all tiles
  //and assigns a position based on their index. since all sprites
  //are using the same texture sheet it also adjusted which part of
  //the spritesheet is rendered based on the tiles ID
  int idx;
  int idy;

  for (int j = 0; j < tiles.size(); ++j)
  {
    idx = j / 21;
    idy = j % 21;
    //std::cout << window.getSize().x << std::endl;
    float x = 1 + (20.0f/(window.getSize().x / 70.0f));
    float y = 1 + (20.0f/(window.getSize().y / 34.0f));

    tilesSprites[idx][idy].setScale(x, y);

    tilesSprites[idx][idy].setTexture(tileMap);
    tilesSprites[idx][idy].setPosition(idy * 16 * tilesSprites[idx][idy].getScale().x + 140, idx * 16 * tilesSprites[idx][idy].getScale().y);

    switch(tiles[j].ID)
    {
      case 394:
      {
        tilesSprites[idx][idy].setTextureRect(sf::IntRect(160, 60, 20, 20));
        break;
      }

      case 663:
      {
        tilesSprites[idx][idy].setTextureRect(sf::IntRect(440, 100, 20, 20));
        break;
      }

      default:
      {
        tilesSprites[idx][idy].setTextureRect(sf::IntRect(0, 0, 20, 20));
        break;
      }
    }
  }
}

TileHandler::~TileHandler()
{

}
