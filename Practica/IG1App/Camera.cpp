#include "Shader.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_access.hpp>
// otros includes Elena
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

//N diferencia entre el look y el eye

Camera::Camera(Viewport* vp)
  : mViewMat(1.0)
  , mProjMat(1.0)
  , xRight(vp->width() / 2.0)
  , xLeft(-xRight)
  , yTop(vp->height() / 2.0)
  , yBot(-yTop)
  , mViewPort(vp)
{
	setPM();
	setAxes();
}

void
Camera::uploadVM() const
{
	Shader::setUniform4All("modelView", mViewMat);
}

void
Camera::setVM()
{
	mViewMat = lookAt(mEye, mLook, mUp); // glm::lookAt defines the view matrix
	setAxes();
}

void
Camera::set2D()
{
	mEye = {0, 0, 500}; 
	mLook = {0, 0, 0}; 
	mUp = {0, 1, 0}; 
	mAng = -90;
	mRadio = 300.0f;
	setVM(); //Actualizamos matriz de vista con los nuevos parametros
}

void
Camera::set3D()
{
	mEye = {500, 500, 500};
	mLook = {0, 10, 0};
	mUp = {0, 1, 0};
	mAng = 90;
	mRadio = 300.0f;
	setVM(); //Actualizamos matriz de vista con los nuevos parametros
}

void
Camera::pitch(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::yaw(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::roll(GLdouble a)
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
	setAxes();
}

void
Camera::setSize(GLdouble xw, GLdouble yh)
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}

void
Camera::setScale(GLdouble s)
{
	mScaleFact -= s;
	if (mScaleFact < 0)
		mScaleFact = 0.01;
	setPM();
}

void
Camera::setPM()
{
	if (bOrto) { //  if orthogonal projection
		mProjMat = ortho(xLeft * mScaleFact,
		                 xRight * mScaleFact,
		                 yBot * mScaleFact,
		                 yTop * mScaleFact,
		                 mNearVal,
		                 mFarVal);
		// glm::ortho defines the orthogonal projection matrix
	}
	else {
		mProjMat = frustum(	xLeft * mScaleFact * 0.001f,
							xRight * mScaleFact * 0.001f,
							yBot * mScaleFact * 0.001f,
							yTop * mScaleFact * 0.001f,
							mNearVal,
							mFarVal);
	}
}

void
Camera::uploadPM() const
{
	Shader::setUniform4All("projection", mProjMat);
}

void
Camera::upload() const
{
	mViewPort->upload();
	uploadVM();
	uploadPM();
}

void Camera::setAxes() {
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2); // Importante el (-)
}

// (-n = look - eye)

//MOVIMIENTO DE CAMARA HACIA LA IZQUIERDA Y DERECHA
void Camera::moveLR(GLfloat cs)
{
	// Global
	mEye += mRight * cs;
	mLook += mRight * cs;

	// Local
	//mEye.x += cs;
	//mLook.x += cs;
	setVM();
}

//MOVIMIENTO DE CAMARA HACIA DELANTE Y HACIA ATRAS (Solo con perspectiva, no ortogonal)
void Camera::moveFB(GLfloat cs)
{
	// Global
	mEye += mFront * cs;
	mLook += mFront * cs;

	// Local
	//mEye.z += cs;
	//mLook.z += cs;
	setVM();
}

//MOVIMIENTO DE CAMARA ARRIBA Y ABAJO
void Camera::moveUD(GLfloat cs)
{
	// Global
	mEye += mUpward * cs;
	mLook += mUpward * cs;

	// Local
	//mEye.y += cs;
	//mLook.y += cs;
	setVM();
}

//CAMBIO DE PERSPECTIVA POR PARAMETRO bOrto
void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM(); //Actualizamos la matriz de puerto de vista
}

//ROTACION DESDE LA PROPIA CAMARA ARRIBA/ABAJO
void Camera::pitchReal(GLfloat cs)
{
	mLook = mEye + rotate(mLook - mEye, radians(double(cs)), dvec3(mRight));
	mUp = rotate(mUp, radians(double(cs)), dvec3(mRight));

	//mLook += mUpward * cs;
	setVM();
}

//ROTACION DESDE LA PROPIA CAMARA IZQUIERDA/DERECHA
void Camera::yawReal(GLfloat cs)
{
	//mLook += mRight * cs;
	mLook = mEye + rotate(mLook - mEye, radians(double(-cs)), dvec3(mUpward));
	mUp = rotate(mUp, radians(double(cs)), dvec3(mUp));
	//mUp = rotate(mUp, radians(double(cs)), dvec3(mUpward));

	setVM();

}

//ROTACION DESDE LA CAMARA EN ESPIRAL SOBRE SU EJE FRONTAL
void Camera::rollReal(GLfloat cs)
{
	//mLook += mFront * cs;
	//mUp += mRight * cs;
	
	//mFront es mLook - mEye
	//-cs porque el giro es inverso
	mRight = rotate(mLook - mEye, radians(double(cs)), dvec3(mFront));
	//mLook = mEye + rotate(mLook - mEye, radians(double(-cs)), dvec3(mFront));
	mUp = rotate(mUp, radians(double(-cs)), dvec3(mFront));
	//rotar el up sobre el front
	setVM();
}

//ROTACION A PARTIR DE UN ANGULO CONCRETO
void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	mUp = { 0, 1, 0 };
	setVM();
}

void Camera::setCenital()
{
	mEye = { 0, 500, 0 }; //Nos situamos arriba de la escena
	//Look - eye = n, sale negativo pero porque la camara esta en posicion negativa, como el set2D
	mLook = { 0, 0, 0 }; 
	mUp = { 0, 0, 1 };
	mAng = 90;
	mRadio = 300.0f;
	setVM();
}
