#include "cityMapCoords.h"

cityMapCoords::cityMapCoords(const cityMapCoords& city)
{
    xCoord = city.getX();
    yCoord = city.getY();
}

const cityMapCoords& cityMapCoords::operator= (const cityMapCoords& city)
{
    if(this != &city)
    {
        xCoord = city.getX();
        yCoord = city.getY();
    }
    return *this;
}

int cityMapCoords::getX() const
{
    return xCoord;
}

void cityMapCoords::setX(int xCoordinate)
{
    xCoord = xCoordinate;
}

int cityMapCoords::getY() const
{
    return yCoord;
}

void cityMapCoords::setY(int yCoordinate)
{
    yCoord = yCoordinate;
}