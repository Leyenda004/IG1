#include "IG1App.h"

#include <iostream>

#include "ColorMaterialEntity.h"

using namespace std;

// static single instance (singleton pattern)
IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

// Print OpenGL errors and warnings
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                   GLsizei length, const GLchar* message, const void* userParam)
{
	const char* prefix = (type == GL_DEBUG_TYPE_ERROR)
		? "\x1b[31m[ERROR]\x1b[0m "
		: "\x1b[33m[WARNING]\x1b[0m ";
	cout << prefix << message << endl;
}

void
IG1App::close()
{
	cout << "Closing GLFW...\n";
	glfwSetWindowShouldClose(mWindow, true); // stops main loop
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWindow == 0) // if not intilialized
		init();
	
	// IG1App main loop
	while (!glfwWindowShouldClose(mWindow)) {
		// Redisplay the window if needed
		if (mNeedsRedisplay) {
			display();
			mNeedsRedisplay = false;
		}
		if (mUpdateEnabled) { // Si se ha presionado la u
			GLdouble time = glfwGetTime(); // coges el tiempo en el que se actualiza por �ltima vez
			if (time >= (mNextUpdate)){ // si el tiempo llega a cuando se tiene que volver a actualizar
				mNextUpdate = time + FRAME_DURATION; // cambias cu�ndo se tiene que volver a actualizar
				mScenes[mCurrentScene]->update(); // y actualizas
				// Cuando hay que actualizar se establece el booleano a true
				mNeedsRedisplay = true;
			}
		}

		// Stop and wait for new events
		//glfwWaitEvents();
		if (mUpdateEnabled) glfwWaitEventsTimeout(mNextUpdate - glfwGetTime()); // Si se ha presionado la u, calcula el tiempo que queda
		else glfwWaitEvents();
	}

	destroy();
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH);
	mCamera = new Camera(mViewPort);
	mScenes.push_back(new Scene0);
	mScenes.push_back(new Scene1);
	mScenes.push_back(new Scene2);
	mScenes.push_back(new Scene3);
	mScenes.push_back(new Scene4);
	mScenes.push_back(new Scene5);
	mScenes.push_back(new Scene6);
	mScenes.push_back(new Scene7);

	mCamera->set2D();


	for (int i = 0; i < mScenes.size(); ++i) {
		mScenes[i]->init();
	}
	mScenes[0]->load();

	//EL LOAD HAY QUE QUITARLO EN TODAS LAS CLASES NUEVAS
	//EL LOAD SE HACE AUTOMATICAMENTE AL HACER EL CAMBIO DE ESCENA PERO NO EN LA PRIMERA
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting GLFW...\n";
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // enable on macOS

	// Create window with its associated OpenGL context, return window's pointer
	mWindow = glfwCreateWindow(mWinW, mWinH, "IG1App", nullptr, nullptr);

	if (mWindow == nullptr) {
		glfwTerminate();
		throw std::logic_error("cannot create GLFW window");
	}

	glfwMakeContextCurrent(mWindow);

	// Initialize OpenGL extension library
	if (GLenum err = glewInit(); err != GLEW_OK) {
		glfwTerminate();
		throw std::logic_error("Error while loading extensions: "s +
		                       reinterpret_cast<const char*>(glewGetErrorString(err)));
	}

	// Callback registration
	glfwSetWindowSizeCallback(mWindow, s_resize);
	glfwSetCharCallback(mWindow, s_key);
	glfwSetKeyCallback(mWindow, s_specialkey);
	glfwSetWindowRefreshCallback(mWindow, s_display);

	//EDITABLE, CALLBACKS DE RATON
	glfwSetMouseButtonCallback(mWindow, s_mouse); //Registrar los botones y posicion del raton
	glfwSetCursorPosCallback(mWindow, s_motion); //Mover el raton 
	glfwSetScrollCallback(mWindow, s_mouseWheel); //uso de la rueda del raton

	// Error message callback (all messages)
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0u, 0, GL_TRUE);
	glDebugMessageCallback(debugCallback, nullptr);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::destroy()
{ // release memory and resources
	for (Scene* scene : mScenes)
		delete scene;
	mScenes.clear();

	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;

	glfwTerminate();
}

void
IG1App::display() const
{ // double buffering

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer

	//Si no activamos la vista doble renderizamos la camara normal
	if (!m2Vistas) {
	//Reseteamos la posicion del viewport
	mViewPort->setPos(0, 0);
	//Reseteamos el tama�o del viewport
	mViewPort->setSize(mWinW, mWinH);
	// Reseteamos el tama�o de la camara
	mCamera->setSize(mViewPort->width(), mViewPort->height());

	mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU
	}
	else {
		display2V(escenaSegundaVista == -1 ? mCurrentScene : escenaSegundaVista); //Display2V
	}

	glfwSwapBuffers(mWindow); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned int key)
{
	bool need_redisplay = true;

	// Comprobar si la escena que queremos cargar es la misma en la que estamos
	bool mismaEscena = escenaSegundaVista == mCurrentScene || escenaSegundaVista == -1;

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		// VISTA 3D
		case 'l':
			mCamera->set3D();
			break;
		// VISTA 2D
		case 'o':
			mCamera->set2D();
			break;
		// UPDATE
		case 'u':
			mUpdateEnabled = !mUpdateEnabled;
			break;
		// FOTO
		case 'f' :
			mScenes[mCurrentScene]->takePhoto();
			break;
		// MOVIMIENTO CÁMARA
		case 'a':
			mCamera->moveLR(-1 * cameraSpeed);
			break;
		case 'd':
			mCamera->moveLR(1 * cameraSpeed);
			break;
		case 'w':
			mCamera->moveUD(1 * cameraSpeed);
			break;
		case 's':
			mCamera->moveUD(-1 * cameraSpeed);
			break;
		case 'W':
			mCamera->moveFB(1 * cameraSpeed);
			break;
		case 'S':
			mCamera->moveFB(-1 * cameraSpeed);
			break;
		case 'p':
			mCamera->changePrj();
			break;
		case 'O':
			mCamera->orbit(1 * cameraSpeed);
			break;
		case 'c':
			mCamera->setCenital();
			break;
		case 'k':
			//Llamando al display de 2 vistas
			m2Vistas = !m2Vistas;

			// Cambiar a dos vistas
			if (m2Vistas) {
				// Decidimos la escena que le queremos pasar y la cargamos
				// Si la escena es la misma en la que estamos no la cargamos dos veces
				if (!mismaEscena) {
					mScenes[escenaSegundaVista]->load();
				}
			} // Cambiar a una vista
			else { // Descargamos la segunda escena
				// Si la escena es la misma en la que estamos no la cargamos dos veces
				
				if (!mismaEscena) {
					mScenes[escenaSegundaVista]->unload();
				}
				
			}

			mNeedsRedisplay = true;
			break;
		case 'n':
		case 'N':
			ColorMaterialEntity::toggleShowNormals();
			break;
		default:
			if (key >= '0' && key <= '9' && !changeScene(key - '0'))
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			else
				if (!mScenes[mCurrentScene]->handleKey(key)) //Keys de escenas especificas
				need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void
IG1App::specialkey(int key, int scancode, int action, int mods)
{
	// Only interested in press events
	if (action == GLFW_RELEASE)
		return;

	bool need_redisplay = true;


	if (mods == GLFW_MOD_CONTROL){
		ctrlPressed = true;
	}
	else {
		ctrlPressed = false;
	}
	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;

		
		// ROTACION CAMARA
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL) {
				mCamera->rollReal(1 * cameraSpeed); // rotates 1 on the Z axis
			}
			else
				mCamera->yawReal(1 * cameraSpeed); // rotates 1 on the Y axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL){
				mCamera->rollReal(-1 * cameraSpeed); // rotates -1 on the Z axis
			}
			else
				mCamera->yawReal(-1 * cameraSpeed); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(1 * cameraSpeed); // rotates 1 on the X axis
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-1 * cameraSpeed); // rotates -1 on the X axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

void IG1App::display2V(int nScene) const
{
	//Usamos camara y viewport auxiliar
	Camera auxCam = *mCamera;
	Viewport auxVP = *mViewPort;

	//Para dos puertos de vista
	mViewPort->setSize(mWinW / 2, mWinH);

	//La camara tiene el tama�o del viewport completo, para que siga ocupando la mitad de la pantalla
	auxCam.setSize(mViewPort->width(), mViewPort->height());
	//Restauramos el viewport
	
	//Primer viewport con camara en perspectiva 2D
	mViewPort->setPos(0, 0);
	auxCam.set2D();
	//mScenes[mCurrentScene]->render(auxCam);

	// Cambiar loads de las escenas
	//mScenes[nScene]->load();
	mScenes[nScene]->render(auxCam); //hemos cambiado mCurrentScene por la escena 0
	//mScenes[nScene]->unload();


	//Segundo viewport con camara en perspectiva 3D
	mViewPort->setPos(mWinW / 2, 0);
	auxCam.set3D();
	mScenes[mCurrentScene]->render(auxCam);

	*mViewPort = auxVP;

}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

	if (sceneNr == 7) glClearColor(0.0, 0.0, 0.0, 1.0); // background color (alpha=1 -> opaque)
	else glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)

	// Change only if a different scene
	if (sceneNr != mCurrentScene) {
		mScenes[mCurrentScene]->unload();
		mCurrentScene = sceneNr;
		mScenes[mCurrentScene]->load();
		// El cambio de escena requiere un redisplay
		mNeedsRedisplay = true;
	}

	return true;
}

//Captura en mMouseCoord las coordenadas del rat�n (x,y), y en mMouseButt, el boton pulsado
void IG1App::mouse(int button, int state, int x, int y)
{
	if (button == mMouseButt){ mMouseButt = -1; return; } //Si se pulsa el mismo boton no hacemos nada
	mMouseButt = button; //Registro del boton pulsado
	mMouseCoord = { x, y }; //Registro de la posicoon en x e y del rat�n
}

//Captura las coordenadas del rat�n, obtiene el desplazamiento con respecto a las anteriores coordenadas y, si el boton pulsado es el derecho, mueve la c�mara en sus ejes mRight(horizontal)
//y mUpward(vertical) el correspondiente desplazamiento, mientras que si es el bot�n izquierdo rota la c�maara alrededor de la escena.
void IG1App::motion(int x, int y)
{
	glm::dvec2 mp = { mMouseCoord[0] - x, mMouseCoord[1] - y }; //Usamos la nueva posicion
	mMouseCoord = { x, y }; //Guardamos la nueva posicion para el proximo movimiento
	//Boton izquierdo = 0, Boton derecho = 1
	if (mMouseButt == 0) mCamera->orbit(mp.x * 0.05, mp.y); //Rotamos alrededor de la escena
	else if (mMouseButt == 1) {
		mCamera->moveUD(-mp[1]); //Movimiento vertical de raton
		mCamera->moveLR(mp[0]); //Movimiento horizontal del raton
	}
	mNeedsRedisplay = true;
}

//Si no esta pulsada ninguna tecla modificadora, desplaza la c�mara en su direcci�n de vista (eje mFront), hacia delante/atr�s, seg�n sea d
//positivo/negativo, si se pulsa la tecla control, escala la escena segun el velor de d.
void IG1App::mouseWheel(GLFWwindow* win, int n, int d, int x, int y)
{
	//d es lo que has arrastrado del raton
	// if (!(glfwGetKey(win, GLFW_MOD_CONTROL) == GLFW_PRESS)) {
	if (!ctrlPressed) {
		mCamera->moveFB(d * 5);
	}
	else {
		mCamera->setScale(d * 0.1);
	}
	mNeedsRedisplay = true;
}
