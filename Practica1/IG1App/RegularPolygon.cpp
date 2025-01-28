#include "RegularPolygon.h"

RegularPolygon::RegularPolygon() {
	mMesh = Mesh::generateRegularPolygon(7, 1);
}