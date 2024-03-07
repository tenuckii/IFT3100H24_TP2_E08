#pragma once

#include "ofMain.h"

enum class PrimitiveType {
	NONE,
	LINE,
	RECTANGLE,
	TRIANGLE,
	CIRCLE,
	ELLIPSE,
};

struct Primitive {
	PrimitiveType type;
	float start_pos[2];
	float end_pos[2];
	float outline_width;
	unsigned char outline_color[4];
	unsigned char fill_color[4];
	bool selectionner;
};

struct PrimitiveCreationData {
	bool is_active;
	ofColor background_color;
	ofColor outline_color;
	ofColor fill_color;
	float outline_width;
	PrimitiveType primitiveType;
};

class Renderer
{
private:
	bool is_mouse_button_pressed;

	int mouse_press_x;
	int mouse_press_y;

	int mouse_current_x;
	int mouse_current_y;
	//historique et selection
	vector<Primitive> DrawMatrice;
	// Used to draw primitives
	bool draw_new_primitive_next_frame;
	PrimitiveCreationData latestCreationData;
	Primitive* primitives;
	int buffer_count;
	int buffer_stride;
	int buffer_size;
	int buffer_head;
	int index;

	float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2);


public:
	void setup();
	void update();
	void draw(PrimitiveCreationData primitiveCreationData);

	void createPrimitive();
	void drawPrimitiveCurrentlyBeingDrawn();
	void drawPrimitive(Primitive primitive);

	void setMousePosition(int x, int y);
	void setMouseClickPosition(int x, int y);
	void setMousePressStatus(bool pressed);

	bool SelectChecker(int mouse_x, int mouse_y);

	~Renderer();
};
