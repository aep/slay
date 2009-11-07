#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "resourcemanager.hpp"
#include "mainscene.hpp"
#include "appconf.hpp"


using namespace SlView;

static std::string magicstring(MAGICUNPACKSTRING);

ResourceManager::ResourceManager(MainScene * m):scene(m){

    std::cerr<<"loading static resources"<<std::endl;

    std::string realmagicstring="real_"+magicstring;

    std::ifstream app;
    app.open (AppConf::argv[0],std::ios::ate|std::ios::in|std::ios::binary);
	if (!app.is_open()) {
        std::cerr<<"cannot open binary to unpack static resources"<<std::endl;
        return;
    }
    app.seekg(-1,std::ios_base::end);
    int msOffset=realmagicstring.length();
    char * dt=new char;
    while(app.tellg()>0){
        if(app.peek()==realmagicstring[msOffset]){
            msOffset--;
            if(msOffset<0){
                break;
            }
        }else{
            msOffset=0;
        }
        app.seekg(-1,std::ios_base::cur);
    }

    if(app.eof()){
        std::cerr<<"no static resources found to unpack in binary"<<std::endl;
        app.close();
        return;
    }
    std::cerr<<"found static resources at "<<app.tellg()<<std::endl;
    app.close();
}     


irr::video::ITexture      * ResourceManager::getStaticTexture (const char * name){
    std::string n="../resources/"+std::string(name);
    return scene->driver->getTexture(n.c_str());
}

irr::scene::IAnimatedMesh * ResourceManager::getStaticMesh    (const char * name){
    return 0;
}
