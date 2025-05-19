#include "CuWindow.h"
#include "AbsolutePanel.h"  
#include <iostream>
#include <unistd.h>         // For usleep()
#include <cstdlib>          // For exit()

//constructor
CuWindow::CuWindow(const std::string& name, int width, int height, const RGB& background): name(name), width(width), height(height), background(background)
{
    //open connection to the server
    display = XOpenDisplay(nullptr);
    if (!display) {
        std::cerr << "Cannot open display" << std::endl;
        exit(1);
    }
    int screen = DefaultScreen(display);
    
    //create window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, width, height, 1,
                                 BlackPixel(display, screen), background.getColour());
    
    //create the graphics context
    gc = XCreateGC(display, window, 0, nullptr);
    
    XStoreName(display, window, name.c_str());
    XMapWindow(display, window);
    XFlush(display);
    
    //create the root panel as an AbsolutePanel
    root = new AbsolutePanel(0, 0, width, height, "root");
}

//destructor
CuWindow::~CuWindow()
{
    delete root;
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

//adds a Component to the root panel
bool CuWindow::add(Component* comp) {
    if (root) {
        return root->add(comp);
    }
    return false;
}

//removes the Component with the specified id from root panel
Component* CuWindow::remove(const std::string& id) {
    if (root) {
        return root->remove(id);
    }
    return nullptr;
}

//getter: returns a pointer to the Component with the given id
Component* CuWindow::get(const std::string& id) const {
    if (root) {
        return root->get(id);
    }
    return nullptr;
}

//draws the window
void CuWindow::draw() {
    usleep(100000);
    
    XSetForeground(display, gc, background.getColour());
    XFillRectangle(display, window, gc, 0, 0, width, height);
    
    //create a Rectangle for the entire window
    Rectangle winRect;
    winRect.x = 0;
    winRect.y = 0;
    winRect.width = width;
    winRect.height = height;
    
    //draw the root panel
    root->draw(display, window, gc, winRect);
    
    XFlush(display);
}

//prints the windows name and the number of Components in the root panel
void CuWindow::print() const {
    std::cout << "Window name: " << name << std::endl;
    std::cout << "Has " << root->getSize() << " component(s)." << std::endl;
}

//prints out all the Components in the root panel
void CuWindow::printComponents() const {
    root->printComponents();
}

//getters and setters
const std::string& CuWindow::getName() const {
    return name;
}

int CuWindow::getWidth() const {
    return width;
}

int CuWindow::getHeight() const {
    return height;
}

void CuWindow::setName(const std::string& n) {
    name = n;
}

void CuWindow::setWidth(int w) {
    width = w;
}

void CuWindow::setHeight(int h) {
    height = h;
}
