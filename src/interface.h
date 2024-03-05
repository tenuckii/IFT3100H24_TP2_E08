#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "Cursor.h"

class Interface
{
public:
    void setup(Cursor& cursor);
    void draw();

private:

	// void circleResolutionChanged(int & circleResolution);
	// void ringButtonPressed();
    ofxPanel gui;
	bool bHide;
    ofxColorSlider color;
    // ofxIntSlider crosshairCircleResolution;

    // unsigned int r,g,b,a;

    // ofxFloatSlider radius;
    // ofxVec2Slider center;
    // ofxIntSlider circleResolution;
    // ofxToggle filled;
    // ofxButton twoCircles;
    // ofxButton ringButton;
    // ofxLabel screenSize;

	// ofSoundPlayer ring;
};