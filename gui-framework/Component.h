#ifndef COMPONENT_H
#define COMPONENT_H


#include <string>
#include <X11/Xlib.h>
#include <iostream>
#include "defs.h"


class Component {
protected:
    Rectangle prefRect;   //preferred rectangle     
    std::string id;    


public:
    //constructors
    Component(const Rectangle& r, const std::string& id);
    Component(int x, int y, int width, int height, const std::string& id);


    //virtual destructor
    virtual ~Component() {}


    //getter for id
    const std::string& getId() const;


    //getter for the rectangle
    const Rectangle& getRectangle() const;


    //sees if the component overlaps with another
    bool overlaps(const Component& other) const;


    //prints about the Component
    virtual void print() const;


    //pure virtual draw function
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& drawRect) const = 0;
};
#endif
