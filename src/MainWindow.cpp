#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ObjMeshModel.h"
#include "MeshRendererModel.h"

#include "nodeeditor/DataModelRegistry.hpp"

using QtNodes::DataModelRegistry;

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
	auto ret = std::make_shared<DataModelRegistry>();
	ret->registerModel<ObjMeshModel>();
	ret->registerModel<MeshRendererModel>();
	return ret;
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_ui(new Ui::MainWindow)
{
	// setup ui
	m_ui->setupUi(this);
	// create viewport widget
	m_gl = new Viewport(this);
	m_ui->mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);
	// create node graph widget
	m_nodes = new FlowScene(registerDataModels());
	m_flowView = new FlowView(m_nodes);
	m_ui->mainWindowGridLayout->addWidget(m_flowView, 0, 1, 1, 1);
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
