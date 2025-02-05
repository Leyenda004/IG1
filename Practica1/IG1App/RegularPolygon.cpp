#include "RegularPolygon.h"

RegularPolygon::RegularPolygon() : SingleColorEntity() {
	mMesh = Mesh::generateRegularPolygon(7, 100.0); 
	//SingleColorEntity::load();
	load();
}