#include "Component.h"


//constructors
Component::Component(const Rectangle& r, const std::string& id): prefRect(r), id(id) {}

Component::Component(int x, int y, int width, int height, const std::string& id): prefRect{x, y, width, height}, id(id) {}


//getter for id
const std::string& Component::getId() const {
    return id;
}

//getter for the rectangle
const Rectangle& Component::getRectangle() const {
    return prefRect;
}

//sees if the component overlaps with another
bool Component::overlaps(const Component& other) const {
    const Rectangle& r1 = this->prefRect;
    const Rectangle& r2 = other.prefRect;
    if (r1.x + r1.width <= r2.x || r2.x + r2.width <= r1.x ||
        r1.y + r1.height <= r2.y || r2.y + r2.height <= r1.y)
    {
        return false;
    }
    return true;
}


//virtual print function
void Component::print() const {
    std::cout << "Component ID: " << id
              << " Rect: (" << prefRect.x << ", " << prefRect.y
              << ", " << prefRect.width << ", " << prefRect.height << ")"
              << std::endl;
}
