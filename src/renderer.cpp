#include "renderer.h"

void Renderer::setup()
{
    //on a pas besoin de cap a 60fps
	// ofSetFrameRate(60);

	buffer_count = 200;
	buffer_head = 0;
	buffer_stride = sizeof(Primitive);
	buffer_size = buffer_count * buffer_stride;

	primitives = (Primitive*)std::malloc(buffer_size);

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = index = 0;
	is_mouse_button_pressed = draw_new_primitive_next_frame = false;
}

void Renderer::draw(PrimitiveCreationData primitiveCreationData)
{
	this->latestCreationData = primitiveCreationData;
	ofSetBackgroundColor(this->latestCreationData.background_color);

	if (draw_new_primitive_next_frame) 
		createPrimitive();
	if (this->latestCreationData.is_active && is_mouse_button_pressed)
		drawPrimitiveCurrentlyBeingDrawn();

	for (index = 0; index < buffer_count; ++index)
		this->drawPrimitive(primitives[index]);
}

void Renderer::createPrimitive()
{
	draw_new_primitive_next_frame = false;

	// Skip when was created with NONE type (no type was selected yet)
	if (this->latestCreationData.primitiveType == PrimitiveType::NONE)
		return;

	primitives[buffer_head].type = this->latestCreationData.primitiveType;

	primitives[buffer_head].start_pos[0] = mouse_press_x;
	primitives[buffer_head].start_pos[1] = mouse_press_y;

	primitives[buffer_head].end_pos[0] = mouse_current_x;
	primitives[buffer_head].end_pos[1] = mouse_current_y;

	primitives[buffer_head].outline_color[0] = this->latestCreationData.outline_color.r;
	primitives[buffer_head].outline_color[1] = this->latestCreationData.outline_color.g;
	primitives[buffer_head].outline_color[2] = this->latestCreationData.outline_color.b;
	primitives[buffer_head].outline_color[3] = this->latestCreationData.outline_color.a;

	primitives[buffer_head].fill_color[0] = this->latestCreationData.fill_color.r;
	primitives[buffer_head].fill_color[1] = this->latestCreationData.fill_color.g;
	primitives[buffer_head].fill_color[2] = this->latestCreationData.fill_color.b;
	primitives[buffer_head].fill_color[3] = this->latestCreationData.fill_color.a;

	primitives[buffer_head].outline_width = this->latestCreationData.outline_width;

	buffer_head = ++buffer_head >= buffer_count ? 0 : buffer_head; // boucler sur le tableau si plein
}

void Renderer::drawPrimitiveCurrentlyBeingDrawn()
{
	// Create a temporary primitive object to draw on screen.
	Primitive p = { this->latestCreationData.primitiveType, 
		{ mouse_press_x, mouse_press_y }, 
		{ mouse_current_x, mouse_current_y }, 
		this->latestCreationData.outline_width, 
		{this->latestCreationData.outline_color.r,
			this->latestCreationData.outline_color.g ,
			this->latestCreationData.outline_color.b ,
			this->latestCreationData.outline_color.a }, 
		{ this->latestCreationData.fill_color.r,
			this->latestCreationData.fill_color.g ,
			this->latestCreationData.fill_color.b ,
			this->latestCreationData.fill_color.a } 
	};

	drawPrimitive(p);
}

void Renderer::drawPrimitive(Primitive primitive)
{
	// Circle data
	float radius = distanceBetweenTwoPoints(primitive.start_pos[0], primitive.start_pos[1], primitive.end_pos[0], primitive.end_pos[1]);

	// Ellipse data
	float diameter_x = primitive.end_pos[0] - primitive.start_pos[0];
	float diameter_y = primitive.end_pos[1] - primitive.start_pos[1];

	// Triangle data
	float v1_x = primitive.start_pos[0];
	float v1_y = primitive.start_pos[1];
	float v2_x = primitive.start_pos[0] + (primitive.end_pos[0] - primitive.start_pos[0]) / 2;
	float v2_y = primitive.end_pos[1];
	float v3_x = primitive.end_pos[0];
	float v3_y = primitive.start_pos[1];

	switch (primitive.type)
	{
	case PrimitiveType::LINE:
		ofFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawLine(primitive.start_pos[0], primitive.start_pos[1], primitive.end_pos[0], primitive.end_pos[1]);
		break;
	case PrimitiveType::RECTANGLE:
		// Draw inside rectangle
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		ofDrawRectangle(primitive.start_pos[0], 
			primitive.start_pos[1], 
			primitive.end_pos[0] - primitive.start_pos[0], 
			primitive.end_pos[1] - primitive.start_pos[1]);

		// Draw outline rectangle
		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawRectangle(primitive.start_pos[0],
			primitive.start_pos[1],
			primitive.end_pos[0] - primitive.start_pos[0],
			primitive.end_pos[1] - primitive.start_pos[1]);
		break;
	case PrimitiveType::TRIANGLE:
		// Draw inside triangle
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		ofDrawTriangle(v1_x, v1_y, v2_x, v2_y, v3_x, v3_y);

		// Draw outline triangle
		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawTriangle(v1_x, v1_y, v2_x, v2_y, v3_x, v3_y);
		break;
	case PrimitiveType::CIRCLE:
		// Draw inside circle
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		ofDrawCircle(primitive.start_pos[0], primitive.start_pos[1], radius);

		// Draw outside circle
		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawCircle(primitive.start_pos[0], primitive.start_pos[1], radius);
		break;
	case PrimitiveType::ELLIPSE:
		// Draw inside ellipse
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		ofDrawEllipse(primitive.start_pos[0] + diameter_x / 2.0f, primitive.start_pos[1] + diameter_y / 2.0f, diameter_x, diameter_y);

		// Draw outside ellipse
		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawEllipse(primitive.start_pos[0] + diameter_x / 2.0f, primitive.start_pos[1] + diameter_y / 2.0f, diameter_x, diameter_y);
		break;
	default:
		break;
	}
}

void Renderer::setMousePosition(int x, int y)
{
	mouse_current_x = x;
	mouse_current_y = y;
}

void Renderer::setMouseClickPosition(int x, int y)
{
	mouse_press_x = x;
	mouse_press_y = y;
}

void Renderer::setMousePressStatus(bool pressed)
{
	is_mouse_button_pressed = pressed;

	if (!pressed && this->latestCreationData.is_active)
		draw_new_primitive_next_frame = true;
}

void Renderer::update() {

}

float Renderer::distanceBetweenTwoPoints(float x1, float y1, float x2, float y2)
{
	// Calculate the difference in x and y coordinates
	float dx = x2 - x1;
	float dy = y2 - y1;

	// Apply the Euclidean distance formula
	return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

Renderer::~Renderer()
{
	std::free(primitives);
}