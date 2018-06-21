#include <golge/core/tilemap.h>

#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

using namespace golge;

Tilemap::SharedPtr Tilemap::create(const std::string &fileName)
{
  SharedPtr tilemap(new Tilemap(fileName));
  return tilemap;
}

Tilemap::Tilemap(const std::string &fileName)
{
  std::ifstream mapFile(fileName);
  nlohmann::json mapJson;
  mapFile >> mapJson;

  m_width  = mapJson["width"];
  m_height = mapJson["height"];

  for(auto const& layer: mapJson["layers"]) {
    if(layer["type"] == "tilelayer")
      m_layers.push_back( layer["data"] );
  }

  for(auto const& tileset: mapJson["tilesets"]) {
    m_firstIds.push_back( tileset["firstgid"] );
  }
}

int Tilemap::getTileNumber(int layer, int index, int &materialIndex) const {
  int i = -1, baseValue = 1;
  int tileNumber = m_layers[layer][index];
  
  for(auto const& firstId: m_firstIds) {
    if(firstId > tileNumber) break;
    baseValue = firstId;
    i++;
  }
  
  materialIndex = i;  

  return (tileNumber - baseValue);
}