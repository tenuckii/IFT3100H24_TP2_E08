/*
This class is responsible for showing the interface of the drawing tool for primitives and for containing the current drawing data.
*/

#pragma once

#include "ofxGui.h"
#include "ofMain.h"

enum class PrimitiveType {
	NONE,
	LINE,
	RECTANGLE,
	TRIANGLE,
	CIRCLE,
	ELLIPSE,
	HOUSE,
	SUN
};

enum class CommandType {
	CREATE, 
	UNDO, 
	REDO, 
	CLEAR
};

struct Primitive {
	PrimitiveType type;
	float start_pos[2];
	float end_pos[2];
	float outline_width;
	unsigned char outline_color[4];
	unsigned char fill_color[4];
};

struct DrawingToolStatus {
	bool is_active;
	CommandType commandType;
	ofColor background_color;
	ofColor outline_color;
	ofColor fill_color;
	float outline_width;
	PrimitiveType primitiveType;
};

class DrawingTool {

private:
	// UI Elements
	ofxPanel gui;

	ofParameter<ofColor> color_picker_background;
	ofParameter<ofColor> color_picker_shape_fill;
	ofParameter<ofColor> color_picker_shape_outline;

	ofParameter<float> slider_stroke_weight;

	ofxButton line_button;
	ofxButton rectangle_button;
	ofxButton triangle_button;
	ofxButton circle_button;
	ofxButton ellipse_button;

	ofxButton house_button;
	ofxButton sun_button;
	ofxButton undo_button;
	ofxButton redo_button;
	ofxButton clear_button;

	CommandType currentCommandType;

	PrimitiveType currentPrimitiveType;
	DrawingToolStatus* drawingToolStatus;

	bool show_menu;

public:
	void setup();
	void exit();
	void draw();

	void showHideMenu();

	void setLineType();
	void setRectangleType();
	void setTriangleType();
	void setCircleType();
	void setEllipseType();
	void setHouseType();
	void setSunType();

	void undo();
	void redo();
	void clear();

	DrawingToolStatus* getDrawingToolStatus();

	bool isDrawModeActive() const;
	ofColor getBackgroundColor();
	ofColor getOutlineColor();
	ofColor getFillColor();
	float getOutlineWidth();
	PrimitiveType getCurrentPrimitiveType();
    ofxBaseGui * getUi();

	~DrawingTool();
};
