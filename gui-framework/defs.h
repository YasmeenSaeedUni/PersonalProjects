#ifndef DEFS_H
#define DEFS_H
#define MAX_COMPONENTS 256

#define CuColour unsigned long


struct Rectangle{
    int x;
    int y;
    int width;
    int height;
    Rectangle(): x(0), y(0), width(0), height(0){}
    Rectangle(int x, int y, int width, int height): x(x), y(y), width(width), height(height){}
    Rectangle(const Rectangle& rect): x(rect.x), y(rect.y), width(rect.width), height(rect.height){}
    bool overlaps(const Rectangle& rect) const{
        if (x < rect.x + rect.width && x + width > rect.x && y < rect.y + rect.height && y + height > rect.y){
            return true;
        }
        if (rect.x < x + width && rect.x + rect.width > x && rect.y < y + height && rect.y + rect.height > y){
            return true;
        }
        return false;
    }

    bool contains(int x, int y) const{
        return x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height;
    }
};



#endif