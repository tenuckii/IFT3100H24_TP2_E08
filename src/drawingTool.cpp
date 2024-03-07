#include "drawingTool.h"

void DrawingTool::setup()
{
	currentPrimitiveType = PrimitiveType::NONE;
	show_menu = true;

    creationData = (PrimitiveCreationData*)std::malloc(sizeof(PrimitiveCreationData));

	gui.setup("Outils de dessin");
	gui.setDefaultWidth(400);

	// Color Pickers
	color_picker_background.set("Couleur du canevas", ofColor(127), ofColor(0, 0), ofColor(255, 255));
	color_picker_shape_outline.set("Couleur du contour", ofColor(0), ofColor(0, 0), ofColor(255, 255));
	color_picker_shape_fill.set("Couleur de remplissage", ofColor(0), ofColor(0, 0), ofColor(255, 255));

	// Sliders
	slider_stroke_weight.set("Largeur de la ligne", 4.0f, 0.0f, 20.0f);

	// Buttons with event listeners
	line_button.setup("Ligne", 200, 25);
	line_button.addListener(this, &DrawingTool::setLineType);

	rectangle_button.setup("Rectangle", 200, 25);
	rectangle_button.addListener(this, &DrawingTool::setRectangleType);

	triangle_button.setup("Triangle", 200, 25);
	triangle_button.addListener(this, &DrawingTool::setTriangleType);

	circle_button.setup("Cercle", 200, 25);
	circle_button.addListener(this, &DrawingTool::setCircleType);

	ellipse_button.setup("Ellipse", 200, 25);
	ellipse_button.addListener(this, &DrawingTool::setEllipseType);

	gui.add(&line_button);
	gui.add(&rectangle_button);
	gui.add(&triangle_button);
	gui.add(&circle_button);
	gui.add(&ellipse_button);
	gui.add(color_picker_background);
	gui.add(color_picker_shape_outline);
	gui.add(color_picker_shape_fill);
	gui.add(slider_stroke_weight);
}

void DrawingTool::exit()
{
	line_button.removeListener(this, &DrawingTool::setLineType);
	rectangle_button.removeListener(this, &DrawingTool::setRectangleType);
	triangle_button.removeListener(this, &DrawingTool::setTriangleType);
	circle_button.removeListener(this, &DrawingTool::setCircleType);
	ellipse_button.removeListener(this, &DrawingTool::setEllipseType);
}

void DrawingTool::draw() {
	if (show_menu)
		gui.draw();
}

void DrawingTool::showHideMenu()
{
	show_menu = !show_menu;
}

void DrawingTool::setLineType()
{
	currentPrimitiveType = PrimitiveType::LINE;
}

void DrawingTool::setRectangleType()
{
	currentPrimitiveType = PrimitiveType::RECTANGLE;
}

void DrawingTool::setTriangleType()
{
	currentPrimitiveType = PrimitiveType::TRIANGLE;
}

void DrawingTool::setCircleType()
{
	currentPrimitiveType = PrimitiveType::CIRCLE;
}

void DrawingTool::setEllipseType()
{
	currentPrimitiveType = PrimitiveType::ELLIPSE;
}

PrimitiveCreationData* DrawingTool::getPrimitiveCreationData()
{
	creationData->is_active = show_menu;
	creationData->background_color = color_picker_background;
	creationData->outline_color = color_picker_shape_outline;
	creationData->fill_color = color_picker_shape_fill;
	creationData->outline_width = slider_stroke_weight;
	creationData->primitiveType = currentPrimitiveType;
	return creationData;
}

bool DrawingTool::isDrawModeActive() const
{
	return show_menu;
}

ofColor DrawingTool::getBackgroundColor()
{
	return color_picker_background;
}

ofColor DrawingTool::getOutlineColor()
{
	return color_picker_shape_outline;
}

ofColor DrawingTool::getFillColor()
{
	return color_picker_shape_fill;
}

float DrawingTool::getOutlineWidth()
{
	return slider_stroke_weight;
}

PrimitiveType DrawingTool::getCurrentPrimitiveType()
{
	return currentPrimitiveType;
}

ofxBaseGui * DrawingTool::getUi(){
    return &gui;
}