#include "coordinatesystemxy.hpp"

CoordinateSystemXY::CoordinateSystemXY(int xO, int yO, int maxX, int maxY, int numOfIntermediateSpaces, float step)
{
	this->xO = xO;
	this->yO = yO;
	
	this->focusX = this->xO;
	this->focusY = this->yO;

	this->maxX = maxX;
	this->maxY = maxY;

	this->step = step;

	this->numOfIntermediateSpaces = numOfIntermediateSpaces;
	this->numOfAxisDivisions = int(1 / this->step);
	this->numOfAllPiecesOfAxisInterval = this->numOfIntermediateSpaces * this->numOfAxisDivisions + this->numOfAxisDivisions;

	this->content = new char[(this->maxX + 1) * this->maxY];
	this->initializeCoordinateSystem();
}

void CoordinateSystemXY::clearCoordinateSystem()
{
	for (int i = 0; i < this->maxY; i++)
	{
		int j;
		for (j = 0; j < this->maxX; j++)
		{
			this->content[i * this->maxX + j] = ' ';
		}
		this->content[i * this->maxX + j] = '\n';
	}
}

void CoordinateSystemXY::attachXXFunction()
{

	for (float i = 0; i < this->maxX; i += this->step)
	{
		int x = int (i * this->numOfAllPiecesOfAxisInterval);
		int y = this->yO - int(i * i * this->numOfAllPiecesOfAxisInterval);
		int coordinatePositive = y * this->maxX + this->xO + x;
		int coordinateNegative = y * this->maxX + this->xO - x;

		if (coordinatePositive < 0 || coordinatePositive > this->maxX * this->maxY) {
			break;
		}
		if (coordinateNegative < 0 || coordinateNegative > this->maxX * this->maxY) {
			break;
		}
		char sym = x % this->numOfAllPiecesOfAxisInterval == 0 ? 'O' : 'o';
		this->content[coordinatePositive] = sym;
		this->content[coordinateNegative] = sym;
	}
}

void CoordinateSystemXY::setAxisXPeace(int screenX, int screenY, int difference)
{
	int tmp = difference % this->numOfAllPiecesOfAxisInterval;
	if (tmp % (this->numOfIntermediateSpaces + 1))
	{
		this->content[screenY * this->maxX + screenX] = '-';
	}
	else
	{
		if (tmp)
		{
			this->content[screenY * this->maxX + screenX] = '+';
		}
		else
		{
			this->content[screenY * this->maxX + screenX] = '|';
		}
	}
}

void CoordinateSystemXY::setAxisYPeace(int screenX, int screenY, int difference)
{
	int tmp = difference % this->numOfAllPiecesOfAxisInterval;
	if (tmp % (this->numOfIntermediateSpaces + 1))
	{
		this->content[screenY * this->maxX + screenX] = '|';
	}
	else
	{
		if (tmp)
		{
			this->content[screenY * this->maxX + screenX] = '+';
		}
		else
		{
			this->content[screenY * this->maxX + screenX] = '=';
		}
	}
}

void CoordinateSystemXY::setStartPointOfOXY(int screenX, int screenY)
{
	if (screenY >= 0 && screenY < this->maxY && screenX >= 0 && screenX < this->maxX)
	{
		this->content[screenY * this->maxX + screenX] = 'O';
	}
}

void CoordinateSystemXY::buildAxisX(int xO, int yO)
{
	if (yO >= 0 && yO < this->maxY)
	{
		int diff;

		// when focus goes left, xO goes right
		if (xO >= this->maxX)
		{
			diff = std::abs(xO - this->xO) - int(this->maxX / 2) + 1 - (this->maxX & 1);
		}
		else
		{
			diff = 1;
		}

		for (int i = std::min(xO, this->maxX) - 1; i >= 0; i--)
		{
			this->setAxisXPeace(i, yO, diff);
			diff++;
		}

		// when focus goes right, xO goes left
		if (xO < 0)
		{
			diff = std::abs(xO - this->xO) - int(this->maxX / 2);
		}
		else
		{
			diff = 1;
		}

		for (int i = std::max(0, xO + 1); i < this->maxX; i++)
		{
			this->setAxisXPeace(i, yO, diff);
			diff++;
		}
	}
}


void CoordinateSystemXY::buildAxisY(int xO, int yO)
{
	int diff, tmp;

	if (xO >= 0 && xO < this->maxX)
	{
		// when focus goes up, yO goes down
		if (yO >= this->maxY)
		{
			diff = std::abs(yO - this->yO) - int(this->maxY / 2) + 1 - (this->maxY & 1);
		}
		else
		{
			diff = 1;
		}

		for (int i = std::min(yO, this->maxY) - 1; i >= 0; i--)
		{
			this->setAxisYPeace(xO, i, diff);
			diff++;
		}

		// when focus goes down, yO goes up
		if (yO < 0)
		{
			diff = std::abs(yO - this->yO) - int(this->maxY / 2);
		}
		else
		{
			diff = 1;
		}

		for (int i = std::max(0, yO + 1); i < this->maxY; i++)
		{
			this->setAxisYPeace(xO, i, diff);
			diff++;
		}
	}
}

void CoordinateSystemXY::attachFocus()
{
	int focusCenter = int(this->maxY / 2) * this->maxX + int(this->maxX / 2);
	this->content[focusCenter - 1] = '<';
	this->content[focusCenter + 1] = '>';
}

void CoordinateSystemXY::buildCoordinateSystem(int xO, int yO)
{
	this->buildAxisX(xO, yO);
	this->buildAxisY(xO, yO);
	this->setStartPointOfOXY(xO, yO);
	this->attachFocus();
}

void CoordinateSystemXY::initializeCoordinateSystem()
{
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->xO, this->yO);
	this->attachXXFunction();
}

void CoordinateSystemXY::goLeft(int step)
{
	this->focusX += step;
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goRight(int step)
{
	this->focusX -= step;
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goTop(int step)
{
	this->focusY += step;
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goBottom(int step)
{
	this->focusY -= step;
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}