#include "interface.h"

void Interface::setup(Cursor &cursor)
{
    gui.setup(); // most of the time you don't need a name
    gui.add(color.setup("Crosshair Color", cursor.get_color(), ofColor(0, 0), ofColor(255, 255)));
    // g = a = 255;
    // gui.add(radius.setup("radius", 140, 10, 300));
    // gui.add(center.setup("center", {ofGetWidth() * .5, ofGetHeight() * .5}, {0, 0}, {ofGetWidth(), ofGetHeight()}));
    // gui.add(circleResolution.setup("circle res", 5, 3, 90));
    // gui.add(twoCircles.setup("two circles"));
    // gui.add(ringButton.setup("ring"));
    // gui.add(screenSize.setup("screen size", ofToString(ofGetWidth()) + "x" + ofToString(ofGetHeight())));

    // bHide = false;
}

void Interface::draw()
{
    if (!bHide)
    {
        
        gui.draw();
    }
}
