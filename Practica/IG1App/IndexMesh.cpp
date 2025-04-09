#include "IndexMesh.h"

using namespace std;
using namespace glm;

constexpr GLuint NONE = numeric_limits<GLuint>::max();

void IndexMesh::load()
{
	Mesh::load();

	glBindVertexArray(mVAO);
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndexes.size() * sizeof(GLuint),
										  vIndexes.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void IndexMesh::unload() {
	Mesh::unload();

	if (mVAO != NONE) {
		if (mIBO != NONE) {
			glDeleteBuffers(1, &mIBO);
			//??
			mIBO = NONE;
		}
	}

}

void IndexMesh::draw() const
{
	glDrawElements(
		mPrimitive, //primitiva elegida, TRIANGLES, etc
		vIndexes.size(), //num indices
		GL_UNSIGNED_INT, //tipo de indices
		nullptr //offset en VBO de indices
	);
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->mNumVertices = (nSamples + 1) * tamPerfil;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble theta1 = 2 * numbers::pi / nSamples;

	for (int i = 0; i <= nSamples; ++i) {
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		for (auto p : profile) mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}

	return mesh;
}
