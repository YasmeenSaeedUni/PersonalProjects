#include "FlowPanel.h"

//constructors
FlowPanel::FlowPanel(const Rectangle& rect, const std::string& id, int xgap, int ygap): Panel(rect, id), xgap(xgap), ygap(ygap) {}

FlowPanel::FlowPanel(int x, int y, int width, int height, const std::string& id, int xgap, int ygap): Panel(x, y, width, height, id), xgap(xgap), ygap(ygap) {}


void FlowPanel::print() const {
    std::cout << "  Flow Panel ID: " << getId() << std::endl;
    Rectangle r = getRectangle();
    std::cout << "  Preferred Rectangle: (" << r.x << ", " << r.y << ", " 
              << r.width << ", " << r.height << ")" << std::endl;
    std::cout << "  Has " << getSize() << " component(s)." << std::endl;
}

//override draw
void FlowPanel::draw(Display* display, Window window, GC gc, const Rectangle& rect)const{
    //draw a rectangle around the panel
    XSetForeground(display, gc, RGB::WHITE().getColour());
    XDrawRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    //positions for placing components
    int margin=10;
    int currentX = rect.x+margin;
    int currentY = rect.y+margin;
    int panelRight = rect.x + rect.width-margin;
    int panelBottom = rect.y + rect.height-margin;
    int rowHeight=0;
    
    //go over each component
    int n = getSize();
    for (int i = 0; i < n; i++) {
        Component* comp = get(i);
        if (!comp) continue;
        //get the components preferred rectangle
        Rectangle compRect = comp->getRectangle();

        
        //if the component doesnt fit on the current line go to the next line
        if (currentX + compRect.width > panelRight) {
            currentX = rect.x+margin;           
            currentY += rowHeight + ygap; 
            rowHeight =0;
        }
        
        //dont draw the component if its width or height goes past the available area
        if(compRect.width >(rect.width -2 * margin)|| compRect.height > (rect.width -2 * margin)||currentY+ compRect.height>panelBottom){
            continue;
            
        }
        //create a drawing rectangle for the componen
        Rectangle drawRect;
        drawRect.x = currentX;
        drawRect.y = currentY;
        drawRect.width = compRect.width;
        drawRect.height = compRect.height;

        //draw the component using its own draw function
        comp->draw(display, window, gc, drawRect);

        // increment currentX with the components width plus the horizontal gap
        currentX += compRect.width + xgap;
        
        if(compRect.height>rowHeight){
            rowHeight=compRect.height;
        }
    }
    XFlush(display);
}
