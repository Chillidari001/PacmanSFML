//
// Created by awseb on 31/10/2022.
//

#include "TileHandler.h"
TileHandler::TileHandler()
{
  //if statement loads spritesheet used in tiled and checks if it loads
  if(!tileMap.loadFromFile(R"(E:\Learning Projects\PacmanSFML\Data\tileAssets\kennytileset.png)"))
  {
    std::cout << "FAILED TO LOAD TILEMAP" << std::endl;
  }
  //if statement loads tilemap generated from tiled and checks if loaded
  if(!map.load(R"(E:\Learning Projects\PacmanSFML\Data\tileAssets\kennyMap.tmx)"))
  {
    std::cout << "FAILED TO LOAD TMX MAP" << std::endl;
  }

  //this code is responsible for accessing layers in the map, single layer within layers
  //and finally all the tiles within a layer
  const auto& layers = map.getLayers();
  const auto layer = layers[0]->getLayerAs<tmx::TileLayer>(); //layer is -1 from tmx layer
  const auto& tiles = layer.getTiles();

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
    tilesSprites[idx][idy].setTexture(tileMap);
    tilesSprites[idx][idy].setPosition(idy * 20, idx * 20);

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
