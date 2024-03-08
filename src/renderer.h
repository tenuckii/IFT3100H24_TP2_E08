#pragma once

#include "ofMain.h"
#include "drawingTool.h"

class Renderer
{
private:
	bool is_mouse_button_pressed;

	int mouse_press_x;
	int mouse_press_y;

	int mouse_current_x;
	int mouse_current_y;

	// Used to draw primitives
	bool draw_new_primitive_next_frame;
	DrawingToolStatus* latestDrawingToolStatus;
	Primitive* primitives;
	std::stack<Primitive> redoPrimitives;
	int buffer_count;
	int buffer_stride;
	int buffer_size;
	int buffer_head;
	int index;

	float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2);
	void createPrimitive();
	void createPrimitive(Primitive primitive);
	void drawPrimitiveCurrentlyBeingDrawn();
	void drawPrimitive(Primitive primitive);


public:
	void setup();
	void update();
	void draw(DrawingToolStatus* primitiveCreationData);

	void undoLastPrimitive();
	void redoLastPrimitive();
	void clearPrimitives();

	void setMousePosition(int x, int y);
	void setMouseClickPosition(int x, int y);
	void setMousePressStatus(bool pressed);

	~Renderer();
};
