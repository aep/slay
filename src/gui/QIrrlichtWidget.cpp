#include <QMetaType>
#include "QIrrlichtWidget.hpp" 
#include <irrlicht.h> 

using namespace irr; 
using namespace core; 
using namespace scene; 
using namespace video; 
using namespace io; 
using namespace gui; 

QIrrlichtWidget::QIrrlichtWidget( QWidget *parent ) 
    : QGLWidget(parent)
    , device(0) 
    , m_dirty(false)
{



}    

QIrrlichtWidget::~QIrrlichtWidget() { 
    if(device){
        device->closeDevice(); 
        device->run(); 
        device->drop(); 
    }
} 

void QIrrlichtWidget::initializeGL(){


    if(!device){
        SIrrlichtCreationParameters createParams;
        createParams.DriverType = irr::video::EDT_OPENGL;
        createParams.IgnoreInput = true;
	    createParams.WindowId = ( void * ) winId();
        device = createDeviceEx( createParams );

        if(!device){
            qFatal("failed to initialise irrlicht");
            return;
        }

        driver= device->getVideoDriver();
        scene= device->getSceneManager();

        initializeScene();
	    startTimer(60);
    }

}


void QIrrlichtWidget::paintGL() {
    setDirty();
} 


void QIrrlichtWidget::timerEvent ( QTimerEvent * event ){
    if(!device)
        return;

    updateScene();

    if(!m_dirty)
        return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    driver->beginScene( true, false, SColor( 255, 128, 128, 128 ));
    scene->drawAll();
    driver->endScene();
    m_dirty=false;
}


void QIrrlichtWidget::resizeGL(int w, int h){
    if(!device)
        return;

    glViewport(0, 0, (GLint)w, (GLint)h);

    irr::core::dimension2d<uint> size; 
    size.Width = w;
    size.Height = h;
    device->getVideoDriver()->OnResize(size); 
        
    /*
    irr::scene::ICameraSceneNode *cam = device->getSceneManager()->getActiveCamera(); 
    if ( cam != 0 ){
        cam->setAspectRatio( (h/(double)w) ); 
    }
    */
}



void QIrrlichtWidget::setDirty(){
    m_dirty=true;
}



/*
struct SIrrlichtKey 
{ 
    irr::EKEY_CODE code; 
    wchar_t ch; 
}; 

SIrrlichtKey convertToIrrlichtKey( int key ) 
{ 
    SIrrlichtKey irrKey; 
    irrKey.code = (irr::EKEY_CODE)(0); 
    irrKey.ch = (wchar_t)(0); 
    
    // Letters A..Z and numbers 0..9 are mapped directly 
    if ( (key >= Qt::Key_A && key <= Qt::Key_Z) || (key >= Qt::Key_0 && key <= Qt::Key_9) ) 
    { 
        irrKey.code = (irr::EKEY_CODE)( key ); 
        irrKey.ch = (wchar_t)( key ); 
    } 
    else 
    
    // Dang, map keys individually 
    switch( key ) 
    { 
    case Qt::Key_Up: 
        irrKey.code = irr::KEY_UP; 
        break; 
        
    case Qt::Key_Down: 
        irrKey.code = irr::KEY_DOWN; 
        break; 
        
    case Qt::Key_Left: 
        irrKey.code = irr::KEY_LEFT; 
        break; 
        
    case Qt::Key_Right: 
        irrKey.code = irr::KEY_RIGHT; 
        break; 
    } 
    return irrKey; 
} 

void QIrrlichtWidget::sendKeyEventToIrrlicht( QKeyEvent* event, bool pressedDown ) 
{ 
    irr::SEvent irrEvent; 
    
    irrEvent.EventType = irr::EET_KEY_INPUT_EVENT; 
    
    SIrrlichtKey irrKey = convertToIrrlichtKey( event->key() ); 
    
    if ( irrKey.code == 0 ) return; // Could not find a match for this key 
    
    irrEvent.KeyInput.Key = irrKey.code; 
    irrEvent.KeyInput.Control = ((event->modifiers() & Qt::ControlModifier) != 0); 
    irrEvent.KeyInput.Shift = ((event->modifiers() & Qt::ShiftModifier) != 0); 
    irrEvent.KeyInput.Char = irrKey.ch; 
    irrEvent.KeyInput.PressedDown = pressedDown; 
    
    device->postEventFromUser( irrEvent ); 
} 

void QIrrlichtWidget::keyPressEvent( QKeyEvent* event ) 
{ 
    if ( device != 0 ) 
    { 
        sendKeyEventToIrrlicht( event, true ); 
    } 
    event->ignore(); 
} 

void QIrrlichtWidget::keyReleaseEvent( QKeyEvent* event ) 
{ 
    if ( device != 0 ) 
    { 
        sendKeyEventToIrrlicht( event, false ); 
    } 
    event->ignore(); 
} 

void QIrrlichtWidget::sendMouseEventToIrrlicht( QMouseEvent* event, bool pressedDown ) 
{ 
    irr::SEvent irrEvent; 
    
    irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT; 
    
    switch ( event->button() ) 
    { 
    case Qt::LeftButton: 
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_LMOUSE_PRESSED_DOWN:irr::EMIE_LMOUSE_LEFT_UP; 
        break; 
    
    case Qt::MidButton: 
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_MMOUSE_PRESSED_DOWN:irr::EMIE_MMOUSE_LEFT_UP; 
        break; 
    
    case Qt::RightButton: 
        irrEvent.MouseInput.Event = pressedDown? irr::EMIE_RMOUSE_PRESSED_DOWN:irr::EMIE_RMOUSE_LEFT_UP; 
        break; 
    
    default: 
        return; // Cannot handle this mouse event 
    } 
    
    irrEvent.MouseInput.X = event->x(); 
    irrEvent.MouseInput.Y = event->y(); 
    irrEvent.MouseInput.Wheel = 0.0f; // Zero is better than undefined 
    
    device->postEventFromUser( irrEvent ); 
} 

void QIrrlichtWidget::mousePressEvent( QMouseEvent* event ) 
{ 
    if ( device != 0 ) 
    { 
        sendMouseEventToIrrlicht( event, true ); 
    } 
    event->ignore(); 
} 

void QIrrlichtWidget::mouseReleaseEvent( QMouseEvent* event ) 
{ 
    if ( device != 0 ) 
    { 
        sendMouseEventToIrrlicht( event, false ); 
    } 
    event->ignore(); 
} 

void QIrrlichtWidget::wheelEvent( QWheelEvent* event ) 
{ 
    if ( device != 0 && event->orientation() == Qt::Vertical ) 
    { 
        irr::SEvent irrEvent; 
        
        irrEvent.EventType = irr::EET_MOUSE_INPUT_EVENT; 
        
        irrEvent.MouseInput.Event = irr::EMIE_MOUSE_WHEEL; 
        irrEvent.MouseInput.X = 0; // We don't know these, 
        irrEvent.MouseInput.Y = 0; // but better zero them instead of letting them be undefined 
        irrEvent.MouseInput.Wheel = event->delta() / 120.0f; 
        
        device->postEventFromUser( irrEvent ); 
    } 
    event->ignore(); 
} 


*/









