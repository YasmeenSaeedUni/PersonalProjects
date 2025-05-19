#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <string>
#include <X11/Xlib.h>
#include "Component.h"
#include "RGB.h"  
#include <iostream>

class TextArea : public Component {
private:
    std::string text;       
    RGB borderColour;       
    RGB fillColour;         
    
    std::string getNextLine(const std::string& text, int start, int availableWidth, XFontStruct* font_info)const;

public:
    //constructors
    TextArea(const Rectangle& rect, const std::string& id, const std::string& text,
             const RGB& borderColour = RGB::BLACK(), const RGB& fillColour = RGB::WHITE());

    TextArea(int x, int y, int width, int height, const std::string& id, const std::string& text,
             const RGB& borderColour = RGB::BLACK(), const RGB& fillColour = RGB::WHITE());
    //getter and setter
    void setText(const std::string& newText);
    std::string getText() const;
    
    virtual void print() const override;

    //override draw
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& rect) const override;
};

#endif
