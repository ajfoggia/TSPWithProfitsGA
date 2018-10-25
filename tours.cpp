#include <iostream>
#include "tours.h"
#include "tourChroms.h"

tours::tours()
{
    // Initialize our arrays.
    firstTourArray = NULL;
    secondTourArray = NULL;

    arraySpaceSwap = true;  // Since we start with using the firstTourArray, we set the flag to true.

    // Other initializations.
    tourArrayCapacity = 0;
    tourCount = 0;
    toursCreated = 0;
}

tours::~tours()
{
    // This simply checks to make sure nothing is in the arrays that should not be there!
    // If there happens to be stuff left, clean it out.
    if(firstTourArray != NULL)
    {
        delete[] firstTourArray;
    }
    if(secondTourArray != NULL)
    {
        delete[] secondTourArray;
    }
}

int tours::getTourCount() const
{
    return tourCount;  // Getter function to retrieve the number of tours.
}

void tours::expandArray()
{
    // This function helps keep an updated list of the tours by swapping the chromosomes
    // between two arrays.

    // When the flag is true, we are using the firstTourArray to hold the data.
    // When firstTourArray gets too small, we recreate the secondTourArray to hold
    // twice the capacity as the first array and then we transfer the chromosomes to
    // that array.
    if(arraySpaceSwap == true)
    {
        if(tourArrayCapacity == 0) // If the array capacity is not hit, update the capacity.
        {
            secondTourArray = new tourChroms[1];
            tourArrayCapacity = 1;
        }
        else  // Otherwise, the capacity of the first array was hit and we need to make the new array.
        {
            secondTourArray = new tourChroms[tourArrayCapacity * 2];  // Create the new array with twice the capacity.
            tourArrayCapacity *= 2;  // Update the overall capacity.

            for(int i = 0; i <= tourCount - 1; i++)  // For all the tours we have...
            {
                secondTourArray[i] = firstTourArray[i];  // Transfer the chromosomes to the new array.
            }
        }

        arraySpaceSwap = false;    // Now we flip the flag because we will use the new array to hold chromosomes now.

        if(firstTourArray != NULL)  // Clear out the first array for re-use.
        {
            delete[] firstTourArray;
            firstTourArray = NULL;
        }
    }
    // When the flag is false, we are using the secondTourArray to hold the data.
    // When secondTourArray gets too small, we recreate the firstTourArray to hold
    // twice the capacity as the previous array and then we transfer the chromosomes to
    // that array.
    else
    {
        if(tourArrayCapacity == 0)  // If the array capacity is not hit, update the capacity.
        {
            firstTourArray = new tourChroms[1];
            tourArrayCapacity = 1;
        }
        else  // Otherwise, the capacity of the second array was hit and we need to make the new array.
        {
            firstTourArray = new tourChroms[tourArrayCapacity * 2];  // Create the new array with twice the capacity.
            tourArrayCapacity *= 2;  // Update the overall capacity.

            for(int i = 0; i <= tourCount - 1; i++)  // For all the tours we have...
            {
                firstTourArray[i] = secondTourArray[i];  // Transfer the chromosomes to the new array.
            }
        }

        arraySpaceSwap = true;  // Now we flip the flag back because we will use the first array to hold chromosomes now.
        if(secondTourArray != NULL)  // Clear out the second array for re-use.
        {
            delete[] secondTourArray;
            secondTourArray = NULL;
        }
    }
}

int tours::addTour(const tourChroms &newChromo)
{
    int tourIndex;  // Variable that holds the index of the tour being added.

    if(tourCount >= tourArrayCapacity - 1)  // If the array does not have space to hold the new tour....
    {
        expandArray();  // Expand it to make space.
    }

    if(arraySpaceSwap == true)  // If the flag is true, then we insert the tour into the firstTourArray.
    {
        firstTourArray[tourCount] = newChromo;
    }
    else  // Otherwise the flag is false which means we insert the tour into the secondTourArray.
    {
        secondTourArray[tourCount] = newChromo;
    }

    tourIndex = tourCount;  // Set the index of the tour in the array.
    tourCount += 1;  // Increase the total tour count.
    toursCreated += 1;  //  Increase the number of tours created.

    return tourIndex;  // Return the index of the tour in the array.
}

void tours::getTour(int index, tourChroms &aChromosome)
{
    if(arraySpaceSwap == true)  // If the flag is true, we grab the tour from the first array.
    {
        aChromosome = firstTourArray[index];
    }
    else  // Otherwise, we are grabbing the tour from the second array.
    {
        aChromosome = secondTourArray[index];
    }
}

void tours::setTour(int index, tourChroms &aChromosome)
{
    if(arraySpaceSwap == true)  // If the flag is true, we refresh the data of the tour from the first array.
    {
        firstTourArray[index] = aChromosome;
    }
    else  // Otherwise, we are refreshing the data of the tour from the second array.
    {
        secondTourArray[index] = aChromosome;
    }
}