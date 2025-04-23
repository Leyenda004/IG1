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

void IndexMesh::buildNormalVectors()
{
	//METODO DE NEWELL TEMA 9 MALLAS INDEXADAS
	//Recorremos n->indices a partir de triangulos
	//Extraer los índices del triángulo a, b, c.
	//Calcular el vector n normal al triángulo tal como se ha explicado.
	//Sumar n al vector normal de cadavértice del triángulo.

	// Inicializar normales a cero
	vNormals.clear();
	vNormals.resize(mNumVertices, vec3(0.0f));

	// Recorrer triángulos y acumular normales por vértice
	for (size_t i = 0; i < vIndexes.size() - 1; i += 3) {

		//Necesitamos 3 indices para formar un triangulo
		GLuint i0 = vIndexes[i];
		GLuint i1 = vIndexes[i + 1];
		GLuint i2 = vIndexes[i + 2];

		//Necesitamos 3 vertices de los indices del triangulo
		const vec3& v0 = vVertices[i0];
		const vec3& v1 = vVertices[i1];
		const vec3& v2 = vVertices[i2];

		//!!!!!!!!! REVISAR
		//Calculamos la normal del triangulo a partir de los vertices
		vec3 normal = normalize(cross(v1 - v0, v2 - v0)); //Signo menos por sentido antihorario y revolución antihoraria
		//Normalize seria positivo respecto a las diapositivas

		//Sumamos n al vector normal en cada vertice del triangulo
		vNormals[i0] += normal;
		vNormals[i1] += normal;
		vNormals[i2] += normal;
	}

	// Normalizamos todas las normales acumuladas
	for (auto& n : vNormals) {
		n = normalize(n);
	}
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{

	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);


	GLdouble theta = 2 * numbers::pi / nSamples;

	for (int i = 0; i <= nSamples; ++i) {
 		GLdouble c = cos(i * theta), s = sin(i * theta);
		for (auto p : profile) mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s); // El signo delante de p.x * s es la dirección en la que se gira
	}

	for (int i = 0; i < nSamples; ++i) {
 		// caras i a i + 1 
 		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara 

			// Tri�ngulo inferior (si no es degenerado) 
			if (profile[j].x != 0.0)
				for (auto [s, t] : { pair{i, j},  {i, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);

			// Tri�ngulo superior
			if (profile[j + 1].x != 0.0)
				for (auto [s, t] : { pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}

	mesh->mNumVertices = mesh->vVertices.size();

	//normales
	mesh->buildNormalVectors();
	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mPrimitive = GL_TRIANGLES;
	
	mesh->vVertices.reserve(8);
	
	//Sentido antihorario
	mesh->vVertices.push_back({-l/2,-l/2,-l/2}); // 0 ---
	mesh->vVertices.push_back({-l/2,+l/2,-l/2}); // 1 -+-
	mesh->vVertices.push_back({-l/2,-l/2,+l/2}); // 2 --+
	mesh->vVertices.push_back({-l/2,+l/2,+l/2}); // 3 -++
	mesh->vVertices.push_back({+l/2,-l/2,+l/2}); // 4 +-+
	mesh->vVertices.push_back({+l/2,+l/2,+l/2}); // 5 +++
	mesh->vVertices.push_back({+l/2,-l/2,-l/2}); // 6 +--
	mesh->vVertices.push_back({+l/2,+l/2,-l/2}); // 7 ++-
	
	mesh->vIndexes.reserve(36);
	
	// CARA +X
	mesh->vIndexes.push_back(6);
	mesh->vIndexes.push_back(7);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(6);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(4);

	// CARA -Z
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(1);
	mesh->vIndexes.push_back(7);
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(7);
	mesh->vIndexes.push_back(6);

	// CARA -Y
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(6);
	mesh->vIndexes.push_back(4);
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(4);
	mesh->vIndexes.push_back(2);

	// CARA -X
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(2);
	mesh->vIndexes.push_back(3);
	mesh->vIndexes.push_back(0);
	mesh->vIndexes.push_back(3);
	mesh->vIndexes.push_back(1);

	// CARA +Z
	mesh->vIndexes.push_back(2);
	mesh->vIndexes.push_back(4);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(2);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(3);

	// CARA +Y
	mesh->vIndexes.push_back(1);
	mesh->vIndexes.push_back(3);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(1);
	mesh->vIndexes.push_back(5);
	mesh->vIndexes.push_back(7);

	mesh->mNumVertices = mesh->vVertices.size();
	mesh->buildNormalVectors();
	return mesh;
}
