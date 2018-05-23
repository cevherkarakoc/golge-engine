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
    m_layers.push_back( layer["data"] );
  }

  for(auto const& tileset: mapJson["tilesets"]) {
    m_firstIds.push_back( tileset["firstgid"] );
  }
}

int Tilemap::getTileNumber(int index, int &materialIndex) const {
  int i = 0, baseValue = 0;
  for(auto const& firstId: m_firstIds) {
    baseValue = firstId;
    if(index >= firstId) break;
    i++;
  }
  materialIndex = i;

  return (m_layers[0][index] - baseValue);
}