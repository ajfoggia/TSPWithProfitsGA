#ifndef QAPGENETICALGORITHM_CITYMAPCOORDS_H
#define QAPGENETICALGORITHM_CITYMAPCOORDS_H

#include "globals.h"

class cityMapCoords
{

private:
    int xCoord;   // Variable that holds the x-coordinate of a city.
    int yCoord;   // Variable that holds the y-coordinate of a city.
    int cProfits; // Variable that holds the profit of a city.

public:
    cityMapCoords(){};
    cityMapCoords(const cityMapCoords& city);                    // Initializes a city's coordinates.
    const cityMapCoords& operator= (const cityMapCoords& city);  // Overload assignment operator.
    int getX() const;                                            // Getter function that gets a city's x-coordinate.
    void setX(int xCoordinate);                                  // Setter function that sets a city's x-coordinate.
    int getY() const;                                            // Getter function that gets a city's y-coordinate.
    void setY(int yCoordinate);                                  // Setter function that sets a city's y-coordinate.
    int getProfit() const;                                       // Getter function that gets a city's profit.
    void setProfit(int cProfit);                                 // Setter function that sets a city's profit.

};

#endif //QAPGENETICALGORITHM_CITYMAPCOORDS_H
