#include "Sphere.h"
#include "IndexMesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;
using namespace std; 

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians)
{
	vector<vec2> perfil(nParallels);

	for (GLuint i = 0; i < nParallels; ++i)
	{
		float theta = (2.0f * std::numbers::pi * i) / nParallels;
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		perfil[i] = vec2(x, y);
	}

	mMesh = IndexMesh::generateByRevolution(perfil, nMeridians);
}
