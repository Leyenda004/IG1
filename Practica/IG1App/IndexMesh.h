#pragma once
#include "Mesh.h"
#include <vector>
#include <numbers>
class IndexMesh : public Mesh {
private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;
	void load() override;
	void unload() override;
	void draw() const override;
public:
	static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples,
		GLfloat angleMax = 2 * std::numbers::pi);
	static IndexMesh* generateIndexedBox(GLdouble l);
};