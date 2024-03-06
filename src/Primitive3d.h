#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

enum TypePrimitive3d
{
	Sphere,
	cube,
};
struct Primitive3d
{
	float x;
	float y;
	float z;

	float rayon;

	ofColor color;
	TypePrimitive3d type3d;
};

class Geometrie
{
public:
	vector<Primitive3d> primitive_geometrique;
	vector<Primitive3d> redo;

	ofParameter<float> PositionX;
	ofParameter<float> PositionY;
	ofParameter<float> PositionZ;
	ofParameter<float> Rayon;
	ofParameter<ofColor> couleur;
	ofxButton sphere_button;
	ofxButton cube_button;

	ofxButton undo_button;
	ofxButton redo_button;
	ofxButton clear_button;

	bool gui3d_afficher = false;

	ofxPanel Gui3d;

	ofxGuiGroup primitive3d;

	void ajouter_une_primitive_3d(TypePrimitive3d type3d);
	void draw();
	void setup();
	void Gui3d_Setup();


	void sphere_button_presse();
	void cube_button_presse();
	void undo_button_presse();
	void redo_button_presse();
	void clear_button_presse();

	void undo();
	void redo3d();
	void clear();


	void Draw_cube(ofColor p_color, ofVec3f position, float rayon) const;
	void Draw_sphere(ofColor p_color, ofVec3f position, float raton) const;


};
