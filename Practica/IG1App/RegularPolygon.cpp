#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(glm::dvec4 color, GLuint edges, GLdouble radius) : SingleColorEntity(color) { 
	mMesh = Mesh::generateRegularPolygon(edges, radius);
	//load(); // No se usa el load de todas las clases de primitivas porque se cargan en IG1App.cpp
}