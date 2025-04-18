#include "Disk.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std;

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples)
{
	vector<vec2> perfil(nRings);
	for (GLuint i = 0; i < nRings; ++i)
	{
		float theta = (2.0f * std::numbers::pi * i) / nRings;
		float x = R + r * cos(radians(theta));
		float y = r * sin(radians(theta));
		perfil[i] = vec2(x, y);
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}


