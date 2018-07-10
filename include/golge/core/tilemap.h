#ifndef GOLGE_TILEMAP_H
#define GOLGE_TILEMAP_H

#include <memory>
#include <string>
#include <vector>

namespace golge
{

class Tilemap
{
public:
  using SharedPtr = std::shared_ptr<Tilemap>;

  static SharedPtr create(const std::string &fileName);

  Tilemap(const std::string &fileName);
  int getTileNumber(int layer, int index, int &materialIndex) const;
  int inline getWidth() const { return m_width; };
  int inline getHeight() const { return m_height; };
  int inline getLayerCount() const { return m_layers.size(); };

private:
  int m_width;
  int m_height;
  std::vector<std::vector<int>> m_layers;
  std::vector<int> m_firstIds;
};

} // namespace golge

#endif