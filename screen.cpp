#include "screen.hpp"

void Screen::render(WINDOW *win, int xCursorPosition, int yCursorPosition, char *content)
{
    wmove(win, yCursorPosition, xCursorPosition);
    wprintw(win, content);
}

void Screen::refresh(WINDOW *win)
{
    wrefresh(win);
}