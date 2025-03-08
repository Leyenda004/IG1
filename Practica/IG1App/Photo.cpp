#include "Photo.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void Photo::update()
{
	mTexture->loadColorBuffer(800.f, 600.f);
}

Photo::Photo()
{
    mMesh = Mesh::generateRectangleTexCor(100,100);
    mat4 rot = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
    mat4 trans = translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f));
    setModelMat(trans * rot * mModelMat);
}
