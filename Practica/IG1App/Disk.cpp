#include "Disk.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std;

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, GLfloat angleMax)
{
	//CON DOS VERTICES
	//vector<vec2> perfil(2); //reservando dos puntos de perfil
	//perfil[0] = {r, 0.0}; //punto mas cercano al centro
	//perfil[1] = {R, 0.0}; //punto mas alejado al centro
	//mMesh = IndexMesh::generateByRevolution(perfil, nSamples); //El perfil es una linea

	//CON NRINGS
	vector<vec2> perfil(nRings); //reservando nRings de perfil
	for (GLuint i = 0; i < nRings; ++i) {
		GLdouble x = r + (R - r) * (-1.0f * GLdouble(i) / nRings);  // Calculamos la diferencia entre ambos radios y lo aumentamos en funcion de los anillos que quedan por cubrir
		//Usamos 1.0f porque lo hacemos en sentido antihorario como Sphere
		perfil[i] = vec2(x, 0.0);  // punto del perfil
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples, angleMax); //El perfil es una linea de n rings
}


