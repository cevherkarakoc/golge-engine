#ifndef GOLGE_TEXTURE_H
#define GOLGE_TEXTURE_H

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

namespace golge
{
class Texture
{
public:
  using SharedPtr = std::shared_ptr<Texture>;

  static SharedPtr create(const std::string &fileName, float columnCount = 1.0f);

  Texture(const std::string &fileName, float columnCount = 1.0f);
  void bind(GLuint unit) const;
  int inline getWidth() { return m_width; };
  int inline getHeight() { return m_height; };
  float inline getColumnCount() { return m_columnCount; };

  virtual ~Texture();

private:
  void loadTexture(const std::string &fileName, GLenum sub_target);

  GLuint m_texture;
  GLenum m_target;

  int m_width;
  int m_height;
  float m_columnCount;
};
}
#endif
