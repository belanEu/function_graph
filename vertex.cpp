#include "vertex.hpp"

Vertex::Vertex(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Vertex::getX()
{
    return this->x;
}

int Vertex::getY()
{
    return this->y;
}