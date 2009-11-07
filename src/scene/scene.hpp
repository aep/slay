#include "IrrlichtGraphicsScene.hpp"
#include <QPointF>
#include <QHash>
#include <QTime>
#include <QCursor>

class Scene :public IrrlichtGraphicsScene{
    Q_OBJECT;

public:
    Scene(IrrlichtGraphicsView * v);

protected:
    virtual void initializeIrrlichtScene();
    virtual void updateIrrlichtScene();

    virtual void mouseMoveEvent  ( QGraphicsSceneMouseEvent * event );
    virtual void wheelEvent      ( QGraphicsSceneWheelEvent * event );
    virtual void focusInEvent    ( QFocusEvent * event );
    virtual void focusOutEvent   ( QFocusEvent * event );
    virtual void keyPressEvent   ( QKeyEvent * event );
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
