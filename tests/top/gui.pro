TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

CONFIG+=debug

OBJECTS_DIR=.obj
MOC_DIR=.obj

INCLUDEPATH += . ../../dependencies/irrlicht/include/ 

LIBS += ../../dependencies/irrlicht/lib/Linux/libIrrlicht.a  -lGL -lXxf86vm

QT= core gui opengl


HEADERS += IrrlichtGraphicsScene.hpp scene.hpp
SOURCES += IrrlichtGraphicsScene.cpp main.cpp scene.cpp
