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

    float mainCam[4];
    float cameraTop[4];
    float cameraDroit[4];
    float cameraGauche[4];
private:
    Cursor cursor;
    DrawingTool drawingTool;
    Renderer renderer;
    Interface interface;

    Mode mode;
    bool mode_change;
    ofEasyCam camera;
    ofEasyCam camTop;
    ofEasyCam camDroit;
    ofEasyCam camGauche;
    ofVec2f lastMouse;
    ofVec3f rotationPoint;

    int choix_de_cam;
    int choisirCamABouger(int x, int y);
};
