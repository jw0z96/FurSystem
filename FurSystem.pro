# general
TARGET = FurSystem
DESTDIR = .
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

# qt config
QT += gui
QT += opengl
QT += core
QT += widgets

# project files
SOURCES += ./src/*.cpp \
	./nodeeditor/*.cpp

HEADERS += ./include/*.h \
	./nodeeditor/*.hpp

INCLUDEPATH += ./include \
	./nodeeditor

RESOURCES += ./resources/resources.qrc \
	$$PWD/ui/MainWindow.ui

OBJECTS_DIR = ./obj

MOC_DIR = ./moc

#FORMS += $$PWD/ui/MainWindow.ui

DEFINES += NODE_EDITOR_SHARED

#OTHER_FILES+= shaders/*.glsl  \
#	README.md \

isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES += QT5BUILD
}

LIBS+=-lboost_system
