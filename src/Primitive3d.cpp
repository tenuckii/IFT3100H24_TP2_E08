#include "Primitive3D.h"

void Geometrie::ajouter_une_primitive_3d(TypePrimitive3d type3d)
{
	Primitive3d primitive3d;
	Index++;
	primitive3d.index = Index;

	primitive3d.type3d = type3d;

	primitive3d.x = ofGetWindowWidth() / 2 + PositionX;
	primitive3d.y = ofGetWindowHeight() / 2 + PositionY;
	primitive3d.z = -PositionZ;

	primitive3d.rayon = Rayon;

	primitive3d.angle = Angle;

	primitive3d.color = couleur;

	primitive3d.scaleX = ScaleX;
	primitive3d.scaleY = ScaleY;
	primitive3d.scaleZ = ScaleZ;

	primitive3d.rotationx = rotationX;
	primitive3d.rotationy = rotationY;
	primitive3d.rotationz = rotationZ;

	primitive_geometrique.push_back(primitive3d);
	redo.clear();



	Index_selection.set("Index", Index_selection, 0, Index);

}

void Geometrie::setup()
{
	Gui3d_Setup();
}
	
void Geometrie::draw() {

	ofEnableLighting();
	
	light.setAmbientColor(ofColor(255, 255, 255));
	light.setDiffuseColor(ofColor(0, 0, 0));
	light.setPosition(ofGetWindowWidth() / 2, 0.0f, 1000.0f);
	light.enable();

	for (int i = 0; i < primitive_geometrique.size(); i++) {
		
		ofVec3f position(primitive_geometrique[i].x, primitive_geometrique[i].y, primitive_geometrique[i].z);

		switch (primitive_geometrique[i].type3d)
		{
		case TypePrimitive3d::Sphere:
			Draw_sphere(primitive_geometrique[i].color, position, primitive_geometrique[i].rayon);

			if (primitive_geometrique[i].selctionner)
			{
				Draw_primitive_slectionner(position,i,Sphere);
			}
			break;

		case TypePrimitive3d::cube:
			Draw_cube(primitive_geometrique[i].color, position, primitive_geometrique[i].scaleX * 100, primitive_geometrique[i].scaleY * 100, primitive_geometrique[i].scaleZ * 100);
			if (primitive_geometrique[i].selctionner)
			{
				Draw_primitive_slectionner(position, i, cube);
			}
			break;
		
			
		case TypePrimitive3d::human:
			Draw_Modele(primitive_geometrique[i].angle, position, Human, primitive_geometrique[i].rotationx, primitive_geometrique[i].rotationy, primitive_geometrique[i].rotationz, primitive_geometrique[i].scaleX, primitive_geometrique[i].scaleY, primitive_geometrique[i].scaleZ);
			if (primitive_geometrique[i].selctionner)
			{
				Draw_Modele_slectionner(position, Human, i);
			}
			break;

		case TypePrimitive3d::dino:
			Draw_Modele(primitive_geometrique[i].angle, position, Dino, primitive_geometrique[i].rotationx, primitive_geometrique[i].rotationy, primitive_geometrique[i].rotationz, primitive_geometrique[i].scaleX, primitive_geometrique[i].scaleY, primitive_geometrique[i].scaleZ);
			if (primitive_geometrique[i].selctionner)
			{
				Draw_Modele_slectionner(position, Dino, i);
			}
			break;

		case TypePrimitive3d::f1:
			Draw_Modele(primitive_geometrique[i].angle, position, F1, primitive_geometrique[i].rotationx, primitive_geometrique[i].rotationy, primitive_geometrique[i].rotationz, primitive_geometrique[i].scaleX, primitive_geometrique[i].scaleY, primitive_geometrique[i].scaleZ);
			if (primitive_geometrique[i].selctionner)
			{
				Draw_Modele_slectionner(position, F1, i);
			}
			break;
		}
	}
}



void Geometrie::Gui3d_Setup()
{
	Gui3d.setup("Objets 3D");

	Gui3d.setDefaultWidth(270);
	Gui3d.setDefaultHeight(20);
	Gui3d.setSize(270, 200);

	PositionX.set("Position en X", 0, -ofGetWidth()/2, ofGetWidth()/2);
	PositionY.set("Position en Y", 0, -ofGetHeight() / 2, 600);
	PositionZ.set("Position en Z", 0, 0, 1000);
	
	Angle.set("Angle", 0, 0, 360);

	rationX.setup("Changer l'angle en x", false);
	rationX.addListener(this, &Geometrie::RationX_button_presse);

	rationY.setup("Changer l'angle en y", true);
	rationY.addListener(this, &Geometrie::RationY_button_presse);

	rationZ.setup("Changer l'angle en z", false);
	rationZ.addListener(this, &Geometrie::RationZ_button_presse);

	ScaleX.set("Proportion en X", 1, 0.1, 5);
	ScaleY.set("Proportion en Y", 1, 0.1, 5);
	ScaleZ.set("Proportion en Z", 1, 0.1, 5);

	Rayon.set("Rayon", 100, 0, 1000); 
	couleur.set("couleur du trait", ofColor(255), ofColor(0, 0), ofColor(255, 255));

	Index_selection.set("Index", 0, 0, Index);

	selection.setup("Selectionner");
	selection.addListener(this, &Geometrie::selectionner_button);

	sphere_button.setup("Sphere");
	sphere_button.addListener(this, &Geometrie::sphere_button_presse);
	
	cube_button.setup("Cube");
	cube_button.addListener(this, &Geometrie::cube_button_presse);

	undo_button.setup("Undo");
	undo_button.addListener(this, &Geometrie::undo_button_presse);

	redo_button.setup("Redo");
	redo_button.addListener(this, &Geometrie::redo_button_presse);

	clear_button.setup("Clear");
	clear_button.addListener(this, &Geometrie::clear_button_presse);

	Add_Human.setup("Human");
	Add_Human.addListener(this, &Geometrie::Human_button_presse);

	Add_Dino.setup("Dino");
	Add_Dino.addListener(this, &Geometrie::Dino_button_presse);

	Add_F1.setup("F1");
	Add_F1.addListener(this, &Geometrie::F1_button_presse); 

	Gui3d.add(&cube_button);
	Gui3d.add(&sphere_button);
	Gui3d.add(&Add_Human);
	Gui3d.add(&Add_Dino);
	Gui3d.add(&Add_F1);

	Gui3d.add(couleur);

	Gui3d.add(PositionX);
	Gui3d.add(PositionY);
	Gui3d.add(PositionZ);

	Gui3d.add(Angle);
	Gui3d.add(&rationX);
	Gui3d.add(&rationY);
	Gui3d.add(&rationZ);

	Gui3d.add(Rayon);
	Gui3d.add(ScaleX);
	Gui3d.add(ScaleY);
	Gui3d.add(ScaleZ);

	Gui3d.add(&undo_button);
	Gui3d.add(&redo_button);
	Gui3d.add(&clear_button);



	Gui3d.add(Index_selection);
	Gui3d.add(&selection);




	//model
	Human.load("Human.obj");
	Dino.load("T-Rex.obj");
	F1.load("F1.obj");

	//cam
	Camera.setup("Camera");
	nb_cam2.set("Nb de camera", 1, 1, 4);

	Camera.add(nb_cam2);

	Gui3d.add(&Camera);


}

void Geometrie::sphere_button_presse()
{
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	ajouter_une_primitive_3d(Sphere);
}

void Geometrie::cube_button_presse()
{
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	ajouter_une_primitive_3d(cube);
}



void Geometrie::Human_button_presse()
{
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	ajouter_une_primitive_3d(human);
}

void Geometrie::Dino_button_presse()
{
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	ajouter_une_primitive_3d(dino);
}

void Geometrie::F1_button_presse()
{
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	ajouter_une_primitive_3d(f1);
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

void Geometrie::selectionner_button()
{
	autreIndex = Index_selection;
	for (int i = 0; i < primitive_geometrique.size(); i++)
	{
		primitive_geometrique[i].selctionner = false;
	}
	primitive_geometrique[autreIndex].selctionner = true;

	regarde_un_objet[0] = primitive_geometrique[autreIndex].x;
	regarde_un_objet[1] = primitive_geometrique[autreIndex].y;
	regarde_un_objet[2] = primitive_geometrique[autreIndex].z;
}




void Geometrie::RationX_button_presse(bool &value)
{
	if (value) {
		rotationX = 1.0f;
	}
	else
	{
		rotationX = 0.0f;
	}
}

void Geometrie::RationY_button_presse(bool& value)
{
	if (value) {
		rotationY = 1.0f;
	}
	else
	{
		rotationY = 0.0f;
	}
}

void Geometrie::RationZ_button_presse(bool& value)
{
	if (value) {
		rotationZ = 1.0f;
	}
	else
	{
		rotationZ = 0.0f;
	}
}

void Geometrie::undo()
{
	Index--;
	if (!primitive_geometrique.empty())
	{
		Primitive3d undoPrimitive = primitive_geometrique.back();
		primitive_geometrique.pop_back();
		redo.push_back(undoPrimitive);
	}
}

void Geometrie::redo3d()
{
	Index++;
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
	Index = -1;
	
}

void Geometrie::Draw_cube(ofColor p_color, ofVec3f position, float width, float height, float depth) const
{
	ofNoFill();
	ofSetColor(p_color);

	ofDrawBox(position, width, height, depth);
}

void Geometrie::Draw_sphere(ofColor p_color, ofVec3f position, float rayon) const
{
	ofNoFill();
	ofSetColor(p_color);
	ofDrawSphere(position, rayon);
}

void Geometrie::Draw_Modele(float angle, ofVec3f position, ofxAssimpModelLoader& model,  float rotax, float rotay, float roatz,float scalex, float scaley, float scalez) const
{
	model.setPosition(position.x, position.y, position.z);
	model.setRotation(0, angle, rotax, rotay, roatz);
	model.setScale(scalex, scaley, scalez);
	model.draw(OF_MESH_FILL);

	model.getNumMeshes();
}


void Geometrie::Draw_Modele_slectionner(ofVec3f position, ofxAssimpModelLoader& model, int index)
{

	model.setPosition(position.x, position.y, position.z);
	model.setRotation(0, Angle, rotationX, rotationY, rotationZ);
	model.setPosition(ofGetWindowWidth() / 2 + PositionX, ofGetWindowHeight() / 2 + PositionY, -PositionZ);

	model.setScale(ScaleX, ScaleY, ScaleZ);

	primitive_geometrique[index].x = ofGetWindowWidth() / 2 + PositionX;
	primitive_geometrique[index].y = ofGetWindowHeight() / 2 + PositionY;
	primitive_geometrique[index].z = -PositionZ;

	primitive_geometrique[index].scaleX = ScaleX;
	primitive_geometrique[index].scaleY = ScaleY;
	primitive_geometrique[index].scaleZ = ScaleZ;



	primitive_geometrique[index].angle = Angle;

	primitive_geometrique[index].rotationx = rotationX;
	primitive_geometrique[index].rotationy = rotationY;
	primitive_geometrique[index].rotationz = rotationZ;

	regarde_un_objet[0] = primitive_geometrique[index].x;
	regarde_un_objet[1] = primitive_geometrique[index].y;
	regarde_un_objet[2] = primitive_geometrique[index].z;

	model.draw(OF_MESH_FILL);
}


void Geometrie::Draw_primitive_slectionner(ofVec3f position, int index, TypePrimitive3d type)
{



	primitive_geometrique[index].x = ofGetWindowWidth() / 2 + PositionX;
	primitive_geometrique[index].y = ofGetWindowHeight() / 2 + PositionY;
	primitive_geometrique[index].z = -PositionZ;


	primitive_geometrique[index].rayon = Rayon;

	primitive_geometrique[index].color = couleur;

	switch (type)
	{
	case Sphere:
		ofDrawSphere(primitive_geometrique[index].x, primitive_geometrique[index].y, primitive_geometrique[index].z, primitive_geometrique[index].rayon);
		break;
	case cube:
		ofDrawBox(primitive_geometrique[index].x, primitive_geometrique[index].y, primitive_geometrique[index].z, primitive_geometrique[index].rayon);
		break;
	
	
	}

	ofDrawSphere(primitive_geometrique[index].x, primitive_geometrique[index].y, primitive_geometrique[index].z, primitive_geometrique[index].rayon);


	regarde_un_objet[0] = primitive_geometrique[index].x;
	regarde_un_objet[1] = primitive_geometrique[index].y;
	regarde_un_objet[2] = primitive_geometrique[index].z;


}


ofxBaseGui * Geometrie::getUi(){
    return &Gui3d;
}