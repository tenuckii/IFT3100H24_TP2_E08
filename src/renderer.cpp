#include "renderer.h"

void Renderer::setup()
{
	buffer_count = 200;
	buffer_head = 0;
	buffer_stride = sizeof(Primitive);
	buffer_size = buffer_count * buffer_stride;

    latestDrawingToolStatus = (DrawingToolStatus*)std::malloc(sizeof(DrawingToolStatus));
	primitives = (Primitive*)std::malloc(buffer_size);

	mouse_press_x = mouse_press_y = mouse_current_x = mouse_current_y = index = 0;
	is_mouse_button_pressed = draw_new_primitive_next_frame = false;
}

void Renderer::draw(DrawingToolStatus* primitiveCreationData)
{
	latestDrawingToolStatus = primitiveCreationData;
	ofSetBackgroundColor(this->latestDrawingToolStatus->background_color);

	if (draw_new_primitive_next_frame) 
		createPrimitive();
	if (this->latestDrawingToolStatus->is_active && is_mouse_button_pressed)
		drawPrimitiveCurrentlyBeingDrawn();
	if (this->latestDrawingToolStatus->commandType == CommandType::UNDO)
		undoLastPrimitive();
	if (this->latestDrawingToolStatus->commandType == CommandType::REDO)
		redoLastPrimitive();
	if (this->latestDrawingToolStatus->commandType == CommandType::CLEAR)
		clearPrimitives();

	for (index = 0; index < buffer_count; ++index)
		this->drawPrimitive(primitives[index]);
}

void Renderer::undoLastPrimitive()
{
	if (buffer_head == 0)
		return;

	buffer_head = buffer_head - 1;
	Primitive primitiveToUndo = primitives[buffer_head];
	redoPrimitives.push(primitiveToUndo);

	primitives[buffer_head].type = PrimitiveType::NONE;
}

void Renderer::redoLastPrimitive()
{
	if (redoPrimitives.size() == 0)
		return;

	Primitive recreatedPrimitive = redoPrimitives.top();
	redoPrimitives.pop();

	createPrimitive(recreatedPrimitive);
}

void Renderer::clearPrimitives()
{
	while (!redoPrimitives.empty())
		redoPrimitives.pop();

	for (index = 0; index < buffer_count; ++index)
		primitives[index].type = PrimitiveType::NONE;

	buffer_head = 0;
}

void Renderer::createPrimitive()
{
	// Empty the redo stack
	while (!redoPrimitives.empty())
		redoPrimitives.pop();

	draw_new_primitive_next_frame = false;

	// Skip when was created with NONE type (no type was selected yet)
	if (this->latestDrawingToolStatus->primitiveType == PrimitiveType::NONE)
		return;

	primitives[buffer_head].type = this->latestDrawingToolStatus->primitiveType;

	primitives[buffer_head].start_pos[0] = mouse_press_x;
	primitives[buffer_head].start_pos[1] = mouse_press_y;

	primitives[buffer_head].end_pos[0] = mouse_current_x;
	primitives[buffer_head].end_pos[1] = mouse_current_y;

	primitives[buffer_head].outline_color[0] = this->latestDrawingToolStatus->outline_color.r;
	primitives[buffer_head].outline_color[1] = this->latestDrawingToolStatus->outline_color.g;
	primitives[buffer_head].outline_color[2] = this->latestDrawingToolStatus->outline_color.b;
	primitives[buffer_head].outline_color[3] = this->latestDrawingToolStatus->outline_color.a;

	primitives[buffer_head].fill_color[0] = this->latestDrawingToolStatus->fill_color.r;
	primitives[buffer_head].fill_color[1] = this->latestDrawingToolStatus->fill_color.g;
	primitives[buffer_head].fill_color[2] = this->latestDrawingToolStatus->fill_color.b;
	primitives[buffer_head].fill_color[3] = this->latestDrawingToolStatus->fill_color.a;

	primitives[buffer_head].outline_width = this->latestDrawingToolStatus->outline_width;

	buffer_head = ++buffer_head >= buffer_count ? 0 : buffer_head; // boucler sur le tableau si plein
}

void Renderer::createPrimitive(Primitive primitive)
{
	primitives[buffer_head].type = primitive.type;

	primitives[buffer_head].start_pos[0] = primitive.start_pos[0];
	primitives[buffer_head].start_pos[1] = primitive.start_pos[1];

	primitives[buffer_head].end_pos[0] = primitive.end_pos[0];
	primitives[buffer_head].end_pos[1] = primitive.end_pos[1];

	primitives[buffer_head].outline_color[0] = primitive.outline_color[0];
	primitives[buffer_head].outline_color[1] = primitive.outline_color[1];
	primitives[buffer_head].outline_color[2] = primitive.outline_color[2];
	primitives[buffer_head].outline_color[3] = primitive.outline_color[3];

	primitives[buffer_head].fill_color[0] = primitive.fill_color[0];
	primitives[buffer_head].fill_color[1] = primitive.fill_color[1];
	primitives[buffer_head].fill_color[2] = primitive.fill_color[2];
	primitives[buffer_head].fill_color[3] = primitive.fill_color[3];

	primitives[buffer_head].outline_width = primitive.outline_width;

	buffer_head = ++buffer_head >= buffer_count ? 0 : buffer_head; // boucler sur le tableau si plein
}

void Renderer::drawPrimitiveCurrentlyBeingDrawn()
{
	// Create a temporary primitive object to draw on screen.
	Primitive p = { this->latestDrawingToolStatus->primitiveType, 
		{ mouse_press_x, mouse_press_y }, 
		{ mouse_current_x, mouse_current_y }, 
		this->latestDrawingToolStatus->outline_width, 
		{this->latestDrawingToolStatus->outline_color.r,
			this->latestDrawingToolStatus->outline_color.g ,
			this->latestDrawingToolStatus->outline_color.b ,
			this->latestDrawingToolStatus->outline_color.a / 2.0f }, 
		{ this->latestDrawingToolStatus->fill_color.r,
			this->latestDrawingToolStatus->fill_color.g ,
			this->latestDrawingToolStatus->fill_color.b ,
			this->latestDrawingToolStatus->fill_color.a / 2.0f } 
	};

	drawPrimitive(p);
}

void Renderer::drawPrimitive(Primitive primitive)
{
	float width = primitive.end_pos[0] - primitive.start_pos[0];
	float height = primitive.end_pos[1] - primitive.start_pos[1];

	// Circle data
	float radius = distanceBetweenTwoPoints(primitive.start_pos[0], primitive.start_pos[1], primitive.end_pos[0], primitive.end_pos[1]);

	// Triangle data
	float v1_x = primitive.start_pos[0];
	float v1_y = primitive.start_pos[1];
	float v2_x = primitive.start_pos[0] + width / 2;
	float v2_y = primitive.end_pos[1];
	float v3_x = primitive.end_pos[0];
	float v3_y = primitive.start_pos[1];

	// Sun data
	float corner_offset = sqrt(2) / 2;
	float sun_y_top_inner_offset = 1.5 * radius * corner_offset;
	float sun_y_top_outer_offset = 2.5 * radius * corner_offset;
	float sun_x_right_inner_offset = 1.5 * radius * corner_offset;
	float sun_x_right_outer_offset = 2.5 * radius * corner_offset;
	float sun_y_bottom_inner_offset = 1.5 * radius * -corner_offset;
	float sun_y_bottom_outer_offset = 2.5 * radius * -corner_offset;
	float sun_x_left_inner_offset = 1.5 * radius * -corner_offset;
	float sun_x_left_outer_offset = 2.5 * radius * -corner_offset;

	// House Roof data
	float roof_v1_x = primitive.start_pos[0];
	float roof_v1_y = primitive.end_pos[1];
	float roof_v2_x = primitive.end_pos[0];
	float roof_v2_y = primitive.end_pos[1];
	float roof_v3_x = primitive.start_pos[0] + width / 2;
	float roof_v3_y = primitive.end_pos[1] + 0.5 * height;

	// House door data
	float door_start_x = primitive.start_pos[0] + 7 * width / 16;
	float door_start_y = primitive.start_pos[1];
	float door_width = width / 8;
	float door_height = height / 3;

	// House window data
	float window_1_start_x = primitive.start_pos[0] + width / 20;
	float window_1_start_y = primitive.start_pos[1] + height / 2;
	float window_2_start_x = primitive.start_pos[0] + width / 20 + width / 2 + width / 5;
	float window_2_start_y = primitive.start_pos[1] + height / 2;
	float window_width = width / 5;
	float window_height = height / 3;

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
			width, 
			height);

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
			width,
			height);
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
		ofDrawEllipse(primitive.start_pos[0] + width / 2.0f, primitive.start_pos[1] + height / 2.0f, width, height);

		// Draw outside ellipse
		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawEllipse(primitive.start_pos[0] + width / 2.0f, primitive.start_pos[1] + height / 2.0f, width, height);
		break;
	case PrimitiveType::HOUSE:
		// Draw Rectangle, base of the house
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		ofDrawRectangle(primitive.start_pos[0],
			primitive.start_pos[1],
			width,
			height);

		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawRectangle(primitive.start_pos[0],
			primitive.start_pos[1],
			width,
			height);

		// Draw Triangle, roof of the house
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			primitive.fill_color[0],
			primitive.fill_color[1],
			primitive.fill_color[2],
			primitive.fill_color[3]);
		
		ofDrawTriangle(roof_v1_x, roof_v1_y, roof_v2_x, roof_v2_y, roof_v3_x, roof_v3_y);

		ofNoFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawTriangle(roof_v1_x, roof_v1_y, roof_v2_x, roof_v2_y, roof_v3_x, roof_v3_y);

		// Draw Rectangle, the door of the house
		ofFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);
		ofDrawRectangle(door_start_x,
			door_start_y,
			door_width,
			door_height);

		// Draw rectangle, the window of the house
		ofDrawRectangle(window_1_start_x,
			window_1_start_y,
			window_width,
			window_height);
		ofDrawRectangle(window_2_start_x,
			window_2_start_y,
			window_width,
			window_height);
		break;
	case PrimitiveType::SUN:
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

		// Draw the 8 lines of the sun
		ofFill();
		ofSetLineWidth(primitive.outline_width);
		ofSetColor(
			primitive.outline_color[0],
			primitive.outline_color[1],
			primitive.outline_color[2],
			primitive.outline_color[3]);

		// 4 lines along the axis of the circle in the order : right, top, left, bottom
		ofDrawLine(primitive.start_pos[0] + 1.5 * radius, primitive.start_pos[1], primitive.start_pos[0] + 2.5 * radius, primitive.start_pos[1]);
		ofDrawLine(primitive.start_pos[0], primitive.start_pos[1] + 1.5 * radius, primitive.start_pos[0], primitive.start_pos[1] + 2.5 * radius);
		ofDrawLine(primitive.start_pos[0] - 1.5 * radius, primitive.start_pos[1], primitive.start_pos[0] - 2.5 * radius, primitive.start_pos[1]);
		ofDrawLine(primitive.start_pos[0], primitive.start_pos[1] - 1.5 * radius, primitive.start_pos[0], primitive.start_pos[1] - 2.5 * radius);

		// 4 lines around the circle, with angles of 45, 135, 225 and 315, which are equal to 1/4PI, 3/4PI, 5/4PI and 7/4PI
		ofDrawLine(primitive.start_pos[0] + sun_x_right_inner_offset, primitive.start_pos[1] + sun_y_top_inner_offset, primitive.start_pos[0] + sun_x_right_outer_offset, primitive.start_pos[1] + sun_y_top_outer_offset);
		ofDrawLine(primitive.start_pos[0] + sun_x_left_inner_offset, primitive.start_pos[1] + sun_y_top_inner_offset, primitive.start_pos[0] + sun_x_left_outer_offset, primitive.start_pos[1] + sun_y_top_outer_offset);
		ofDrawLine(primitive.start_pos[0] + sun_x_left_inner_offset, primitive.start_pos[1] + sun_y_bottom_inner_offset, primitive.start_pos[0] + sun_x_left_outer_offset, primitive.start_pos[1] + sun_y_bottom_outer_offset);
		ofDrawLine(primitive.start_pos[0] + sun_x_right_inner_offset, primitive.start_pos[1] + sun_y_bottom_inner_offset, primitive.start_pos[0] + sun_x_right_outer_offset, primitive.start_pos[1] + sun_y_bottom_outer_offset);
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

	if (!pressed && this->latestDrawingToolStatus->is_active && this->latestDrawingToolStatus->commandType == CommandType::CREATE)
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