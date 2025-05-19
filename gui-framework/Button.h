#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <iostream>
#include <X11/Xlib.h>
#include "Component.h"
#include "RGB.h" 

class Button : public Component {
private:
    std::string label;       
    RGB borderColour;        
    RGB fillColour;          

public:
    //constructors
    Button(const Rectangle& rect, const std::string& id, const std::string& label,
           const RGB& borderColour = RGB::BLACK(), const RGB& fillColour = RGB::WHITE());

    Button(int x, int y, int width, int height, const std::string& id, const std::string& label,
           const RGB& borderColour = RGB::BLACK(), const RGB& fillColour = RGB::WHITE());

    //getter and setter
    void setHeight(int newHeight);
    int getHeight() const;
    
    virtual void print() const override;

    //override draw
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& rect) const override;
};

#endif
