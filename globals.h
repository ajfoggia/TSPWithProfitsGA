#ifndef QAPGENETICALGORITHM_GLOBALS_H
#define QAPGENETICALGORITHM_GLOBALS_H

const int populationStartSize = 25;      // Population size at start.
const int maxGenerations = 100;     // Arbitrary number of test generations.
const double R_RATE = 0.7;      // Probability of two chromosomes mating.
const double mutationChance = 0.01;    // Mutation Rate.
const int minParentsSelected = 10;      // Minimum parents allowed for selection.
const int maxParentsSelected = 20;      // Maximum parents allowed for selection.
const int offspringCreated = 15;          // New offspring created per generation. (Needs to be < maxParentsSelected.)
const int minChromosomeShuffles = 8;     // For randomizing starting chromosomes.
const int maxChromosomeShuffles = 20;

// These last four are all dependent on each other.
// Any one can't be modified without having to recalculate the others.
const int maxCities = 8;
const double TARGET = 86.6299;  // Number for algorithm to find.
const int X_LOCS[] = {30, 40, 40, 29, 19, 9, 9, 20};
const int Y_LOCS[] = {5, 10, 20, 25, 25, 19, 9, 5};

#endif //QAPGENETICALGORITHM_GLOBALS_H