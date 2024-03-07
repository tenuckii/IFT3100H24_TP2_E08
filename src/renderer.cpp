#include "renderer.h"

void Renderer::setup()
{
	ofSetFrameRate(60);

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
	if (primitive.selectionner)
	{
		primitive.outline_color[0] = 0;
		primitive.outline_color[1] = 255;
		primitive.outline_color[2] = 0;
		primitive.outline_color[3] = 0;
	}

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
	DrawMatrice.push_back(primitive);
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
bool Renderer::SelectChecker(int mouse_x, int mouse_y)
{
	int jeu_arbitraire = 20;
	for each (Primitive forme in DrawMatrice)
	{	
		switch (forme.type)
		{
		case PrimitiveType::NONE:
			break;
		case PrimitiveType::LINE:
			
				if ((forme.end_pos[0] - forme.start_pos[0]) < jeu_arbitraire && (forme.end_pos[0] - forme.start_pos[0]) > -jeu_arbitraire)
					 {
					if (forme.end_pos[1] > forme.start_pos[1]) 
					{
						if (mouse_x < (forme.start_pos[0] + jeu_arbitraire) && mouse_x >(forme.end_pos[0] - jeu_arbitraire) && mouse_y > forme.start_pos[1]
							&& mouse_y > forme.end_pos[1]) {
							forme.selectionner = true;
							return true;
						}
					}
					else {
						if (mouse_x < (forme.end_pos[0] + jeu_arbitraire) && mouse_x >(forme.start_pos[0] - jeu_arbitraire) && mouse_y < forme.start_pos[1]
							&& mouse_y>forme.end_pos[1]) {
							forme.selectionner = true;
							return true;
						}
					}
				}
				float pente, borigine;
				pente = (forme.end_pos[1] - forme.start_pos[1]) / (forme.end_pos[0] - forme.start_pos[0]);
				borigine = forme.start_pos[1] - pente * forme.start_pos[0];
				if ((mouse_y - jeu_arbitraire) < (pente * mouse_x + borigine) && (mouse_y + jeu_arbitraire) > (pente * mouse_x + borigine)
					&& mouse_x > forme.start_pos[0] && mouse_x < forme.end_pos[0]) {
					forme.selectionner = true;
					return true;
				}
			
			break;
		case PrimitiveType::RECTANGLE:
			int rectangleWith = forme.end_pos[0] - forme.start_pos[0];
			int rectangleLenght= forme.end_pos[1] - forme.start_pos[1];
			if ((mouse_x >= forme.start_pos[0] && mouse_x <= forme.start_pos[0] + rectangleWith) &&
				(mouse_y >= forme.start_pos[1] && mouse_y <= forme.start_pos[1] + rectangleLenght))
			{
				forme.selectionner = true;
				return true;
			}

			break;
		case PrimitiveType::TRIANGLE:

			float v1_x = forme.start_pos[0];
			float v1_y = forme.start_pos[1];
			float v2_x = forme.start_pos[0] + (forme.end_pos[0] - forme.start_pos[0]) / 2;
			float v2_y = forme.end_pos[1];
			float v3_x = forme.end_pos[0];
			float v3_y = forme.start_pos[1];

			glm::vec3 v1 = glm::normalize(glm::vec3(v1_x,v1_y,0) - glm::vec3(mouse_x,mouse_y,0));
			glm::vec3 v2 = glm::normalize(glm::vec3(v2_x, v2_y,0) - glm::vec3(mouse_x, mouse_y, 0));
			glm::vec3 v3 = glm::normalize(glm::vec3(v3_x, v3_y,0) - glm::vec3(mouse_x, mouse_y, 0));
			float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
			float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
			float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
			if (a1 < 0 && a2 < 0 && a3 < 0) return true;
			else return false;

			break;
		case PrimitiveType::CIRCLE:

			break;
		case PrimitiveType::ELLIPSE:
			break;
		default:
			break;

		}
	
	}
}

Renderer::~Renderer()
{
	std::free(primitives);
}