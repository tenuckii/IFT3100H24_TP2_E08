#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "drawingTool.h"
#include "renderer.h"
#include "cursor.h"
#include "ImageExpImp.h"
#include "interface.h"
#include "Primitive3D.h"

class Application : public ofBaseApp
{

public:
    ImageExpImp imageExpImp;

    Geometrie geometrie3D;
    
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    Cursor cursor;
    DrawingTool drawingTool;
    Renderer renderer;
    Interface interface;

    Mode mode;
    bool mode_change;
};
