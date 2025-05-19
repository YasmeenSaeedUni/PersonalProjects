#ifndef RGB_H
#define RGB_H

#include "defs.h"  
#include <iostream> 

class RGB {
private:
    int red;
    int green;
    int blue;

public:
    // Constructors
    RGB();                       
    RGB(int r, int g, int b);    
    RGB(CuColour colour);        

    //getters
    int getR() const;
    int getG() const;
    int getB() const;
    CuColour getColour() const;

    //setters
    void setR(int r);
    void setG(int g);
    void setB(int b);
    void setColour(CuColour col);

    //print the RGB values
    void print() const;

    // Static colours
    static RGB WHITE();
    static RGB BLACK();
    static RGB RED();
    static RGB GREEN();
    static RGB BLUE();
};

#endif
