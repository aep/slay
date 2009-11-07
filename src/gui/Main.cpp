#include <QApplication> 
#include "MainWindow.hpp"
#include <irrlicht.h> 


using namespace irr; 

int main(int argc, char **argv) 
{    
    QApplication    app(argc, argv); 
    
    MainWindow      win;
    win.show();


    return app.exec(); 
} 
