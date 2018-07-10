#ifndef GOLGE_MATERIAL_H
#define GOLGE_MATERIAL_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <golge/core/shader.h>
#include <golge/core/texture.h>
using glm::mat4;
using glm::vec3;

namespace golge
{

struct Light
{
	using SharedPtr = std::shared_ptr<golge::Light>;

	Light(const vec3 &position = vec3(0), const vec3 &color = vec3(0), float range = 10.0f, float cutOff = 0.0f)
	{
		this->position = position;
		this->color = color;
		this->range = range;
		this->cutOff = cutOff;
	}

	vec3 position;
	vec3 color;
	float range;
	float cutOff;
};

class Material
{
public:
	using SharedPtr = std::shared_ptr<Material>;

	static SharedPtr create(Shader::SharedPtr const &shader, Texture::SharedPtr const &diffuse);

	Material(Shader::SharedPtr const &shader, Texture::SharedPtr const &diffuse);

	void model(mat4 modelMatrix);
	void use(Camera::SharedPtr camera) const;
	void updateTileNumber(float tileNumber) const;
	void updateOrder(float order) const;

	Shader::SharedPtr inline getShader() { return m_shader; };

private:
	Shader::SharedPtr m_shader;
	Texture::SharedPtr m_diffuse;
};
} // namespace golge

#endif
