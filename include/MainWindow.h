#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QKeyEvent>

#include "nodeeditor/FlowView.hpp"
#include "nodeeditor/FlowScene.hpp"

using QtNodes::FlowScene;
using QtNodes::FlowView;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		explicit MainWindow(QWidget *parent = 0);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//-------------------------------------------------------------------------------------------------\---------------------
		~MainWindow();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief keypress event handling
		//----------------------------------------------------------------------------------------------------------------------
		void keyPressEvent(QKeyEvent *_event) override;

	public slots:

	private:
		Ui::MainWindow *m_ui;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_gl our openGL viewport widget
		//----------------------------------------------------------------------------------------------------------------------
		QOpenGLWidget *m_gl;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_nodes Flow scene, contains the functionality of the node scene
		//----------------------------------------------------------------------------------------------------------------------
		FlowScene *m_nodes;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_flowView viewport that displays the node graph
		//----------------------------------------------------------------------------------------------------------------------
		FlowView *m_flowView;
};

#endif // MAINWINDOW_H
