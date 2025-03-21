#include "IG1App.h"

#include <iostream>

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
			GLdouble time = glfwGetTime(); // coges el tiempo en el que se actualiza por última vez
			if (time >= (mNextUpdate)){ // si el tiempo llega a cuando se tiene que volver a actualizar
				mNextUpdate = time + FRAME_DURATION; // cambias cuándo se tiene que volver a actualizar
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

	mScenes[mCurrentScene]->render(*mCamera); // uploads the viewport and camera to the GPU

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

	switch (key) {
		case '+':
			mCamera->setScale(+0.01); // zoom in  (increases the scale)
			break;
		case '-':
			mCamera->setScale(-0.01); // zoom out (decreases the scale)
			break;
		case 'l':
			mCamera->set3D();
			break;
		case 'o':
			mCamera->set2D();
			break;
		case 'u':
			//cout << "pressed u" << endl; // Depuración
			mUpdateEnabled = !mUpdateEnabled;
			//cout << "mUpdateEnabled = " << mUpdateEnabled << endl; // Depuración
			break;
		case 'f' :
			mScenes[mCurrentScene]->takePhoto();
			break;
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
		// Esto lo pilla bien (just in case)
		case 'W':
			mCamera->moveFB(1 * cameraSpeed);
			std::cout << "W" << std::endl;
			break;
		case 'S':
			mCamera->moveFB(-1 * cameraSpeed);
			std::cout << "S" << std::endl;
			break;
		case 'p':
			mCamera->changePrj();
			std::cout << "changePrj()" << std::endl;
			break;
		case 'O':
			// mCamera->setOrbiting(!mCamera->isOrbiting());
			mCamera->orbit(1, 0);
		default:
			if (key >= '0' && key <= '9' && !changeScene(key - '0'))
				cout << "[NOTE] There is no scene " << char(key) << ".\n";
			else
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

	// Handle keyboard input
	// (key reference: https://www.glfw.org/docs/3.4/group__keys.html)
	switch (key) {
		case GLFW_KEY_ESCAPE:                     // Escape key
			glfwSetWindowShouldClose(mWindow, true); // stops main loop
			break;

		// Duda ?? Hemos tenido que cambiar el shift porque no funcionaba el control
		case GLFW_KEY_RIGHT:
			if (mods == GLFW_MOD_CONTROL) {
				mCamera->rollReal(1 * cameraSpeed); // rotates -1 on the X axis
			}
			else
				mCamera->yawReal(1 * cameraSpeed); // rotates 1 on the X axis
			break;
		case GLFW_KEY_LEFT:
			if (mods == GLFW_MOD_CONTROL){
				mCamera->rollReal(-1 * cameraSpeed); // rotates 1 on the Y axis
			}
			else
				mCamera->yawReal(-1 * cameraSpeed); // rotate -1 on the Y axis
			break;
		case GLFW_KEY_UP:
			mCamera->pitchReal(1 * cameraSpeed); // rotates 1 on the Z axis
			break;
		case GLFW_KEY_DOWN:
			mCamera->pitchReal(-1 * cameraSpeed); // rotates -1 on the Z axis
			break;
		default:
			need_redisplay = false;
			break;
	} // switch

	if (need_redisplay)
		mNeedsRedisplay = true;
}

bool
IG1App::changeScene(size_t sceneNr)
{
	// Check whether the scene exists
	if (sceneNr >= mScenes.size())
		return false;

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
