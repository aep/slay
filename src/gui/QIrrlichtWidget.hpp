#ifndef QIRRLICHTWIDGET_H 
#define QIRRLICHTWIDGET_H 

#include <QGLWidget>
#include <irrlicht.h> 


class QPaintEvent; 

class QIrrlichtWidget : public QGLWidget { 

    Q_OBJECT 
    public:    
        QIrrlichtWidget( QWidget *parent=0 );
        ~QIrrlichtWidget();
        irr::IrrlichtDevice         * device;
        irr::scene::ISceneManager   * scene;
        irr::video::IVideoDriver    * driver;

    protected: 
	    virtual void initializeGL();
        virtual void paintGL( ); 
        virtual void timerEvent ( QTimerEvent * event );
        virtual void resizeGL(int w, int h);
        virtual void initializeScene()=0;
	    virtual void updateScene()=0;
        
        void setDirty();

    private:
        bool m_dirty;
    
}; 

#endif
