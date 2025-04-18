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
	vector<vec2> profile(nPoints + 1);

	for (GLint i = 0; i < profile.size(); ++i) {
		float ang = (2.0f * std::numbers::pi * i) / nPoints;
		// radians() lo convierte en un disco
		float x = R + r * cos(/*radians*/(ang));
		float y = r * sin(/*radians*/(ang));
		profile[i] = vec2(x, y);
	}
	
	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}