#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow)
{
	// setup ui
	m_ui->setupUi(this);
	// create viewport widget
	m_gl = new QOpenGLWidget(this);
	m_ui->viewportWidget->addWidget(m_gl,0,0,1,1);
	// create node graph widget
	m_nodes = new FlowScene();
	m_flowView = new FlowView(m_nodes);
	m_ui->flowViewWidget->addWidget(m_flowView, 0, 0, 1, 1);
}

MainWindow::~MainWindow()
{
	delete m_ui;
	delete m_gl;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
	// this is called every time we receive a key event.
	switch(_event->key())
	{
		// escape key to quit
		case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
		default: break;
	}
}