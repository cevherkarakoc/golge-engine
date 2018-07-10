#ifndef GOLGE_SHADER_H
#define GOLGE_SHADER_H

#include <memory>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <golge/core/camera.h>

namespace golge
{
class Shader
{
public:
  using SharedPtr = std::shared_ptr<Shader>;

  static SharedPtr create(const std::string &fileName);

  Shader(const std::string &fileName);
  void use() const;
  void updateModel(const glm::mat4 model) const;
  void updateCamera(Camera::SharedPtr camera) const;
  void updateColumnCount(float columnCount) const;
  void updateTileNumber(float tileNumber) const;
  void updateOrder(float order) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec3(const std::string &name, glm::vec3 value) const;
  void setVec4(const std::string &name, float x, float y, float z, float w) const;
  void setVec4(const std::string &name, glm::vec4 value) const;

  virtual ~Shader();

protected:
private:
  std::string loadShader(const std::string &fileName);
  void checkShaderError(GLuint shader, GLuint flag, const std::string &errorMessage);
  void checkProgramError(GLuint program, GLuint flag, const std::string &errorMessage);
  GLuint createShader(const std::string &text, unsigned int type);

  GLuint m_program;
  GLuint m_vertexShader;
  GLuint m_fragmentShader;

  GLuint m_modelLoc;
  GLuint m_viewLoc;
  GLuint m_projectionLoc;
  GLuint m_viewPositionLoc;
  GLuint m_normalLoc;
  GLuint m_columnCountLoc;
  GLuint m_tileNumberLoc;
  GLuint m_orderLoc;
};
} // namespace golge

#endif
