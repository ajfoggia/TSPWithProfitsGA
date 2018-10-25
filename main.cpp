// Alex Foggia
// This program uses a genetic algorithm to find a possible solution to an instance of
// the Traveling Salesman Problem.
// Two different types of selection: roulette & tournament
// Crossover: partially mapped
// Mutation: simple exchange of two numbers in the permutation.

#include "GA.h"
#include "globals.h"
#include "cityMapCoords.h"
#include "tours.h"
#include "tourChroms.h"

int main()
{
    tours population;  // Create tours object to hold our population of chromosomes (tours).
    cityMapCoords coordinates[maxCities];  // Create an array of cityMapCoords objects to hold each city's coordinates.

    srand((unsigned)time(0));  // Seed the random number generator.

    initializeMap(coordinates);  // Create the coordinates of cities.

    geneticAlgorithm(population, coordinates);  // Start the algorithm to find the best tour.

    return 0;
}