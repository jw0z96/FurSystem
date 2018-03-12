#include "MainWindow.h"
#include "widgets/ui_MainWindow.h"
#include "ObjMeshModel.h"
#include "MeshRendererModel.h"
#include "CurvesRendererModel.h"
#include "BasicDistributorModel.h"
#include "RandomDistributorModel.h"
#include "BendCurveOperatorModel.h"
#include "NoiseCurveOperatorModel.h"
#include "ClumpCurveOperatorModel.h"
#include "ComputeShaderManager.h"
#include "RenderableManager.h"

#include "nodeeditor/DataModelRegistry.hpp"
#include "nodeeditor/ConnectionStyle.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::ConnectionStyle;

static std::shared_ptr<DataModelRegistry> registerDataModels()
{
	auto ret = std::make_shared<DataModelRegistry>();
	ret->registerModel<ObjMeshModel>("Mesh Loaders");
	ret->registerModel<MeshRendererModel>("Renderers");
	ret->registerModel<CurvesRendererModel>("Renderers");
	ret->registerModel<BasicDistributorModel>("Distributors");
	ret->registerModel<RandomDistributorModel>("Distributors");
	ret->registerModel<BendCurveOperatorModel>("Curve Operators");
	ret->registerModel<NoiseCurveOperatorModel>("Curve Operators");
	ret->registerModel<ClumpCurveOperatorModel>("Curve Operators");
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
	m_ui(new Ui::MainWindow),
	m_splitter(new QSplitter(parent))
{
	// setup ui
	m_ui->setupUi(this);
	// create viewport widget
	m_gl = new Viewport(this);
	// create node graph widget
	::setStyle();
	m_nodes = new FlowScene(registerDataModels());
	m_flowView = new FlowView(m_nodes);
	// add widgets to splitter
	m_splitter->addWidget(m_gl);
	m_splitter->addWidget(m_flowView);
	m_splitter->setSizes(QList<int>({INT_MAX, INT_MAX})); // set size of both splits to max so we fill 50/50
	// add splitter to layout
	m_ui->mainWindowGridLayout->addWidget(m_splitter, 0, 0, 1, 1);
	// create menubar actions
	auto saveAction = m_ui->menubar->addAction("Save..");
	auto loadAction = m_ui->menubar->addAction("Load..");
	// connect signals
	QObject::connect(saveAction, &QAction::triggered, m_nodes, &FlowScene::save);
	QObject::connect(loadAction, &QAction::triggered, m_nodes, &FlowScene::load);
}

MainWindow::~MainWindow()
{
	delete m_ui;
	delete m_gl;
	delete m_splitter;
}

void MainWindow::keyPressEvent(QKeyEvent *_event)
{
	// this is called every time we receive a key event.
	switch(_event->key())
	{
		// escape key to quit
		case Qt::Key_Escape: QGuiApplication::exit(EXIT_SUCCESS); break;
		case Qt::Key_S: m_nodes->save(); break;
		case Qt::Key_L: m_nodes->load(); break;
		case Qt::Key_R:
			ComputeShaderManager::getInstance()->recompileShaders();
			RenderableManager::getInstance()->recompileShaders();
			break;
		default: break;
	}
}
