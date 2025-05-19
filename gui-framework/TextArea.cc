#include "TextArea.h"

//constructors
TextArea::TextArea(const Rectangle& rect, const std::string& id, const std::string& text, const RGB& borderColour, const RGB& fillColour): Component(rect, id), text(text), borderColour(borderColour), fillColour(fillColour) {}

TextArea::TextArea(int x, int y, int width, int height, const std::string& id, const std::string& text, const RGB& borderColour, const RGB& fillColour): Component(x, y, width, height, id), text(text), borderColour(borderColour), fillColour(fillColour) {}
    
//getter and setters
void TextArea::setText(const std::string& newText) { text = newText; }
std::string TextArea::getText()const { return text; }

void TextArea::print() const {
    std::cout << "  TextArea ID: " << getId() << std::endl;
    Rectangle r = getRectangle();
    std::cout << "  Preferred Rectangle: (" << r.x << ", " << r.y << ", "
              << r.width << ", " << r.height << ")" << std::endl;
    std::cout << "  Text: " << text << std::endl;
}

//the getNextLine helper
std::string TextArea::getNextLine(const std::string& text, int start, int availableWidth, XFontStruct* font_info) const {
    //if we have already used all text return empty
    if (start >= (int)text.size()) {
        return "";
    }

    int currentLength = text.size() - start;
    int textWidth = XTextWidth(font_info, text.substr(start, currentLength).c_str(), currentLength);

    //shrink currentLength until it fits in availableWidth
    while (currentLength > 0 && textWidth > availableWidth) {
        currentLength--;
        textWidth = XTextWidth(font_info, text.substr(start, currentLength).c_str(), currentLength);
    }

    if (currentLength == (int)text.size() - start) {
        return text.substr(start, currentLength);
    }

    int savedLength = currentLength;
    while (currentLength > 0 && text[start + currentLength - 1] != ' ') {
        currentLength--;
    }
    
    //if we couldn't find a space just return the substring that fits
    if (currentLength == 0) {
        return text.substr(start, savedLength);
    }
    //return up to the space
    return text.substr(start, currentLength);
}

//override draw
void TextArea::draw(Display* display, Window window, GC gc, const Rectangle& rect) const {

    unsigned long fillPixel = fillColour.getColour();
    unsigned long borderPixel = borderColour.getColour();

    XSetForeground(display, gc, fillPixel);
    XFillRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    XSetForeground(display, gc, borderPixel);
    XDrawRectangle(display, window, gc, rect.x, rect.y, rect.width, rect.height);

    //load a font
    const char* fontName = "6x10";
    Font font = XLoadFont(display, fontName);
    XFontStruct* font_info = XQueryFont(display, font);
    if (!font_info) {
        std::cerr << "Failed to query font." << std::endl;
        return;
    }
    XSetFont(display, gc, font);

    //calculate the text line height
    int textHeight = font_info->ascent + font_info->descent;

    // margin so the text doesn't touch the edges
    int margin = 3;
    int availableWidth = rect.width - 2 * margin; 

    int currentStart = 0;
    int currentLine = 0;

    //go through the text draw one line at a time
    while (currentStart < (int)text.size()) {
        //use your helper function to get the next line
        std::string nextLine = getNextLine(text, currentStart, availableWidth, font_info);
        if (nextLine.empty())
            break;  //no more text to display

        //get the position where the text should be drawn
        int textX = rect.x + margin;  // start at left margin
        int textY = rect.y + margin + textHeight * (currentLine + 1);

        if (textY + textHeight > rect.y + rect.height)
            break;
        XDrawString(display, window, gc, textX, textY, nextLine.c_str(), nextLine.size());
        
        currentStart += nextLine.size();
        currentLine++;
    }

    XFreeFontInfo(nullptr, font_info, 1);
    XFlush(display);
}

