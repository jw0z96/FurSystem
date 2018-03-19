#include "Viewport.h"

#include <QApplication>
#include <QKeyEvent>

#include <iostream>

#include "RenderableManager.h"
#include "ComputeShaderManager.h"

//----------------------------------------------------------------------------------------------------------------------

Viewport::Viewport(QWidget* _parent) : QOpenGLWidget(_parent)
{
	// set this widget to have the initial keyboard focus
	setFocusPolicy(Qt::StrongFocus);
	this->resize(_parent->size());
	m_timer.start();
	// startTimer(10);
}

//----------------------------------------------------------------------------------------------------------------------

Viewport::~Viewport()
{
	std::cout<<"~Viewport\n";
	RenderableManager::getInstance()->cleanUpAll();
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::resizeGL(int _w, int _h)
{
	m_cam.setProjection(45.0f, static_cast<float>(_w) / _h, 0.1f, 1000.0f);
	m_win.width  = static_cast<int>(_w * devicePixelRatio());
	m_win.height = static_cast<int>(_h * devicePixelRatio());
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::initializeGL()
{
	// set this first so that new driver features are included.
	glewExperimental = true;
	// now init glew
	GLenum err = glewInit();
	// error check
	if (GLEW_OK != err)
	{
		std::cerr<<"Error: "<<glewGetErrorString(err)<<"\n";
	}
	int majorVersion,minorVersion;
	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
	std::cerr <<"glew configured with GL version "<<majorVersion<<"."<<minorVersion<<"\n";

	// Grey Background
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	// enable multisampling for smoother drawing
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);

	glm::vec3 from(-1.0, 0.0, -1.0);
	glm::vec3 to(0.0, 0.0, 0.0);
	glm::vec3 up(0.0, 1.0, 0.0);
	m_cam.set(from, to, up);
	m_cam.setProjection(45.0f,(float)1024/720,1.0f,1000.0f);

	glViewport(0,0,width(),height());

	RenderableManager::getInstance()->registerViewport(this);
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::paintGL()
{
	float currentFrame = m_timer.elapsed()*0.001f;
	// std::cout<<"FPS: "<<1.0f / m_deltaTime<<'\n';
	m_framesPerSecond = 1.0f / m_deltaTime;
	m_deltaTime = currentFrame - m_lastFrame;
	m_lastFrame = currentFrame;

	/// first we reset the movement values
	float xDirection=0.0;
	float yDirection=0.0;
	// now we loop for each of the pressed keys in the the set
	// and see which ones have been pressed. If they have been pressed
	// we set the movement value to be an incremental value
	constexpr float s_update = 1.0f;
	foreach(Qt::Key key, m_keysPressed)
	{
		switch (key)
		{
			case Qt::Key_Left : {yDirection=-s_update; break;}
			case Qt::Key_Right : {yDirection=s_update; break;}
			case Qt::Key_Up : {xDirection=s_update; break;}
			case Qt::Key_Down : {xDirection=-s_update; break;}
			default : break;
		}
	}
	// if the set is non zero size we can update the ship movement
	// then tell openGL to re-draw
	if (m_keysPressed.size() !=0)
	{
		m_cam.move(xDirection, yDirection, m_deltaTime);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RenderableManager::getInstance()->cleanupRenderables();
	RenderableManager::getInstance()->constructRenderables();
	loadMatricesToRenderManager();
	RenderableManager::getInstance()->drawRenderables();

	// ComputeShaderManager::getInstance()->endTimer();
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::keyPressEvent(QKeyEvent *_event)
{
	// add to our keypress set the values of any keys pressed
	m_keysPressed += static_cast<Qt::Key>(_event->key());

	// this method is called every time the main window recives a key event.
	// we then switch on the key value and set the camera in the GLWindow
	switch (_event->key())
	{
		// escape key to quit
		case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
		// turn on wirframe rendering
		case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
		// turn off wire frame
		case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
		// show full screen
		case Qt::Key_F : showFullScreen(); break;
		// center camera
		case Qt::Key_C : m_cam.resetPos(); break;
		// show windowed
		case Qt::Key_N : showNormal(); break;
		default : break;
	}
	// finally update the GLWindow and re-draw
	//if (isExposed())
	update();
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::keyReleaseEvent( QKeyEvent *_event)
{
	// remove from our key set any keys that have been released
	m_keysPressed -= static_cast<Qt::Key>(_event->key());
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::loadMatricesToRenderManager()
{
	glm::mat4 M = glm::mat4(1.0);
	glm::mat4 MV = m_cam.getView() * M;
	glm::mat4 MVP = m_cam.getVP() * M;
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(MV)));
	// glm::mat3 normalMatrix = glm::mat3(MV);
	RenderableManager::getInstance()->setMatrices(M, MV, MVP, normalMatrix, m_cam.getEye());
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::timerEvent(QTimerEvent *_event)
{
	update();
}
