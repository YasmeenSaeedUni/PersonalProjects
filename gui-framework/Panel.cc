#include "Panel.h"
#include <iostream>

//constructors
Panel::Panel(const Rectangle& rect, const std::string& id): Component(rect, id) {}

Panel::Panel(int x, int y, int width, int height, const std::string& id): Component(x, y, width, height, id) {}

//virtual destructor
Panel::~Panel() {
    while(getSize() >0){
        Component* comp=remove(0);
        delete comp;
    }
}

//copying functions from ComponentList
bool Panel::add(Component* comp) {
    return components.add(comp);
}

bool Panel::add(Component* comp, int index) {
    return components.add(comp, index);
}

Component* Panel::remove(const std::string& id) {
    return components.remove(id);
}

Component* Panel::remove(int index) {
    return components.remove(index);
}

Component* Panel::get(const std::string& id) const {
    return components.get(id);
}

Component* Panel::get(int index) const {
    return components.get(index);
}

int Panel::getSize() const {
    return components.getSize();
}

void Panel::print() const {
    std::cout << "  Panel ID: " << getId() << std::endl;
    Rectangle r = getRectangle();
    std::cout << "  Preferred Rectangle: (" << r.x << ", " << r.y << ", " 
              << r.width << ", " << r.height << ")" << std::endl;
    std::cout << "  Contains " << getSize() << " component(s)." << std::endl;
}

//print out all the Components
void Panel::printComponents() const {
    std::cout << "Components:" << std::endl;
    for (int i = 0; i < getSize(); i++) {
        Component* comp = get(i);
        if (comp != nullptr) {
            comp->print();
        }
    }
}
