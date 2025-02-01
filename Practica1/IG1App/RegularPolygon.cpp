#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(){
	//mShader = Shader::get("vcolors");
	mMesh = Mesh::generateRegularPolygon(7, 100.0); 
	//SingleColorEntity::load();
	load();
}