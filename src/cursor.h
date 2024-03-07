#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Cursor
{
public:
    void setup();
    void draw();
    void exit();
    void set_position(unsigned int x, unsigned int y);
    void open_close_ui();
    ofxPanel getUIComponent();
	bool hide_ui;

private:
    typedef enum CursorType
    {
        CROSSHAIR,
        T_CROSSHAIR,
        ROUND_CROSSHAIR,
        DOT_CROSSHAIR,
        ARROW_CROSSHAIR,
    } CursoType;

    typedef struct Position
    {
        unsigned int x, y;
    } Position;

    Position position;
    CursorType cursor_type;
    float gap;
    float length;
    unsigned int size;
    ofColor color;

    //ui
    ofxPanel gui;
    ofParameter<ofColor> color_slider;
    ofParameter<float> change_gap;
    ofParameter<float> change_length;
    ofParameter<unsigned int> change_size;

    ofxButton crosshair_btn;
	ofxButton t_crosshair_btn;
	ofxButton dot_crosshair_btn;
	ofxButton round_crosshair_btn;
	ofxButton arrow_crosshair_btn;

    void crosshair();
    void t_crosshair();
    void round_crosshair();
    void dot_crosshair();
    void arrow_crosshair();
    
    void set_cursor_crosshair();
    void set_cursor_t_crosshair();
    void set_cursor_round_crosshair();
    void set_cursor_dot_crosshair();
    void set_cursor_arrow_crosshair();
};