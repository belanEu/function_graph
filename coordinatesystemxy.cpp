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

void CoordinateSystemXY::buildAxisX(int xO, int yO)
{
	// todo: replace building of X-axis here from buildCoordinateSystem method
	int diff, tmp;

	/* OX */
	// i < xO
	diff = 1;
	for (int i = xO - 1; i >= 0; i--)
	{
		tmp = diff % this->numOfAllPiecesOfAxisInterval;
		if (tmp % (this->numOfIntermediateSpaces + 1))
		{
			this->content[yO * this->maxX + i] = '-';
		}
		else
		{
			if (tmp)
			{
				this->content[yO * this->maxX + i] = '+';
			}
			else
			{
				this->content[yO * this->maxX + i] = '|';
			}
		}		
		diff++;
	}

	// i > xO
	diff = 1;
	for (int i = xO + 1; i < this->maxX; i++)
	{
		tmp = diff % this->numOfAllPiecesOfAxisInterval;
		if (tmp % (this->numOfIntermediateSpaces + 1))
		{
			this->content[yO * this->maxX + i] = '-';
		}
		else
		{
			if (tmp)
			{
				this->content[yO * this->maxX + i] = '+';
			}
			else
			{
				this->content[yO * this->maxX + i] = '|';
			}
		}		
		diff++;
	}
	/* OX */
}


void CoordinateSystemXY::buildAxisY(int xO, int yO)
{
	// todo: replace building of Y-axis here from buildCoordinateSystem method
	int diff, tmp;

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
	this->focusX = std::min(this->maxX - 1, this->xO + step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goRight(int step)
{
	this->focusX = std::max(0, this->xO - step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goTop(int step)
{
	this->focusY = std::min(this->maxY - 1, this->yO + step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}

void CoordinateSystemXY::goBottom(int step)
{
	this->focusY = std::max(0, this->yO - step);
	this->clearCoordinateSystem();
	this->buildCoordinateSystem(this->focusX, this->focusY);
}