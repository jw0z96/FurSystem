#include <GL/glew.h>
#include <QApplication>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	// create an OpenGL format specifier
	QSurfaceFormat format;
	format.setSamples(16);
	format.setDepthBufferSize(16);
	format.setVersion(4, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);
	// we can now query the version to see if it worked
	std::cout<<"Profile is "<<format.majorVersion()<<" "<<format.minorVersion()<<"\n";

	// glewExperimental = GL_TRUE;
	// glewInit();

	// now we are going to create our scene window
	MainWindow window;
	window.show();
	return app.exec();
}
