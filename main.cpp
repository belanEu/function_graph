#include <iostream>
#include <thread>
#include <chrono>
#include "vertex.hpp"
#include "screen.hpp"
#include "coordinatesystemxy.hpp"
#include "keycontroller.hpp"
#include "defs.hpp"
using namespace std;

int main()
{
	initscr();
	noecho();
	curs_set(0);

	Screen scr(stdscr);
	CoordinateSystemXY sys(int(scr.width / 2), int(scr.height / 2), scr.width, scr.height, 3, 0.5);
	
	bool t = true;
	while (t)
	{
		// render coordinate system
		scr.render(stdscr, 0, 0, sys.content);
		scr.refresh(stdscr);
		// render width and height
		move(scr.height - 3, 0);
		printw("focusX: %d, focusY: %d", sys.focusX, sys.focusY);
		scr.refresh(stdscr);

		move(scr.height - 2, 0);
		printw("x0: %d, y0: %d", sys.xO, sys.yO);
		scr.refresh(stdscr);

		move(scr.height - 1, 0);
		printw("width: %d, height: %d", scr.width, scr.height);
		
		char chr = getch();
		switch (chr)
		{
			case KeyController::exit:
				t = false;
				break;
			case KeyController::goTop:
				sys.goTop(1);
				break;
			case KeyController::goBottom:
				sys.goBottom(1);
				break;
			case KeyController::goLeft:
				sys.goLeft(1);
				break;
			case KeyController::goRight:
				sys.goRight(1);
				break;
		}
	}

	endwin();

	return 0;
}
