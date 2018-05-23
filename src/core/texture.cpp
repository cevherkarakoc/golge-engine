#include <golge/core/texture.h>

#include <iostream>

#include <stb_image.h>

using namespace golge;

Texture::SharedPtr Texture::create(const std::string &fileName, float columnCount)
{
  SharedPtr texture(new Texture(fileName, columnCount));
  return texture;
}

Texture::Texture(const std::string &fileName, float columnCount)
{
  m_target = GL_TEXTURE_2D;
  m_columnCount = columnCount;

  glGenTextures(1, &m_texture);
  glBindTexture(m_target, m_texture);

  loadTexture(fileName, m_target);
  glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

  glTexParameterf(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameterf(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_texture);
}

void Texture::bind(GLuint unit) const
{
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(m_target, m_texture);
}

void Texture::loadTexture(const std::string &fileName, GLenum sub_target)
{
  int numComponents;
  unsigned char *data = stbi_load((fileName).c_str(), &m_width, &m_height, &numComponents, 4);

  if (data == NULL)
    std::cerr << "Unable to load texture: " << fileName << std::endl;
  else
  {
    glTexImage2D(sub_target, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }
}