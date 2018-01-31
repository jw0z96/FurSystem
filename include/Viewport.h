#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <GL/glew.h>

#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <QSet>

#include "FirstPersonCamera.h"

struct WinParams
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief used to store the x rotation mouse value
	//----------------------------------------------------------------------------------------------------------------------
	int spinXFace = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief used to store the y rotation mouse value
	//----------------------------------------------------------------------------------------------------------------------
	int spinYFace = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if the mouse button is pressed when dragging
	//----------------------------------------------------------------------------------------------------------------------
	bool rotate = false;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief flag to indicate if the Right mouse button is pressed when dragging
	//----------------------------------------------------------------------------------------------------------------------
	bool translate = false;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the previous x mouse value
	//----------------------------------------------------------------------------------------------------------------------
	int origX = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the previous y mouse value
	//----------------------------------------------------------------------------------------------------------------------
	int origY = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the previous x mouse value for Position changes
	//----------------------------------------------------------------------------------------------------------------------
	int origXPos = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the previous y mouse value for Position changes
	//----------------------------------------------------------------------------------------------------------------------
	int origYPos = 0;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief window width
	//----------------------------------------------------------------------------------------------------------------------
	int width = 1024;
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief window height
	//----------------------------------------------------------------------------------------------------------------------
	int height = 720;
};

//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
constexpr float INCREMENT = 2.5f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
constexpr float ZOOM = 2.5f;

class Viewport : public QOpenGLWidget
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief Constructor for GLWindow
		//----------------------------------------------------------------------------------------------------------------------
		explicit Viewport(QWidget *_parent = 0);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief dtor
		//----------------------------------------------------------------------------------------------------------------------
		~Viewport();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief the initialize class is called once when the window is created and we have a valid GL context
		/// use this to setup any default GL stuff
		//----------------------------------------------------------------------------------------------------------------------
		void initializeGL() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this is called everytime we want to draw the scene
		//----------------------------------------------------------------------------------------------------------------------
		void paintGL() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this is called everytime we resize
		//----------------------------------------------------------------------------------------------------------------------
		void resizeGL(int _w, int _h) override;

	public slots:

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief the windows params such as mouse and rotations etc
		//----------------------------------------------------------------------------------------------------------------------
		WinParams m_win;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief Our Camera
		//----------------------------------------------------------------------------------------------------------------------
		FirstPersonCamera m_cam;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief the keys being pressed
		//----------------------------------------------------------------------------------------------------------------------
		QSet<Qt::Key> m_keysPressed;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief timing for camera update
		//----------------------------------------------------------------------------------------------------------------------
		float m_deltaTime = 0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief frame time for camera update
		//----------------------------------------------------------------------------------------------------------------------
		float m_lastFrame = 0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief frames per second for gui
		//----------------------------------------------------------------------------------------------------------------------
		float m_framesPerSecond = 0.0f;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief timer for measurment
		//----------------------------------------------------------------------------------------------------------------------
		QElapsedTimer m_timer;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief Qt Event called when a key is pressed
		/// @param [in] _event the Qt event to query for size etc
		//----------------------------------------------------------------------------------------------------------------------
		void keyPressEvent(QKeyEvent *_event) override;
		void keyReleaseEvent(QKeyEvent *_event) override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this method is called every time a mouse is moved
		/// @param _event the Qt Event structure
		//----------------------------------------------------------------------------------------------------------------------
		void mouseMoveEvent (QMouseEvent * _event ) override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this method is called everytime the mouse button is pressed
		/// inherited from QObject and overridden here.
		/// @param _event the Qt Event structure
		//----------------------------------------------------------------------------------------------------------------------
		void mousePressEvent (QMouseEvent *_event) override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this method is called everytime the mouse button is released
		/// inherited from QObject and overridden here.
		/// @param _event the Qt Event structure
		//----------------------------------------------------------------------------------------------------------------------
		void mouseReleaseEvent (QMouseEvent *_event ) override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief this method is called everytime the mouse wheel is moved
		/// inherited from QObject and overridden here.
		/// @param _event the Qt Event structure
		//----------------------------------------------------------------------------------------------------------------------
		void wheelEvent(QWheelEvent *_event) override;
};

#endif // VIEWPORT_H
