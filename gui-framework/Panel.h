#ifndef PANEL_H
#define PANEL_H

#include <iostream>
#include <string>
#include "Component.h"
#include "ComponentList.h"

class Panel : public Component {
protected:
    ComponentList components;

public:
    //constructors
    Panel(const Rectangle& rect, const std::string& id);
    Panel(int x, int y, int width, int height, const std::string& id);

    //virtual destructor
    virtual ~Panel();

    //copying ComponentList interface
    bool add(Component* comp);
    bool add(Component* comp, int index);
    Component* remove(const std::string& id);
    Component* remove(int index);
    Component* get(const std::string& id) const;
    Component* get(int index) const;
    int getSize() const;

    virtual void print() const override;
    
    //print out all the Components
    void printComponents() const;

    //override draw (pure virtual)
    virtual void draw(Display* display, Window window, GC gc, const Rectangle& rect) const override = 0;
};

#endif
