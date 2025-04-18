#include "Cone.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std;

Cone::Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples)
{
	vector<vec2> perfil(nRings + 1);
	for (GLuint i = 0; i < nRings + 1; ++i)
	{
		float theta = (2.0f * std::numbers::pi * i) / nRings;
		float x = R + r * cos(radians(theta));
		float y = r * sin(radians(theta));
		perfil[i] = vec2(x, y);
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples, h);
}
