#include "AbsolutePanel.h"

//constructors
AbsolutePanel::AbsolutePanel(const Rectangle& rect, const std::string& id): Panel(rect, id) {}
AbsolutePanel::AbsolutePanel(int x, int y, int width, int height, const std::string& id): Panel(x, y, width, height, id) {}

//print
void AbsolutePanel::print() const {
    std::cout << " Absolute Panel ID: " << getId() << std::endl;
    Rectangle r = getRectangle();
    std::cout << "  Preferred Rectangle: (" << r.x << ", " << r.y << ", " 
              << r.width << ", " << r.height << ")" << std::endl;
    std::cout << "  Has" << getSize() << " component(s)." << std::endl;
}

//override draw
void AbsolutePanel::draw(Display* display, Window window, GC gc, const Rectangle& rect) const{
    //draw a rectangle around the panel
    XSetForeground(display, gc, RGB::BLACK().getColour());
    XDrawRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    //get the number of components in the panel
    int n = getSize();
    //allocate an array to hold the rectangles of components that have been drawn
    Rectangle* drawnRects = new Rectangle[n];
    int drawnCount = 0;

    //go through each component
    for (int i = 0; i < n; i++) {
        Component* comp = get(i);
        if (!comp)
            continue;
        //get the components preferred rectangle
        Rectangle compRect = comp->getRectangle();
        //check if overlapping
        bool isOverlapping = false;
        for (int j = 0; j < drawnCount; j++) {
            // dont overlap if one is completely to the left, right, above, or below the other rectangle
            if (!(compRect.x + compRect.width <= drawnRects[j].x ||
                  drawnRects[j].x + drawnRects[j].width <= compRect.x ||
                  compRect.y + compRect.height <= drawnRects[j].y ||
                  drawnRects[j].y + drawnRects[j].height <= compRect.y)) {
                isOverlapping = true;
                break;
            }
        }

        // if they dont overlap draw it
        if (!isOverlapping) {
            comp->draw(display, window, gc, compRect);
            drawnRects[drawnCount++] = compRect;
        }
    }
    delete[] drawnRects;
    XFlush(display);
}
