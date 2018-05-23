#ifndef GOLGE_MESH_H
#define GOLGE_MESH_H

#include <memory>
#include <vector>

#include <glm/glm.hpp>

namespace golge
{

struct Vertex
{
	Vertex(const glm::vec3 &position = glm::vec3(0),
				 const glm::vec2 &textureCoord = glm::vec2(0))
	{
		this->position = position;
		this->textureCoord = textureCoord;
	}
	glm::vec3 position;
	glm::vec2 textureCoord;
};

class Mesh
{
public:
	using UniquePtr = std::unique_ptr<Mesh>;
	using SharedPtr = std::shared_ptr<Mesh>;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void draw() const;

	virtual ~Mesh();

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_numIndices;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void initMesh();
};
}

#endif
