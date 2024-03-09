#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

struct image_struct
{

	float x1;
	float y1;

	float x2;
	float y2;


	float radius;
	float height;
	float width;

	ofImage image;
};
class ImageExpImp
{
private : 
	std::vector<image_struct> vecImage;

	int radius;

	bool zoneExportingInProgress;
	bool exportOnMouseRelease;

	ofImage img;
	ofxPanel importeGui;

	ofParameter<int> img_start_x;
	ofParameter<int> img_start_y;
	ofParameter<int> img_end_x;
	ofParameter<int> img_end_y;

	ofxButton import;
	ofxButton exporte;
	ofxButton exportPartie;
	ofxButton echantillon;

	ofxGuiGroup import_img;
	ofxGuiGroup export_img;
public:

	bool is_mouse_button_pressed;

	int mouse_press_x;
	int mouse_press_y;

	int mouse_current_x;
	int mouse_current_y;
	
	void setup();
	void update();
	void draw();

	void draw_zone(float x1, float y1, float x2, float y2) const;

	void export_image();
	void image_import();

	void GUI_image_setup();
	void import_button_pressed();
	void exporte_button_pressed();
	void exportPartie_button_pressed();
	void importBroke_button_pressed();
	ofImage scambler(ofImage image);
	

    ofxBaseGui * getUi();

};