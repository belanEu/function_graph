#include <iostream>
#include <thread>
#include <chrono>
#include "vertex.hpp"
#include "screen.hpp"
#include "coordinatesystemxy.hpp"
#include "defs.hpp"
using namespace std;

int main()
{
	initscr();

	Screen scr(stdscr);
	CoordinateSystemXY sys(int(scr.width / 2), int(scr.height / 2), scr.width, scr.height, 3, 0.5);
	
	// render coordinate system
	scr.render(stdscr, 0, 0, sys.content);
	scr.refresh(stdscr);
	// render width and height
	move(scr.height - 3, 0);
	printw("focusX: %d, focusY: %d", sys.focusX, sys.focusY);
	refresh();

	move(scr.height - 2, 0);
	printw("x0: %d, y0: %d", sys.xO, sys.yO);
	refresh();

	move(scr.height - 1, 0);
	printw("width: %d, height: %d", scr.width, scr.height);
	refresh();

	sys.goRight(int(33));
	sys.goTop(int(14));

	this_thread::sleep_for(chrono::seconds(3));

	// render coordinate system
	scr.render(stdscr, 0, 0, sys.content);
	scr.refresh(stdscr);
	// render width and height
	move(scr.height - 3, 0);
	printw("focusX: %d, focusY: %d", sys.focusX, sys.focusY);
	refresh();

	move(scr.height - 2, 0);
	printw("x0: %d, y0: %d", sys.xO, sys.yO);
	refresh();

	move(scr.height - 1, 0);
	printw("width: %d, height: %d", scr.width, scr.height);

	char c = getch();

	if (c == 'a')
	{
		move(0, 0);
		printw("Goodbye!");
		refresh();
	}

	return 0;
}
