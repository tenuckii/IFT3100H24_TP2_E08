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
public:
	std::vector<image_struct> vecImage;

	ofImage img;
	ofxPanel importeGui;

	bool gui_image = false;
	 
	int mouse_press_x;
	int mouse_press_y;

	int mouse_current_x;
	int mouse_current_y;

	int radius;

	void setup();
	void update();
	void draw();

	void draw_zone(float x1, float y1, float x2, float y2) const;

	void export_image();
	void image_import();

	//gui image
	void GUI_image_setup();
	void import_button_pressed();
	void exporte_button_pressed();
	void exportPartie_button_pressed();

    void show_hide_ui();

	bool is_mouse_button_pressed;
	

	ofParameter<int> img_start_x;
	ofParameter<int> img_start_y;
	ofParameter<int> img_end_x;
	ofParameter<int> img_end_y;
	ofParameter<string> fileName;

	ofxButton import;
	ofxButton exporte;
	ofxButton exportPartie;

	ofxGuiGroup import_img;
	ofxGuiGroup export_img;
	

    ofxBaseGui * getUi();

};