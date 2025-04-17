#include "ColorMaterialEntity.h"

using namespace glm;

ColorMaterialEntity::ColorMaterialEntity() {
	mShader = Shader::get("LightDir");
    mShaderAux = Shader::get("normals");
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
        mShader->use();
        mShader->setUniform("LightDir", modelViewMat);
        upload(aMat);
        mMesh->render();

        if (mShowNormals) {
            mShaderAux->use();
            mShaderAux->setUniform("normals", modelViewMat);
            mMesh->render();
        }
    }
}