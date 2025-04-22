#include "Cone.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std;

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples)
{
	vector<vec2> perfil(nRings);

	for (GLuint i = 0; i < nRings; ++i) {
		GLdouble y = -h / 2.0 + h * i / nRings; //va de -h/2 a h/2 siendo h la altura del cono
		GLdouble x = r + (R - r) * (GLdouble(i) / nRings);  // Calculamos la diferencia entre ambos radios y lo aumentamos en funcion de los anillos que quedan por cubrir
		perfil[i] = vec2(x, y);  // punto del perfil
	}

	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}
