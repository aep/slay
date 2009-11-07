#include "scene.hpp"
#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QDateTime>
#include <QtOpenGL>

using namespace irr;
using namespace irr;
using namespace irr::video;
using namespace irr::core;
using namespace irr::scene;

Scene::Scene(IrrlichtGraphicsView * v)
 :IrrlichtGraphicsScene(v)
 ,mouseLook(false)
 ,rotH(0)
 ,rotV(0)
 ,movementSpeed(0.3)
 ,rotationSpeed(0.2)
 ,cameraToAvatarOffset(0,70,-50)
 ,cameraTargetToAvatarOffset(0,70,0)
 ,cameraAngleH(0)
 ,cameraAngleV(0){
}

void Scene::initializeIrrlichtScene(){

	device->getFileSystem()->addZipFileArchive("../resources/sl/test/map-20kdm2.pk3");
	scene::IAnimatedMesh* mesh = scene->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;
	if (mesh)
		node = scene->addOctTreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	if (node)
		node->setPosition(core::vector3df(-1300,-144,-1249));


	avatar= scene->addAnimatedMeshSceneNode(scene->getMesh( "../resources/sl/avatar/ninja.b3d" ));
	if(avatar){
		avatar->setFrameLoop(0, 14);
		avatar->setAnimationSpeed(15);
		avatar->setMD2Animation(scene::EMAT_RUN);

		avatar->setScale(core::vector3df(6.f,6.f,6.f));
		avatar->setPosition(core::vector3df(0,-50,0));
		avatar->setRotation(core::vector3df(0,-90,0));

		avatar->setAnimationSpeed(10.f);
		avatar->getMaterial(0).NormalizeNormals = true;
		avatar->getMaterial(0).Lighting = false;
	}


	camera=scene->addCameraSceneNode();
	camera->bindTargetAndRotation(true);
	move=1; updateIrrlichtScene();

	frameTime.start();
}



void Scene::updateIrrlichtScene(){

	int frameDeltaTime=frameTime.elapsed();
	frameTime.restart();

	if(pressedKeys[Qt::Key_Up]||pressedKeys[Qt::Key_W]){
			move+=movementSpeed*frameDeltaTime;
	}
	if(pressedKeys[Qt::Key_Down]||pressedKeys[Qt::Key_S]){
			move-=movementSpeed*frameDeltaTime;
	}
	if(pressedKeys[Qt::Key_Left]||pressedKeys[Qt::Key_A]){
			rotH-=rotationSpeed*frameDeltaTime;
	}
	if(pressedKeys[Qt::Key_Right]||pressedKeys[Qt::Key_D]){
			rotH+=rotationSpeed*frameDeltaTime;
	}

	updateAvatarPosition();
	updateCamera();

	move=0;
	slide=0;
	rotH=0;
	rotV=0;
}

void Scene::mouseMoveEvent ( QGraphicsSceneMouseEvent * e ){
    IrrlichtGraphicsScene::mouseMoveEvent(e);
    if (e->isAccepted())
        return;

    if(mouseLook){
        QPointF d=mousePos-(QPointF(e->pos()));
        QCursor::setPos(mousePos);
        rotH-=d.x()*rotationSpeed;
        rotV-=d.y()*rotationSpeed;
    }
}

void Scene::wheelEvent ( QGraphicsSceneWheelEvent * event){
	core::vector3df nodePosition = camera->getPosition();
	nodePosition.X += (event->delta() / 8 / 15);
	camera->setPosition(nodePosition);
}

void Scene::focusInEvent ( QFocusEvent *  ){
	if(mouseLook){
		mousePos=QCursor::pos();
		view->setCursor( QCursor( Qt::BlankCursor ) );
		view->grabMouse();
        //		activeWindow ()->setMouseTracking(true);
	}
}

void Scene::focusOutEvent ( QFocusEvent *  ){
	if(mouseLook){
		QCursor::setPos(mousePos);
		view->setCursor( QCursor( Qt::ArrowCursor ) );
		view->releaseMouse();
        //		setMouseTracking(false);
	}
}

void Scene::keyPressEvent ( QKeyEvent * event ){
    if (focusItem()){
        IrrlichtGraphicsScene::keyPressEvent(event);
        return;
    }
	pressedKeys[event->key()]=true;
	event->accept();
}


void Scene::keyReleaseEvent ( QKeyEvent * event ){
    if (focusItem()){
        IrrlichtGraphicsScene::keyReleaseEvent(event);
        return;
    }
	pressedKeys[event->key()]=false;
	event->accept();
}


void Scene::updateAvatarPosition(){
	if(slide || move){

		//removeme move animation demo.
		static int i=0;
		i+=abs(move);
		if(i>(13*10))
			i=0;
		avatar->setCurrentFrame (i/10);

		irr::core::matrix4 mat = camera->getRelativeTransformation();
		irr::core::vector3df slideVec(slide,0,0);
		irr::core::vector3df moveVec(0,0,move);
		mat.rotateVect(slideVec);
		mat.rotateVect(moveVec);
		avatar->setPosition( avatar->getPosition() + slideVec + moveVec );
		setDirty();
	}
}


void Scene::updateCamera()
{
	if(slide || move || rotH || rotV){
		cameraAngleH+=rotH;
		while(cameraAngleH>360)
			cameraAngleH-=360;
		while(cameraAngleH<0)
			cameraAngleH+=360;

		cameraAngleV+=rotV;
		avatar->setRotation(irr::core::vector3df(0,cameraAngleH,0));
		irr::core::vector3df camof=( cameraToAvatarOffset);
		camof.rotateXZBy(-cameraAngleH);
		camera->setPosition(avatar->getPosition() +camof);
		camera->setTarget(avatar->getPosition() + cameraTargetToAvatarOffset);
		setDirty();
	}



}


