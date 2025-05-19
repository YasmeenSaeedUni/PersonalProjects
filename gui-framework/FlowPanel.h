#ifndef FLOWPANEL_H
#define FLOWPANEL_H

#include <string>
#include <iostream>
#include <X11/Xlib.h>
#include "Panel.h"
#include "RGB.h"

class FlowPanel : public Panel {
private:
    int xgap;   
    int ygap;   

public:
    //constructors
    FlowPanel(const Rectangle& rect, const std::string& id, int xgap = 10, int ygap = 10);

    FlowPanel(int x, int y, int width, int height, const std::string& id, int xgap = 10, int ygap = 10);

    virtual void print() const override;

    //override draw
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& rect)const override;
};

#endif
