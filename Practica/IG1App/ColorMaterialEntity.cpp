#include "ColorMaterialEntity.h"

#include <iostream>
using namespace glm;

ColorMaterialEntity::ColorMaterialEntity() : SingleColorEntity({0.0f,1.0f,0.0f,1.0f}) {
	mShader =       Shader::get("simple_light"); //Usamos el shader simple_light
    mShaderAux =    Shader::get("normals");
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;

        // usamos el shader simple_light
        mShader->use();
        mShader->setUniform("modelView",aMat);
        mShader->setUniform("color", (vec4)color()); //Necesitamos cargar el color de SingleColorEntity
        upload(aMat);
        mMesh->render(); //Renderizamos la forma con color e iluminacion

        // si se desea mostrar normales visualmente
        if (mShowNormals) {
            mShaderAux->use();
            mShaderAux->setUniform("modelView",modelViewMat);
            mMesh->render(); //Renderizamos normales
        }
    }
}
