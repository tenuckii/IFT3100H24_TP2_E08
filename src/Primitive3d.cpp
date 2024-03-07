#include "Primitive3D.h"

void Geometrie::ajouter_une_primitive_3d(TypePrimitive3d type3d)
{
	Primitive3d primitive3d;

	primitive3d.type3d = type3d;

	primitive3d.x = ofGetWindowWidth() / 2 + PositionX;
	primitive3d.y = ofGetWindowWidth() / 2 + PositionY;
	primitive3d.z = -PositionZ;

	primitive3d.rayon = Rayon;
	primitive3d.color = couleur;


	primitive_geometrique.push_back(primitive3d);
	redo.clear();
}

void Geometrie::setup()
{
	Gui3d_Setup();
}
	
void Geometrie::draw() {

	

	for (int i = 0; i < primitive_geometrique.size(); i++) {
		
		ofVec3f position(primitive_geometrique[i].x, primitive_geometrique[i].y, primitive_geometrique[i].z);

		switch (primitive_geometrique[i].type3d)
		{
		case TypePrimitive3d::Sphere:
			Draw_sphere(primitive_geometrique[i].color, position, primitive_geometrique[i].rayon);
			break;

		case TypePrimitive3d::cube:
			Draw_cube(primitive_geometrique[i].color, position, primitive_geometrique[i].rayon);
			break;
		}
	}
	
	if (gui3d_afficher)
	{
		Gui3d.draw();
	}
}



void Geometrie::Gui3d_Setup()
{
	

	Gui3d.setup("3D");

	Gui3d.setDefaultWidth(270);
	Gui3d.setDefaultHeight(20);
	Gui3d.setSize(270, 200);


	primitive3d.setup("Primitive3D");

	PositionX.set("x position", 0, -ofGetWindowWidth()/2, ofGetWindowWidth()/2);
	PositionY.set("y position", 0, -ofGetWindowHeight() / 2, ofGetWindowHeight()/2);
	PositionZ.set("z position", 0, 0, 1000);
	Rayon.set("Rayon", 100, 0, 1000); 
	couleur.set("couleur du trait", ofColor(255), ofColor(0, 0), ofColor(255, 255));

	sphere_button.setup("Sphere");
	sphere_button.addListener(this, &Geometrie::sphere_button_presse);
	

	cube_button.setup("Cube");
	cube_button.addListener(this, &Geometrie::cube_button_presse);

	undo_button.setup("undo");
	undo_button.addListener(this, &Geometrie::undo_button_presse);

	redo_button.setup("redo");
	redo_button.addListener(this, &Geometrie::redo_button_presse);

	clear_button.setup("Clear");
	clear_button.addListener(this, &Geometrie::clear_button_presse);
	

	primitive3d.add(PositionX);
	primitive3d.add(PositionY);
	primitive3d.add(PositionZ);
	primitive3d.add(Rayon);
	primitive3d.add(couleur);

	primitive3d.add(&cube_button);
	primitive3d.add(&sphere_button);
	primitive3d.add(&undo_button);
	primitive3d.add(&redo_button);
	primitive3d.add(&clear_button);

	Gui3d.add(&primitive3d);



}

void Geometrie::sphere_button_presse()
{
	ajouter_une_primitive_3d(Sphere);
}

void Geometrie::cube_button_presse()
{
	ajouter_une_primitive_3d(cube);
}

void Geometrie::undo_button_presse()
{
	undo();
}

void Geometrie::redo_button_presse()
{
	redo3d();
}

void Geometrie::clear_button_presse()
{
	clear();
}

void Geometrie::undo()
{
	if (!primitive_geometrique.empty())
	{
		Primitive3d undoPrimitive = primitive_geometrique.back();
		primitive_geometrique.pop_back();
		redo.push_back(undoPrimitive);
	}
}

void Geometrie::redo3d()
{
	if (!redo.empty())
	{
		Primitive3d redoPrimitive = redo.back();
		redo.pop_back();
		primitive_geometrique.push_back(redoPrimitive);
	}

}

void Geometrie::clear()
{
	primitive_geometrique.clear();
	
}

void Geometrie::Draw_cube(ofColor p_color, ofVec3f position, float rayon) const
{
	ofNoFill();
	ofSetColor(p_color);
	ofDrawBox(position, rayon);
}

void Geometrie::Draw_sphere(ofColor p_color, ofVec3f position, float rayon) const
{
	ofNoFill();
	ofSetColor(p_color);
	ofDrawSphere(position, rayon);
}



ofxBaseGui * Geometrie::getUi(){
    return &Gui3d;
}