#include "MainWindow.h"
#include "widgets/ui_MainWindow.h"
#include "ObjMeshModel.h"
#include "MeshRendererModel.h"
#include "CurvesRendererModel.h"
#include "DistributorModel.h"
#include "BendCurveOperatorModel.h"

#include "nodeeditor/DataModelRegistry.hpp"
#include "nodeeditor/ConnectionStyle.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
	auto ret = std::make_shared<DataModelRegistry>();
	ret->registerModel<ObjMeshModel>();
	ret->registerModel<MeshRendererModel>();
	ret->registerModel<CurvesRendererModel>();
	ret->registerModel<DistributorModel>();
	ret->registerModel<BendCurveOperatorModel>();
	return ret;
}

static void setStyle()
{
	ConnectionStyle::setConnectionStyle(
		R"(
		{
			"ConnectionStyle": {
				"UseDataDefinedColors": true
			}
		}
		)");
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
	::setStyle();
	m_nodes = new FlowScene(registerDataModels());
	m_flowView = new FlowView(m_nodes);

	m_ui->mainWindowGridLayout->addWidget(m_flowView, 0, 1, 1, 1);
}

MainWindow::~MainWindow()
{
	delete m_ui;
	// delete m_gl;
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
