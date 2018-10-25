#ifndef QAPGENETICALGORITHM_MAINCODE_H
#define QAPGENETICALGORITHM_MAINCODE_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "tours.h"
#include "cityMapCoords.h"

void    initializeMap(cityMapCoords map[]);
void    initializeChromosomes(tours &population, cityMapCoords map[], int &mutationCount);
void    geneticAlgorithm(tours &population, cityMapCoords map[]);
void    getFitness(tours &population);
void    rouletteSelection(tours &population);
int     tournamentSelection(tours &population);
void    mating(tours &population, cityMapCoords map[], int &nextMutation, int &offspringCount, int &mutationCount);
void    partiallyMappedCrossover(tours &population, int firstChrom, int secondChrom, int &OffspringIndex);
void    exchangeMutation(tours &population, int index, int exchanges, int &mutationCount);
void    prepNextGen(tours &population);
void    printBestFromPopulation(tours &population);
int     getRandomNumber(int low, int high);
void    getTotalDistance(tours &population, cityMapCoords map[], int chromoIndex);
double  getDistance(cityMapCoords map[], int firstCity, int secondCity);
int     minimum(tours &population);

#endif //QAPGENETICALGORITHM_MAINCODE_H
