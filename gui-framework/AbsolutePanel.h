#ifndef ABSOLUTEPANEL_H
#define ABSOLUTEPANEL_H

#include "Panel.h"
#include <iostream>
#include <X11/Xlib.h>
#include "RGB.h"

class AbsolutePanel : public Panel {
public:
    //constructors
    AbsolutePanel(const Rectangle& rect, const std::string& id);
    AbsolutePanel(int x, int y, int width, int height, const std::string& id);

    virtual void print() const override;

    //override draw
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& rect) const override;
};

#endif
