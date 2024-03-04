#pragma once

#include "ofMain.h"

class Cursor
{
public:
    void setup();
    void draw();
    void set_position(unsigned int x, unsigned int y);

private:
    typedef enum CursorType
    {
        CROSSHAIR,
        T_CROSSHAIR,
        ROUND_CROSSHAIR,
        DOT_CROSSHAIR,
        ARROW_CROSSHAIR,
    } CursoType;

    typedef struct Position
    {
        unsigned int x, y;
    } Position;

    Position position;
    CursorType cursor_type;
    float gap;
    float length;
    unsigned int size;
    unsigned int r,g,b;

    void crosshair();
    void t_crosshair();
    void round_crosshair();
    void dot_crosshair();
    void arrow_crosshair();
};