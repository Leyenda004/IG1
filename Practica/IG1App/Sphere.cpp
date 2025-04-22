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
		//1.0f porque vamos en sentido antihorario al igual que las normales y que el revolution
		float theta = std::numbers::pi * (1.0f - float(i) / nParallels);  //+90° a -90° y no multiplicamos por 2.0f ya que 
																		  //necesitamos media circunferencia de perfil, no una entera
		float x = radius * sin(theta);  
		float y = radius * cos(theta); 
		perfil[i] = vec2(x, y);
	}

	mMesh = IndexMesh::generateByRevolution(perfil, nMeridians);
}
