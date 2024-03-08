#include "ofMain.h"
#include "application.h"

//========================================================================
int main( ){

	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.setGLVersion(3,3);

	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<Application>());
	ofRunMainLoop();

}
