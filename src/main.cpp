#include "ofMain.h"
#include "Application.h"

//========================================================================
int main()
{

    // Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
    //  ofGLWindowSettings settings;
    //  settings.setSize(1024, 768);
    //  settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN

    // auto window = ofCreateWindow(settings);

    // ofRunApp(window, make_shared<Application>());
    // ofRunMainLoop();

    ofSetupOpenGL(512, 512, OF_WINDOW);
    ofRunApp(new Application());
}
