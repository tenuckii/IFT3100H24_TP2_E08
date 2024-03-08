#include "drawingTool.h"

void DrawingTool::setup()
{
	currentPrimitiveType = PrimitiveType::NONE;
	currentCommandType = CommandType::CREATE;
	show_menu = true;

    drawingToolStatus = (DrawingToolStatus*)std::malloc(sizeof(DrawingToolStatus));

	gui.setup("Outils de dessin");
	gui.setDefaultWidth(400);

	// Color Pickers
	color_picker_background.set("Couleur du canevas", ofColor(127), ofColor(0, 0), ofColor(255, 255));
	color_picker_shape_outline.set("Couleur du contour", ofColor(0), ofColor(0, 0), ofColor(255, 255));
	color_picker_shape_fill.set("Couleur de remplissage", ofColor(0, 0), ofColor(0, 0), ofColor(255, 255));

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

	house_button.setup("Maison", 200, 25);
	house_button.addListener(this, &DrawingTool::setHouseType);

	sun_button.setup("Soleil", 200, 25);
	sun_button.addListener(this, &DrawingTool::setSunType);

	undo_button.setup("Undo", 200, 25);
	undo_button.addListener(this, &DrawingTool::undo);

	redo_button.setup("Redo", 200, 25);
	redo_button.addListener(this, &DrawingTool::redo);

	clear_button.setup("Clear", 200, 25);
	clear_button.addListener(this, &DrawingTool::clear);

	gui.add(&line_button);
	gui.add(&rectangle_button);
	gui.add(&triangle_button);
	gui.add(&circle_button);
	gui.add(&ellipse_button);
	gui.add(&house_button);
	gui.add(&sun_button);
	gui.add(color_picker_background);
	gui.add(color_picker_shape_outline);
	gui.add(color_picker_shape_fill);
	gui.add(slider_stroke_weight);
	gui.add(&undo_button);
	gui.add(&redo_button);
	gui.add(&clear_button);

}

void DrawingTool::exit()
{
	line_button.removeListener(this, &DrawingTool::setLineType);
	rectangle_button.removeListener(this, &DrawingTool::setRectangleType);
	triangle_button.removeListener(this, &DrawingTool::setTriangleType);
	circle_button.removeListener(this, &DrawingTool::setCircleType);
	ellipse_button.removeListener(this, &DrawingTool::setEllipseType);
	house_button.removeListener(this, &DrawingTool::setHouseType);
	sun_button.removeListener(this, &DrawingTool::setSunType);
	undo_button.removeListener(this, &DrawingTool::undo);
	redo_button.removeListener(this, &DrawingTool::redo);
	clear_button.removeListener(this, &DrawingTool::clear);
}

void DrawingTool::draw() {
	
	if (show_menu)
		gui.draw();

	// Cannot draw when menu is minimized
	if (gui.isMinimized() && !gui.isHeaderEnabled())
		currentPrimitiveType = PrimitiveType::NONE;
}

void DrawingTool::showHideMenu()
{
	show_menu = !show_menu;

	if (!show_menu)
		currentPrimitiveType = PrimitiveType::NONE;
}

void DrawingTool::setNoneType()
{
	currentPrimitiveType = PrimitiveType::NONE;
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

void DrawingTool::setHouseType()
{
	currentPrimitiveType = PrimitiveType::HOUSE;
}

void DrawingTool::setSunType()
{
	currentPrimitiveType = PrimitiveType::SUN;
}

void DrawingTool::undo()
{
	currentCommandType = CommandType::UNDO;
}

void DrawingTool::redo()
{
	currentCommandType = CommandType::REDO;
}

void DrawingTool::clear()
{
	currentCommandType = CommandType::CLEAR;
}

DrawingToolStatus* DrawingTool::getDrawingToolStatus()
{
	drawingToolStatus->is_active = show_menu;
	drawingToolStatus->commandType = currentCommandType;
	drawingToolStatus->background_color = color_picker_background;
	drawingToolStatus->outline_color = color_picker_shape_outline;
	drawingToolStatus->fill_color = color_picker_shape_fill;
	drawingToolStatus->outline_width = slider_stroke_weight;
	drawingToolStatus->primitiveType = currentPrimitiveType;

	// Reset special command after it has been sent.
	if (currentCommandType != CommandType::CREATE)
		currentCommandType = CommandType::CREATE;

	return drawingToolStatus;
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

DrawingTool::~DrawingTool()
{
	std::free(drawingToolStatus);
}
