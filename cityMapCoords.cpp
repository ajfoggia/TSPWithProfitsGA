#include "cityMapCoords.h"

cityMapCoords::cityMapCoords(const cityMapCoords& aCity)
{
    xCoord = aCity.getX();
    yCoord = aCity.getY();
}

const cityMapCoords& cityMapCoords::operator= (const cityMapCoords& aCity)
{
    if(this != &aCity)
    {
        xCoord = aCity.getX();
        yCoord = aCity.getY();
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