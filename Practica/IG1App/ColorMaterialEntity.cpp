#include "ColorMaterialEntity.h"
#include "Material.h"

#include <iostream>
using namespace glm;

ColorMaterialEntity::ColorMaterialEntity() : EntityWithMaterial() {
	mShader =       Shader::get("light"); //Usamos el shader light, en vez de simple_light
    mShaderAux =    Shader::get("normals");
    colorDefecto = mMaterial.getAmbient();
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat;

        // usamos el shader simple_light
        mShader->use();
        mShader->setUniform("modelView",aMat);
        mShader->setUniform("color", glm::vec4(colorDefecto[0], colorDefecto[1], colorDefecto[2], 1.0f)); //Necesitamos cargar el color de SingleColorEntity
		mMaterial.upload(*mShader);
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
