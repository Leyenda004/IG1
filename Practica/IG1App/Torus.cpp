#include "Torus.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std;

//r: grosor
//R: radio
//nSamples: numero de muestras
//nPoints: numero de puntos de la circunferencia
Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples)
{
	// Creamos el perfil
	Mesh* profileMesh = Mesh::generateRegularPolygon(nPoints, r / 2); //El radio es / 2 porque r es el grosor del toroide, es decir el diametro
	// Desplazamos una cantidad de R (radio del toroide)
	mat4 tras = translate(mat4(1.0f), vec3(R, 0, 0));
	setModelMat(mModelMat * tras);

	vector<vec2> profile;
	vector<vec3> vertices = profileMesh->vertices();

	for (const auto& v : vertices) {
		profile.push_back(vec2(v.x, v.y));
	}


	//mMesh = profileMesh;
	mMesh = IndexMesh::generateByRevolution(profile, nSamples);

	delete profileMesh;
}
