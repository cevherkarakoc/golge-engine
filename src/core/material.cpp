#include <golge/core/material.h>

#include <string>

using namespace golge;

Material::SharedPtr Material::create(Shader::SharedPtr const &shader, Texture::SharedPtr const &diffuse)
{
	SharedPtr material(new Material(shader, diffuse));
	return material;
}

Material::Material(Shader::SharedPtr const &shader, Texture::SharedPtr const &diffuse)
{
	m_shader = shader;
	m_diffuse = diffuse;

	m_shader->use();
	m_shader->setInt("material.diffuse", 0);
}

void Material::model(mat4 modelMatrix)
{
	m_shader->updateModel(modelMatrix);
}

void Material::use(Camera::SharedPtr camera) const
{
	m_shader->use();
	m_shader->updateCamera(camera);
	m_shader->updateColumnCount(m_diffuse->getColumnCount());
	m_diffuse->bind(0);
}

void Material::updateTileNumber(float tileNumber) const
{
	m_shader->updateTileNumber(tileNumber);
}

void Material::updateOrder(float order) const
{
	m_shader->updateOrder(order);
}
