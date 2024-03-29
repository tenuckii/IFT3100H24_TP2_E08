#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

enum TypePrimitive3d
{
	Sphere,
	cube,
	dino,
	human,
	f1,
};
struct Primitive3d
{
	float x;
	float y;
	float z;

	float rayon;

	float angle;

	float scaleX;
	float scaleY;
	float scaleZ;

	float rotationx;
	float rotationy;
	float rotationz;

	int index = 0;
	bool selctionner = false;


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

	ofParameter<float> Angle;

	ofParameter<float> Rayon;

	ofParameter<ofColor> couleur;


	ofxButton sphere_button;
	ofxButton cube_button;

	ofxButton undo_button;
	ofxButton redo_button;
	ofxButton clear_button;

	ofxButton Add_Human;
	ofxButton Add_Dino;
	ofxButton Add_F1;

	ofxToggle rationX;
	ofxToggle rationY;
	ofxToggle rationZ;

	ofParameter<float> ScaleX;
	ofParameter<float> ScaleY;
	ofParameter<float> ScaleZ;

	ofParameter<int> Index_selection;
	ofxButton selection;
	glm::vec3 regarde_un_objet;


	ofParameter<int> nb_cam2;

	bool gui3d_afficher = false;

	int Index = -1;
	int autreIndex = 0;

	ofxPanel Gui3d;

	ofxGuiGroup primitive3d;
	ofxGuiGroup Model3D;
	ofxGuiGroup Camera;

	ofLight light;

	float rotationX = 0.0f;
	float rotationY = 1.0f;
	float rotationZ = 0.0f;

	void ajouter_une_primitive_3d(TypePrimitive3d type3d);
	void draw();
	void setup();
	void Gui3d_Setup();


	void sphere_button_presse();
	void cube_button_presse();

	void Human_button_presse();
	void Dino_button_presse();
	void F1_button_presse();

	void undo_button_presse();
	void redo_button_presse();
	void clear_button_presse();

	void selectionner_button();

	void RationX_button_presse(bool& value);
	void RationY_button_presse(bool& value);
	void RationZ_button_presse(bool& value);

	void undo();
	void redo3d();
	void clear();


	void Draw_cube(ofColor p_color, ofVec3f position, float width, float height, float depth) const;
	void Draw_sphere(ofColor p_color, ofVec3f position, float rayon) const;
	void Draw_Modele(float angle, ofVec3f position, ofxAssimpModelLoader &model, float rotax, float rotay, float roatz, float scalex, float scaley, float scalez) const;
	void Draw_Modele_slectionner(ofVec3f position, ofxAssimpModelLoader& model, int index);

	void Draw_primitive_slectionner(ofVec3f position, int index, TypePrimitive3d type);


	//modele 3d
	ofxAssimpModelLoader Human;
	ofxAssimpModelLoader Dino;
	ofxAssimpModelLoader F1;

    ofxBaseGui * getUi();
};
