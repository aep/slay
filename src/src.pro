TEMPLATE = app
TARGET = slay
DEPENDPATH += . gui scene
INCLUDEPATH += . gui scene \
     ../dependencies/irrlicht/include/ \
     ../dependencies/qtsl/lib/systems/session \
     ../dependencies/qtsl/lib/systems/simulator \
     ../dependencies/qtsl/lib/systems/avatar \
     ../dependencies/qtsl/lib/systems/scene \
     ../dependencies/qtsl/lib/systems/chat \
     ../dependencies/qtsl/lib/systems/inventory 

LIBS += ../dependencies/irrlicht/lib/Linux/libIrrlicht.a ../dependencies/qtsl/lib/libqtsl.a  -lGL

MOC_DIR=.obj
OBJECTS_DIR=.obj
UI_DIR=.obj

QT=core gui opengl network webkit

CONFIG+=debug


QMAKE_CXXFLAGS_WARN_ON  = 


RESOURCES += ../resources/resources.qrc
FORMS   +=  gui/MainWindow.ui
HEADERS +=  gui/MainWindow.hpp \
            gui/QIrrlichtWidget.hpp \
            gui/SceneWidget.hpp \
            gui/InventoryModel.hpp \
            scene/MainScene.hpp 

SOURCES +=  gui/Main.cpp \
            gui/MainWindow.cpp \
            gui/QIrrlichtWidget.cpp \
            gui/SceneWidget.cpp \
            gui/InventoryModel.cpp  \
            scene/MainScene.cpp 
