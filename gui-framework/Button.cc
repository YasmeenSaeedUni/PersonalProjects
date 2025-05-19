#include "Button.h"

//constructors
Button::Button(const Rectangle& rect, const std::string& id, const std::string& label, const RGB& borderColour, const RGB& fillColour): Component(rect, id), label(label), borderColour(borderColour), fillColour(fillColour) {}

Button::Button(int x, int y, int width, int height, const std::string& id, const std::string& label, const RGB& borderColour, const RGB& fillColour): Component(x, y, width, height, id), label(label), borderColour(borderColour), fillColour(fillColour) {}
   
//getter and setter
void Button::setHeight(int newHeight){ prefRect.height = newHeight; }
int Button::getHeight() const{ return prefRect.height; }

void Button::print() const {
    std::cout << "  Button ID: " << getId() << std::endl;
    std::cout << "  Label: " << label << std::endl;
    Rectangle r = getRectangle();
    std::cout << "  Preferred Rectangle: (" << r.x << ", " << r.y << ", "
              << r.width << ", " << r.height << ")" << std::endl;
    std::cout << "  Border Colour: ";
    borderColour.print();  // Assumes RGB::print() prints the RGB values.
    std::cout << "  Fill Colour: ";
    fillColour.print();
}

//override draw
void Button::draw(Display* display, Window window, GC gc, const Rectangle& rect) const{
    unsigned long fillPixel = fillColour.getColour();
    unsigned long borderPixel = borderColour.getColour();

    XSetForeground(display, gc, fillPixel);
    XFillRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    XSetForeground(display, gc, borderPixel);
    XDrawRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    //draw the buttons label
    int textX = rect.x + 5;               
    int textY = rect.y + (rect.height / 2);
    XDrawString(display, window, gc, textX, textY, label.c_str(), label.length());

    //to make sure its sent to the server
    XFlush(display);
}
