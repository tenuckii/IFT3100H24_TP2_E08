#include "interface.h"

void Interface::setup(Cursor *_cursor, DrawingTool *dt, ImageExpImp *iie, Geometrie *g3d)
{
    cursor = _cursor;
    drawing_tool = dt;
    image_import_export = iie;
    Geometrie3D = g3d;

    gui.setup("UI");

    gui.add(cursor->getUi());
    gui.add(drawing_tool->getUi());
    gui.add(image_import_export->getUi());
    gui.minimizeAll();
}

void Interface::draw(Mode mode, bool &mode_change)
{
    if (mode_change)
    {
        gui.clear();
        switch (mode)
        {
        case Mode::VIEW_2D:
            gui.add(cursor->getUi());
            gui.add(drawing_tool->getUi());
            gui.add(image_import_export->getUi());
            break;
        case Mode::VIEW_3D:
            gui.add(cursor->getUi());
            drawing_tool->setNoneType();
            gui.add(Geometrie3D->getUi());
            break;
        }

        gui.minimizeAll();
        mode_change = false;
    }
    gui.draw();
}
void Interface::exit()
{
    cursor_btn.removeListener(this, &Interface::cursor_open_close_ui);
    drawing_tool_btn.removeListener(this, &Interface::drawing_tool_open_close_ui);
}

void Interface::cursor_open_close_ui()
{
    cursor->open_close_ui();
}
void Interface::drawing_tool_open_close_ui()
{
    drawing_tool->showHideMenu();
}
