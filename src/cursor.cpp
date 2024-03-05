#include "cursor.h"

void Cursor::setup()
{
position = {.x = 0, .y = 0};
    cursor_type = CursorType::CROSSHAIR;
    length = 5.0f;
    gap = 2.5f;
    size = 1;
    color = ofColor(0,255,0,255);
}
void Cursor::draw()
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
    ofDrawCircle(position.x, position.y, length);
}
void Cursor::arrow_crosshair()
{
    ofSetLineWidth(size);
    ofSetColor(color);
    ofDrawLine(position.x, position.y, position.x, position.y + gap + length); // lower
    ofDrawTriangle(position.x - (length), position.y, position.x + (length), position.y, position.x, position.y - (length));
}

void Cursor::set_position(unsigned int x, unsigned int y)
{
    position = {x, y};
}
void Cursor::set_color(ofColor& _color){
    color = _color;
}
ofColor& Cursor::get_color(){
    return color;
}