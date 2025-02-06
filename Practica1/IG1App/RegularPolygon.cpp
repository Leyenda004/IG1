#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(glm::dvec4 color, GLuint edges, GLdouble radius) : SingleColorEntity(color) { 
	mMesh = Mesh::generateRegularPolygon(edges, radius);
	//SingleColorEntity::load();
	load();
}