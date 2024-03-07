/*
This class is responsible for showing the interface of the drawing tool for primitives and for containing the current drawing data.
*/

#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "renderer.h"

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

	PrimitiveType currentPrimitiveType;
	PrimitiveCreationData* creationData;

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

	PrimitiveCreationData* getPrimitiveCreationData();

	bool isDrawModeActive() const;
	ofColor getBackgroundColor();
	ofColor getOutlineColor();
	ofColor getFillColor();
	float getOutlineWidth();
	PrimitiveType getCurrentPrimitiveType();
    ofxBaseGui * getUi();
};
