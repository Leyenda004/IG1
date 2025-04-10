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
	//int tamPerfil = profile.size();
	//mesh->mNumVertices = (nSamples + 1) * tamPerfil;
	mesh->mNumVertices = mesh->vVertices.size();
	mesh->vVertices.reserve(mesh->mNumVertices);

	vector<vector<vec3>> vs(nSamples + 1);
	GLdouble theta1 = 2 * numbers::pi / nSamples;

	for (int i = 0; i <= nSamples; ++i) {
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		vs[i].reserve(profile.size());
		for (glm::vec2 p : profile) vs[i].emplace_back(p.x * c, p.y, p.x * s);
	}

	for (int i = 0; i < nSamples; ++i) {
		// caras i a i + 1 
		for (int j = 0; j < profile.size() - 1; ++j) { // una cara 
			// Triángulo inferior (si no es degenerado) 
			if (profile[j].x != 0.0) {
				mesh->vVertices.push_back(vs[i][j]);
				mesh->vVertices.push_back(vs[i + 1][j]);
				mesh->vVertices.push_back(vs[i][j + 1]);
			}
			if (profile[j + 1].x != 0.0) {
				for (auto [s, t] : { pair{i,j + 1},{i + 1,j},{i + 1,j + 1} }) {
					mesh->vVertices.push_back(vs[s][t]);
				}
			}
		}
	}


	return mesh;
}
