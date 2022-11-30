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

//  int MAP_COLUMNS = map.getTileCount().x;
//  int MAP_ROWS = map.getTileCount().y;
//  auto& tile_size = map.getTileSize();
//  TILE_MAP.reserve(map.getLayers().size());
//  float x = 1 + (20.0f/(window.getSize().x / 70.0f));
//  float y = 1 + (20.0f/(window.getSize().y / 34.0f));
//  for(const auto& layer:map.getLayers())
//  {
//    TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
//    const auto& tiles = layer->getLayerAs<tmx::TileLayer>().getTiles();
//    TILE_MAP.back().reserve(tiles.size());
//    for(const auto& tile:tiles)
//    {
//      auto& current = *TILE_MAP.back().emplace_back(
//        std::make_unique<Tile>(tile.ID, *tileMap));
//
//      //current.GetSprite()->setScale(x, y);
//
//      if(current.GetID() == 0)
//      {
//        current.GetSprite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
//      }
//      else
//      {
//        current.GetSprite()->setTextureRect(sf::IntRect(current.GetID()- 160, 60, 20, 20));
//      }
//      switch(current.GetID())
//      {
//        case 394:
//        {
//          current.GetSprite()->setTextureRect(
//            sf::IntRect(160, 60, 20, 20));
//          break;
//        }
//        case 663:
//        {
//          current.GetSprite()->setTextureRect(sf::IntRect(440, 100, 20, 20));
//          break;
//        }
//        default:
//        {
//          current.GetSprite()->setTextureRect(
//  sf::IntRect(0, 0, 120, 0));
//          break;
//        }
//      }
//
//      current.GetSprite()->setPosition((TILE_MAP.back().size() % MAP_COLUMNS) * tile_size.x,
//                                       (TILE_MAP.back().size() / MAP_COLUMNS) * tile_size.x);
//    }
//  }

//  this code is responsible for accessing layers in the map, single layer within layers
//  and finally all the tiles within a layer
  const auto& layers = map.getLayers();
  const auto layer = layers[0]->getLayerAs<tmx::TileLayer>(); //layer is -1 from tmx layer
  const auto& tiles = layer.getTiles();

  //this for loop iterates through the vector storing all tiles
  //and assigns a position based on their index. since all sprites
  //are using the same texture sheet it also adjusted which part of
  //the spritesheet is rendered based on the tiles ID
  int idx;
  int idy;
  TILE_MAP.reserve(map.getLayers().size());

  for (int j = 0; j < tiles.size(); ++j)
  {
    //TILE_MAP.emplace_back(std::vector<std::unique_ptr<Tile>>());
    idx = j / 21;
    idy = j % 21;
    //std::cout << window.getSize().x << std::endl;
    float x = 1 + (20.0f/(window.getSize().x / 70.0f));
    float y = 1 + (20.0f/(window.getSize().y / 34.0f));

    tilesSprites[idx][idy].tileID = tiles[j].ID;

    tilesSprites[idx][idy].GetSprite()->setScale(x, y);
    tilesSprites[idx][idy].GetSprite()->setTexture(tileMap);
    tilesSprites[idx][idy].GetSprite()->setPosition(idy * 16 * tilesSprites[idx][idy].GetSprite()->getScale().x + 140, idx * 16 * tilesSprites[idx][idy].GetSprite()->getScale().y);

    //TILE_MAP.back().reserve(tiles.size());

    switch(tiles[j].ID)
    {
      case 394:
      {
        tilesSprites[idx][idy].GetSprite()->setTextureRect(sf::IntRect(160, 60, 20, 20));
        break;
      }

      case 663:
      {
        tilesSprites[idx][idy].GetSprite()->setTextureRect(sf::IntRect(440, 100, 20, 20));
        break;
      }

      case 3075:
      {
        tilesSprites[idx][idy].GetSprite()->setTextureRect(sf::IntRect(20*2, 20*24, 20, 20));
        tilesSprites[idx][idy].GetSprite()->setScale(0.5f, 0.5f);
        tilesSprites[idx][idy].GetSprite()->move(20, 14);
        break;
      }

      default:
      {
        tilesSprites[idx][idy].GetSprite()->setTextureRect(sf::IntRect(0, 0, 0, 0));
        break;
      }
    }
}
}

TileHandler::~TileHandler()
{

}
