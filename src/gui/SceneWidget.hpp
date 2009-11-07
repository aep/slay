#include "QIrrlichtWidget.hpp" 
#include "MainScene.hpp"
#include <QPointF>
#include <QHash>
#include <QTime>
#include <QCursor>

class SceneWidget :public QIrrlichtWidget{
    Q_OBJECT

    public:
        SceneWidget(QWidget *parent = 0);

    protected:
        virtual void initializeScene();
	    virtual void updateScene();
        virtual void mouseMoveEvent ( QMouseEvent * event );
        virtual void wheelEvent ( QWheelEvent * event );
        virtual void focusInEvent ( QFocusEvent * event );
        virtual void focusOutEvent ( QFocusEvent * event );
        virtual void keyPressEvent ( QKeyEvent * event );
        virtual void keyReleaseEvent ( QKeyEvent * event );

        void updateAvatarPosition();
        void updateCamera();
    private:

        //config
        const double movementSpeed;
        const double rotationSpeed;
        const irr::core::vector3df cameraTargetToAvatarOffset;
        const irr::core::vector3df cameraToAvatarOffset;

        //stuff in the scene
        irr::scene::ICameraSceneNode * camera;
        irr::scene::IAnimatedMeshSceneNode   * avatar;

        //messure the render time
        QTime frameTime;

        //currently pressed keys
        QHash<int,bool> pressedKeys;

        //mouse pos before grabbed
        QPoint mousePos;
        bool mouseLook;

        //mouse rotation since last update
        double rotH;
        double rotV;

        //avatar movement since last update
        double slide;
    	double move;

        //current camera angle
        int cameraAngleH;
        int cameraAngleV;

};
