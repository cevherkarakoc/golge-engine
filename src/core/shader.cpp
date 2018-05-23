#include <golge/core/shader.h>

#include <iostream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

using namespace golge;

Shader::SharedPtr Shader::create(const std::string& fileName) {
  Shader::SharedPtr shader(new Shader(fileName));
  return shader;
}

Shader::Shader(const std::string& fileName) {
  m_program = glCreateProgram();
  m_vertexShader   = createShader(loadShader(fileName + ".vert") , GL_VERTEX_SHADER);
  m_fragmentShader = createShader(loadShader(fileName + ".frag") , GL_FRAGMENT_SHADER);

  glAttachShader(m_program, m_vertexShader);
  glAttachShader(m_program, m_fragmentShader);

  glLinkProgram(m_program);

  checkProgramError(m_program, GL_LINK_STATUS, "Error linking shader program");

	glValidateProgram(m_program);
	checkProgramError(m_program, GL_LINK_STATUS, "Invalid shader program");

  m_modelLoc = glGetUniformLocation(m_program, "modelMatrix");
  m_viewLoc = glGetUniformLocation(m_program, "viewMatrix");
  m_projectionLoc = glGetUniformLocation(m_program, "projectionMatrix");
  m_viewPositionLoc = glGetUniformLocation(m_program, "viewPosition");
  m_normalLoc = glGetUniformLocation(m_program, "normalMatrix");
  m_columnCountLoc = glGetUniformLocation(m_program, "columnCount");
  m_tileNumberLoc = glGetUniformLocation(m_program, "tileNumber");
}

Shader::~Shader() {
  glDetachShader(m_program, m_vertexShader);
  glDeleteShader(m_vertexShader);

  glDetachShader(m_program, m_fragmentShader);
  glDeleteShader(m_fragmentShader);
 
	glDeleteProgram(m_program);
}

void Shader::use() const{
  glUseProgram(m_program);
}

void Shader::updateModel(const glm::mat4 model) const{
  glm::mat3 normalMatrix(glm::transpose(glm::inverse(model)));
  glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix3fv(m_normalLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void Shader::updateCamera(Camera::SharedPtr camera) const {
  glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(camera->getView()));
  glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));
  glUniform3fv(m_viewPositionLoc, 1, glm::value_ptr(camera->getPosition()));
}

void Shader::updateColumnCount(float columnCount) const {
  glUniform1f(m_columnCountLoc, columnCount);
}

void Shader::updateTileNumber(float tileNumber) const {
  glUniform1f(m_tileNumberLoc, tileNumber);
}

void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(m_program, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f( glGetUniformLocation( m_program, name.c_str() ), x, y, z);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const {
	glUniform3fv( glGetUniformLocation( m_program, name.c_str() ), 1, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
	glUniform4f( glGetUniformLocation( m_program, name.c_str() ), x, y, z, w);
}

void Shader::setVec4(const std::string &name, glm::vec4 value) const {
	glUniform4fv( glGetUniformLocation( m_program, name.c_str() ), 1, glm::value_ptr(value));
}

GLuint Shader::createShader(const std::string& text, unsigned int type) {
  GLuint shader = glCreateShader(type);

  if(shader == 0) std::cerr << "Error !!invalid shader type!! - " << type << std::endl;

  const GLchar* c_str = text.c_str();

  glShaderSource(shader, 1, &c_str , NULL);
  glCompileShader(shader);

  checkShaderError(shader, GL_COMPILE_STATUS, "Error compiling shader!");

  return shader;
}

std::string Shader::loadShader(const std::string& fileName) {
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, const std::string& errorMessage) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  glGetShaderiv(shader, flag, &success);

  if(success == GL_FALSE) {
     glGetShaderInfoLog(shader, sizeof(error), NULL, error);
     std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}

void Shader::checkProgramError(GLuint program, GLuint flag, const std::string& errorMessage) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  glGetProgramiv(program, flag, &success);

  if(success == GL_FALSE) {
     glGetProgramInfoLog(program, sizeof(error), NULL, error);
     std::cerr << errorMessage << ": '" << error << "'" << std::endl;
  }
}
