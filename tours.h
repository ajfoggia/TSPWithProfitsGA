#ifndef QAPGENETICALGORITHM_TOURS_H
#define QAPGENETICALGORITHM_TOURS_H

#include "tourChroms.h"

class tours
{

private:

    // Flag used to switch which array we are using.
    // This happens when another tour is added and we have reached capacity in the current array.
    bool arraySpaceSwap; 
    
    tourChroms * firstTourArray;   // First array for the tours.
    tourChroms * secondTourArray;   // Second array for the tours, used when firstTourArray reaches capacity.

    int tourCount;  // Variable that keeps track of the amount of tours.
    int tourArrayCapacity;  // Variable that holds the current array capacity.
    int toursCreated;  // Variable that keeps track of the amount of tours created.

    // This is only called when either firstArray or secondArray runs out of space.
    // So this function simply moves one array's chromosomes into the other after increasing the space
    // in the other array.
    void expandArray();

public:
    tours();  // Constructor
    ~tours();  // Destructor
    int     getTourCount() const;  // Returns the number of chromosomes in the population.
    int     addTour(const tourChroms &newChromo);  // Adds a chromosome to the population.
    void    getTour(int index, tourChroms &aChromosome);  // Retrieves a chromosome from the population.
    void    setTour(int index, tourChroms &aChromosome);  // Saves changes to a chromosome in the population.
};

#endif //QAPGENETICALGORITHM_TOURS_H
