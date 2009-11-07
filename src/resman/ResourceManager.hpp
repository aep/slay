#ifndef SLVIEW_RESOURCEMANAGERYD_GUARD
#define SLVIEW_RESOURCEMANAGERYD_GUARD

#include <irrlicht.h>

namespace SlView{
    class MainScene;
    class ResourceManager {
    public:
        ResourceManager(MainScene * );

        irr::video::ITexture      * getStaticTexture (const char * name);
        irr::scene::IAnimatedMesh * getStaticMesh    (const char * name);
    protected:
	    MainScene * scene;
    };
}
#endif

