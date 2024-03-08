#include "cursor.h"

void Cursor::setup()
{
    gui.setup("Cursor");

    position = {0, 0};
    cursor_type = CursorType::CROSSHAIR;

    gui.add(gap.set("Change gap", 2.5f, 0, 10));
    gui.add(length.set("Change length", 5.0f, 0, 10));
    gui.add(size.set("Change size", 1, 0, 10));
    gui.add(color.set("Crosshair Color", ofColor(255), ofColor(0, 0), ofColor(255, 255)));

    crosshair_btn.setup("Crosshair", 200, 25);
    t_crosshair_btn.setup("T Crosshair", 200, 25);
    round_crosshair_btn.setup("Round Crosshair", 200, 25);
    dot_crosshair_btn.setup("Dot Crosshair", 200, 25);
    arrow_crosshair_btn.setup("Arrow Crosshair", 200, 25);

    crosshair_btn.addListener(this, &Cursor::set_cursor_crosshair);
    t_crosshair_btn.addListener(this, &Cursor::set_cursor_t_crosshair);
    round_crosshair_btn.addListener(this, &Cursor::set_cursor_round_crosshair);
    dot_crosshair_btn.addListener(this, &Cursor::set_cursor_dot_crosshair);
    arrow_crosshair_btn.addListener(this, &Cursor::set_cursor_arrow_crosshair);

    gui.add(&crosshair_btn);
    gui.add(&t_crosshair_btn);
    gui.add(&dot_crosshair_btn);
    gui.add(&round_crosshair_btn);
    gui.add(&arrow_crosshair_btn);

    hide_ui = false;
}
void Cursor::draw(PrimitiveType primitiveType)
{
    switch (cursor_type)
    {
    case CursorType::ARROW_CROSSHAIR:
        arrow_crosshair();
        break;
    case CursorType::DOT_CROSSHAIR:
        dot_crosshair();
        break;
    case CursorType::ROUND_CROSSHAIR:
        round_crosshair();
        break;
    case CursorType::T_CROSSHAIR:
        t_crosshair();
        break;
    case CursorType::CROSSHAIR:
    default:
        crosshair();
        break;
    }
    if (!hide_ui)
        gui.draw();
    if (primitiveType != PrimitiveType::NONE)
        primitive_crosshair(primitiveType);

}

void Cursor::exit()
{
    crosshair_btn.removeListener(this, &Cursor::set_cursor_crosshair);
    t_crosshair_btn.removeListener(this, &Cursor::set_cursor_t_crosshair);
    round_crosshair_btn.removeListener(this, &Cursor::set_cursor_round_crosshair);
    dot_crosshair_btn.removeListener(this, &Cursor::set_cursor_dot_crosshair);
    arrow_crosshair_btn.removeListener(this, &Cursor::set_cursor_arrow_crosshair);
}
void Cursor::crosshair()
{
    ofSetLineWidth(size);
    ofSetColor(color);
    ofDrawLine(position.x + gap, position.y, position.x + gap + length, position.y); // right
    ofDrawLine(position.x - gap, position.y, position.x - gap - length, position.y); // left
    ofDrawLine(position.x, position.y + gap, position.x, position.y + gap + length); // lower
    ofDrawLine(position.x, position.y - gap, position.x, position.y - gap - length); // upper
}
void Cursor::t_crosshair()
{
    ofSetLineWidth(size);
    ofSetColor(color);
    ofDrawLine(position.x + gap, position.y, position.x + gap + length, position.y); // right
    ofDrawLine(position.x - gap, position.y, position.x - gap - length, position.y); // left
    ofDrawLine(position.x, position.y + gap, position.x, position.y + gap + length); // lower
}
void Cursor::round_crosshair()
{
    ofSetLineWidth(size);
    ofNoFill();
    ofEnableSmoothing();
    ofSetColor(color);
    ofDrawCircle(position.x, position.y, length);
}
void Cursor::dot_crosshair()
{
    ofSetLineWidth(size);
    ofSetColor(color);
    ofFill();
    ofDrawCircle(position.x, position.y, length);
}
void Cursor::arrow_crosshair()
{
    ofSetLineWidth(size);
    ofSetColor(color);
    ofFill();
    ofDrawLine(position.x, position.y, position.x, position.y + gap + length); // lower
    ofDrawTriangle(position.x - (length), position.y, position.x + (length), position.y, position.x, position.y - (length));
}

void Cursor::primitive_crosshair(PrimitiveType type)
{
    const float OFFSET = 15;
    const float DIMENSION = 20;
    const float LINE_WIDTH = 3;
    const float INNER_SUN_OFFSET = 1.1;
    const float OUTER_SUN_OFFSET = 1.5;
    const float RADIUS = DIMENSION / 2;
    Position start_position = { position.x + OFFSET, position.y + 2 * OFFSET };

    ofNoFill();
    ofSetLineWidth(LINE_WIDTH);
    ofSetColor(0);

    switch (type)
    {
    case PrimitiveType::LINE:
        ofDrawLine(start_position.x, start_position.y, start_position.x + DIMENSION, start_position.y - DIMENSION);
        break;
    case PrimitiveType::RECTANGLE:
        ofDrawRectangle(start_position.x, start_position.y, DIMENSION, -DIMENSION);
        break;
    case PrimitiveType::TRIANGLE:
        ofDrawTriangle(start_position.x, start_position.y, start_position.x + DIMENSION / 2, start_position.y - DIMENSION, start_position.x + DIMENSION, start_position.y);
        break;
    case PrimitiveType::CIRCLE:
        ofDrawCircle(start_position.x + RADIUS, start_position.y - RADIUS, RADIUS);
        break;
    case PrimitiveType::ELLIPSE:
        ofDrawEllipse(start_position.x + RADIUS, start_position.y - RADIUS, DIMENSION, RADIUS);
        break;
    case PrimitiveType::HOUSE:
        ofDrawRectangle(start_position.x, start_position.y, DIMENSION, -DIMENSION);
        ofDrawTriangle(start_position.x, start_position.y - DIMENSION, start_position.x + DIMENSION / 2, start_position.y - 1.5 * DIMENSION, start_position.x + DIMENSION, start_position.y - DIMENSION);
        break;
    case PrimitiveType::SUN:
        ofDrawCircle(start_position.x + RADIUS, start_position.y - RADIUS, RADIUS);

        ofDrawLine(start_position.x + RADIUS + INNER_SUN_OFFSET * RADIUS, start_position.y - RADIUS, start_position.x + RADIUS + OUTER_SUN_OFFSET * RADIUS, start_position.y - RADIUS);
        ofDrawLine(start_position.x + RADIUS - INNER_SUN_OFFSET * RADIUS, start_position.y - RADIUS, start_position.x + RADIUS - OUTER_SUN_OFFSET * RADIUS, start_position.y - RADIUS);
        ofDrawLine(start_position.x + RADIUS, start_position.y - RADIUS - INNER_SUN_OFFSET * RADIUS, start_position.x + RADIUS, start_position.y - RADIUS - OUTER_SUN_OFFSET * RADIUS);
        ofDrawLine(start_position.x + RADIUS, start_position.y - RADIUS + INNER_SUN_OFFSET * RADIUS, start_position.x + RADIUS, start_position.y - RADIUS + OUTER_SUN_OFFSET * RADIUS);
        
        ofDrawLine(start_position.x + RADIUS + INNER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.y - RADIUS + INNER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.x + RADIUS + OUTER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.y - RADIUS + OUTER_SUN_OFFSET * RADIUS * sqrt(2) / 2);
        ofDrawLine(start_position.x + RADIUS + INNER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.y - RADIUS + INNER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.x + RADIUS + OUTER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.y - RADIUS + OUTER_SUN_OFFSET * RADIUS * sqrt(2) / 2);
        ofDrawLine(start_position.x + RADIUS + INNER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.y - RADIUS + INNER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.x + RADIUS + OUTER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.y - RADIUS + OUTER_SUN_OFFSET * RADIUS * -sqrt(2) / 2);
        ofDrawLine(start_position.x + RADIUS + INNER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.y - RADIUS + INNER_SUN_OFFSET * RADIUS * -sqrt(2) / 2, start_position.x + RADIUS + OUTER_SUN_OFFSET * RADIUS * sqrt(2) / 2, start_position.y - RADIUS + OUTER_SUN_OFFSET * RADIUS * -sqrt(2) / 2);
        break;
    default:
        break;
    }
}

void Cursor::set_position(unsigned int x, unsigned int y)
{
    position = {x, y};
}

void Cursor::open_close_ui()
{
    hide_ui = !hide_ui;
}
void Cursor::set_cursor_crosshair()
{
    cursor_type = CursorType::CROSSHAIR;
}
void Cursor::set_cursor_t_crosshair()
{
    cursor_type = CursorType::T_CROSSHAIR;
}
void Cursor::set_cursor_round_crosshair()
{
    cursor_type = CursorType::ROUND_CROSSHAIR;
}
void Cursor::set_cursor_dot_crosshair()
{
    cursor_type = CursorType::DOT_CROSSHAIR;
}
void Cursor::set_cursor_arrow_crosshair()
{
    cursor_type = CursorType::ARROW_CROSSHAIR;
}

ofxBaseGui *Cursor::getUi()
{
    return &gui;
}