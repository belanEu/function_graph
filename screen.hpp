#include "defs.hpp"

#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
    public:
    
    int width, height;

    Screen(WINDOW *win)
    {
        getmaxyx(win, this->height, this->width);
    }

    void render(WINDOW *win, int xCursorPosition, int yCursorPosition, char *content);
    void refresh(WINDOW *win);
};

#endif