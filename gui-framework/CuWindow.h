#ifndef CUWINDOW_H
#define CUWINDOW_H

#include <string>
#include <X11/Xlib.h>
#include "RGB.h"
#include "Panel.h"  

class CuWindow {
private:
    std::string name;   
    int width;          
    int height;         
    RGB background;     

    Panel* root;        //root panel to hold Components

    //X11 members
    Display* display;   
    Window window;      
    GC gc;              

public:
    //constructor
    CuWindow(const std::string& name, int width, int height, const RGB& background);

    //destructor
    ~CuWindow();

    //adds a Component to the root panel
    bool add(Component* comp);

    //removes a Component with the given id from root panel
    Component* remove(const std::string& id);

    //getter: returns a pointer to the Component with the given id
    Component* get(const std::string& id) const;

    //draws the window
    void draw();

    //prints the windows name and the number of Components in the root panel
    void print() const;

    //prints out all the Components in the root panel
    void printComponents() const;

    //getters and setters
    const std::string& getName() const;
    int getWidth() const;
    int getHeight() const;
    void setName(const std::string& name);
    void setWidth(int width);
    void setHeight(int height);
};

#endif
