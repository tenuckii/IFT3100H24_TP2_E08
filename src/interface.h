#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "drawingTool.h"
#include "cursor.h"
#include "ImageExpImp.h"
#include "interface.h"
#include "Primitive3D.h"

typedef enum Mode
{
    VIEW_2D,
    VIEW_3D
} Mode;

class Interface
{
public:
    void setup(Cursor *_cursor, DrawingTool *dt, ImageExpImp *iie, Geometrie * g3d);
    void draw(Mode mode, bool& mode_change);
    void exit();

private:
    ofxPanel gui;
    ofxButton cursor_btn;
    ofxButton drawing_tool_btn;
    ofxButton image_import_export_btn;

    Cursor *cursor;
    DrawingTool *drawing_tool;
    ImageExpImp *image_import_export;
    Geometrie * Geometrie3D;

    void cursor_open_close_ui();
    void drawing_tool_open_close_ui();
    void image_import_export_open_close_ui();
};