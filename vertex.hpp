#include <iostream>
using namespace std;

#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
    public:
    int x, y;

    Vertex(int x, int y);
    int getX();
    int getY();
};

#endif