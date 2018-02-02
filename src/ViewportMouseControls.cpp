#include "Viewport.h"
#include <QMouseEvent>

//----------------------------------------------------------------------------------------------------------------------

void Viewport::mouseMoveEvent(QMouseEvent* _event)
{
	// note the method buttons() is the button state when event was called
	// that is different from button() which is used to check which button was
	// pressed when the mousePress/Release event is generated
	if (  _event->buttons() == Qt::LeftButton )
	{
		int diffx = _event->x() - m_win.origX;
		int diffy = _event->y() - m_win.origY;
		m_win.origX = _event->x();
		m_win.origY = _event->y();
		m_cam.processMouseMovement(diffx,diffy);
		update();
	}
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::mousePressEvent(QMouseEvent* _event)
{
	// that method is called when the mouse button is pressed in this case we
	// store the value where the maouse was clicked (x,y) and set the Rotate flag to true
	if ( _event->button() == Qt::LeftButton )
	{
		m_win.origX  = _event->x();
		m_win.origY  = _event->y();
	}
}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::mouseReleaseEvent(QMouseEvent* _event){}

//----------------------------------------------------------------------------------------------------------------------

void Viewport::wheelEvent(QWheelEvent* _event)
{
	// check the diff of the wheel position (0 means no change)
	if ( _event->delta() > 0 )
	{
		m_cam.processMouseScroll(1.0f);
	}
	else if ( _event->delta() < 0 )
	{
		m_cam.processMouseScroll(-1.0f);
	}
	update();
}
