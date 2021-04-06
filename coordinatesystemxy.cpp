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

void CoordinateSystemXY::setAxisXPeace(int screenY, int screenX, int difference)
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

void CoordinateSystemXY::buildAxisX(int xO, int yO)
{
	if (yO >= 0 && yO < this->maxY)
	{
		int diff;

		// when focus goes to left, xO goes to right
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
			this->setAxisXPeace(yO, i, diff);
			diff++;
		}

		// when focus goes to right, xO goes to left
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
			this->setAxisXPeace(yO, i, diff);
			diff++;
		}
	}
}


void CoordinateSystemXY::buildAxisY(int xO, int yO)
{
	// todo: replace building of Y-axis here from buildCoordinateSystem method
	int diff, tmp;

	if (xO >= 0 && xO < this->maxX)
	{
		/* OY */
		// i < yO
		diff = 1;
		for (int i = yO - 1; i >= 0; i--)
		{
			tmp = diff % this->numOfAllPiecesOfAxisInterval;
			if (tmp % (this->numOfIntermediateSpaces + 1))
			{
				this->content[i * this->maxX + xO] = '|';
			}
			else
			{
				if (tmp)
				{
					this->content[i * this->maxX + xO] = '+';
				}
				else
				{
					this->content[i * this->maxX + xO] = '=';
				}
			}		
			diff++;
		}

		// i = yO
		this->content[yO * this->maxX + xO] = 'O';

		// i > yO
		diff = 1;
		for (int i = yO + 1; i < this->maxY; i++)
		{
			tmp = diff % this->numOfAllPiecesOfAxisInterval;
			if (tmp % (this->numOfIntermediateSpaces + 1))
			{
				this->content[i * this->maxX + xO] = '|';
			}
			else
			{
				if (tmp)
				{
					this->content[i * this->maxX + xO] = '+';
				}
				else
				{
					this->content[i * this->maxX + xO] = '=';
				}
			}		
			diff++;
		}
		/* OY */
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
	this->attachFocus();
}

void CoordinateSystemXY::initializeCoordinateSystem()
{
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->xO, this->yO);
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
	this->focusY = std::min(this->maxY - 1, this->focusY + step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goBottom(int step)
{
	this->focusY = std::max(0, this->focusY - step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}