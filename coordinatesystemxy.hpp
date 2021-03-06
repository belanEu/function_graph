#include <iostream>
#include "defs.hpp"

#ifndef COORDINATE_SYSTEM_XY_H
#define COORDINATE_SYSTEM_XY_H

class CoordinateSystemXY
{
    public:
    int xO, yO, // initial values of coordinates of coordinate system start
        focusX, focusY; // actual values of coordinates of focus point
    int maxX, maxY;

    /* values for description of axis interval which is (i, j], i=0,1,2,... and j=i+1 */
    int numOfIntermediateSpaces, // number of intermediate spaces between axis divisions
        numOfAxisDivisions,
        numOfAllPiecesOfAxisInterval;
    
    float step; // value of division step: 1, 1/2, 1/5, 1/10
    
    char *content = nullptr; // array of ascii symbols which represents coordinate system
    

    public:
    CoordinateSystemXY(int xO, int yO, int maxX, int maxY, int numOfIntermediateSpaces, float step);

    ~CoordinateSystemXY()
    {
        delete[] this->content;
    }

    void initializeCoordinateSystem();
    void goLeft();
    void goRight();
    void goTop();
    void goBottom();

    protected:
    void clearCoordinateSystem();
    void buildCoordinateSystem(int xO, int yO);
    void setAxisXPeace(int screenX, int screenY, int difference);
    void setAxisYPeace(int screenX, int screenY, int difference);
    void setStartPointOfOXY(int screenX, int screenY);
    void buildAxisX(int xO, int yO);
    void buildAxisY(int xO, int yO);
    void attachFocus();

    void attachFunction(int xO, int yO);
    void attachXXFunction(int xO, int yO);
};

#endif