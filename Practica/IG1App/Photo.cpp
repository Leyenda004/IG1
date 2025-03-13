#include "Photo.h"
#include "IG1App.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Photo::Photo(GLdouble w, GLdouble h) : EntityWithTexture()
{
    mMesh = Mesh::generateRectangleTexCor(w,h);
    mat4 rot = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
    mat4 trans = translate(mat4(1.0f), vec3(0.0f, /*1.0f*/0.0f, 0.0f)); //ya no es necesario
    setModelMat(trans * rot * mModelMat);
    mTexture = new Texture();
    setTexture(mTexture);
}

void Photo::update()
{
    mTexture->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight());
}
