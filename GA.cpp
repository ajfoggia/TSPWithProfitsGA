#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

#include "tours.h"
#include "cityMapCoords.h"
#include "GA.h"

void geneticAlgorithm(tours &population, cityMapCoords map[])
{
    int currentGen = 0;  // Variable to hold the current generation.
    int offspringCount = 0;  // Variable to hold the number of offspring we have generated so far.
    int nextMutation;  // Variable that holds the decision of when we perform the next mutation.
    int mutations = 0;  // Variable that holds the number of mutations we performed.
    int popSize;  // Variable that holds the population size.
    tourChroms currentChrom;  // Variable that allows us to access our chromosome information.
    bool done = false;  // Flag to signify when we are done. Did we reach the target or max generations?

    initializeChromosomes(population, map, mutations);  // Create each starting chromosome.

    mutations = 0;  // Re-initialize mutations since we mutated the starting chromosomes.

    nextMutation = getRandomNumber(0, static_cast<int>(1 / mutationChance));  // Decide when we mutate next.

    while(currentGen < maxGenerations)
    {
        getFitness(population);  // Grab the populations fitness'.

        rouletteSelection(population);  // Perform our selection.

        mating(population, map, nextMutation, offspringCount, mutations);  // Now we mate our chromosomes.

        prepNextGen(population);  // Prepare the next population with our offspring.

        currentGen += 1;  // Update the number of generations.

        std::cout << "Generation: " << currentGen << endl;
    }

    std::cout << "\nThe Tours from the Final Generation " << currentGen;
    std::cout << "\n--------------------------\n";
    printBestFromPopulation(population);  // Print the final chromosomes.

    std::cout << "\nThe best option in this case is: ";
    population.getTour(minimum(population), currentChrom);
    // Print the chromosome.
    for(int j = 0; j <= maxCities - 1; j++)
    {
        if (j == maxCities - 1)
        {
            std::cout << currentChrom.getData(j);
        }
        else
        {
            std::cout << currentChrom.getData(j) << " -> ";
        }
    }
    std::cout << "\n";

    std::cout << "Completed " << currentGen << " Generations.\n";
    std::cout << "Encountered " << mutations << " mutations in " << offspringCount << " offspring.\n";
}

void initializeMap(cityMapCoords map[])
{
    cityMapCoords city;  // Create a city object to set the coordinates of each city.

    for(int i = 0; i <= maxCities - 1; i++)  // For every city....
    {
        city.setX(X_LOCS[i]);  // Set the x-coordinate.
        city.setY(Y_LOCS[i]);  // Set the y-coordinate.
        map[i] = city;  // Add that (x, y) point to the map.
    }
}

void initializeChromosomes(tours &population, cityMapCoords map[], int &mutationCount)
{
    int shuffles;  // Variable that holds the number of swaps the mutation performs on the initial chromosomes.
    int chromoIndex;  // Variable that holds the index of the chromosome currently being created in the population.

    for(int i = 0; i <= populationStartSize - 1; i++)  // For every chromosome in our population.
    {
        tourChroms currentChrom;  // Variable that holds the current chromosome we are making.

        for(int j = 0; j <= maxCities - 1; j++)  // For as many cities as we have...
        {
            currentChrom.setData(j, j);  // Start by assigning each index to that city number.
        }

        chromoIndex = population.addTour(currentChrom);  // Add that chromosome to our population.

        // Randomly choose the number of city shuffles to perform.
        shuffles = getRandomNumber(minChromosomeShuffles, maxChromosomeShuffles);

        // Mutate the chromosome.
        exchangeMutation(population, chromoIndex, shuffles, mutationCount);

        // Get the total distance of the resulting chromosome.
        getTotalDistance(population, map, chromoIndex);

    }
}

void getFitness(tours &population)
{
    int popSize;  // Variable that holds the population size.
    tourChroms currentChrom;  // Variable that allows us to access each chromosomes attributes and their functions.
    double bestScore;  // Variable that holds the best tour.
    double worstScore;  // Variable that holds the worst tour.

    popSize = population.getTourCount();  // Get how many chromosomes we have in our population.

    population.getTour(maximum(population), currentChrom);  // Get the chromosome that has the longest tour.
    worstScore = abs(TARGET - currentChrom.getTotal());  // Use the worst tour to calculate the worst fitness.

    population.getTour(minimum(population), currentChrom);  // Get the chromosome that has the shortest tour.
    bestScore = worstScore - abs(TARGET - currentChrom.getTotal());  // Find how much closer this chromosome is compared to the farthest tour.

    // Now we can calculate how good all the other chromosomes are.
    for(int i = 0; i <= popSize - 1; i++)
    {
        population.getTour(i, currentChrom);

        currentChrom.setFitness(currentChrom.getTotal());

        population.setTour(i, currentChrom);
    }
}

void rouletteSelection(tours &population)
{
    int popSize;  // Variable that holds the population size.
    int selectCounter;  // Variable that increments to check which chromosomes are selected.
    int maximumToSelect;  // Variable that holds how many chromosomes from the population we will allow to select.
    int rouletteSpin;  // Variable that holds our roulette spin.
    double genTotal = 0;  // Variable that holds our generations total fitness.
    double selTotal;  // Variable that holds the probability of the current chromosome to see if it is chosen.
    tourChroms currentChromo;  // Variable that allows access to any chromosome.
    tourChroms selectedChromo;  // Variable that allows access to the chromosomes selected.
    bool done;  // Flag to check if we are done checking a chromosome for selection.

    // Get how many chromosomes are in our population.
    popSize = population.getTourCount();

    // For every chromosome, we grab its tour and add its fitness to the total.
    for(int i = 0; i <= popSize - 1; i++)
    {
        population.getTour(i, currentChromo);
        genTotal += currentChromo.getFitness();
    }

    genTotal *= 0.01;  // Convert our populations total fitness to a decimal for our roulette spins.

    // Now we set the probability that each chromosome will be picked by the roulette wheel.
    for(int i = 0; i <= popSize - 1; i++)
    {
        population.getTour(i, currentChromo);
        currentChromo.setSelectionProbability(currentChromo.getFitness() / genTotal);
        population.setTour(i, currentChromo);
    }

    // Now we randomly select how many chromosomes we will allow to be selected for the reduced population.
    maximumToSelect = getRandomNumber(minParentsSelected, maxParentsSelected);

    // For however many chromosomes we are selecting, spin the wheel and get a chromosome.
    for(int i = 0; i <= maximumToSelect - 1; i++)
    {
        rouletteSpin = getRandomNumber(0, 99);  // Spin the wheel.
        selectCounter = 0;  // Variable that keeps track of which chromosome we are looking at selecting.
        selTotal = 0.0;  // Variable that holds the total selection probability of a chromosome.
        done = false;  // Flag to mark when we are done selecting our chromosomes.
        
        do
        {
            population.getTour(selectCounter, currentChromo);  // Lets grab a chromosome to check and see if it is chosen.
            selTotal += currentChromo.getSelectionProbability();  // Get its selection probability.
            if (selTotal >= rouletteSpin)  // If the probability is greater than or equal to our wheel spin...
            {
                if (selectCounter == 0)  // If it is the first chromosome.
                {
                    population.getTour(selectCounter, selectedChromo);  // Get its tour data.
                    selectedChromo.setSelected(true);  // Flag that it is a selected chromosome.
                    population.setTour(selectCounter, selectedChromo);  // Then set it.
                }
                else if (selectCounter >= popSize - 1)  // Else if the counter ends up being greater than or equal to the popsize...
                {
                    population.getTour(popSize - 1, selectedChromo);  // Get the tour data of the last chromosome.
                    selectedChromo.setSelected(true);  // Flag that it is a selected chromosome.
                    population.setTour(popSize - 1, selectedChromo);  // Then set it.
                }
                else  // Otherwise, it is another chromosome in the population.
                {
                    population.getTour(selectCounter - 1, selectedChromo);  // Get the tour data of that chromosome.
                    selectedChromo.setSelected(true);  // Flag that it is a selected chromosome.
                    population.setTour(selectCounter - 1, selectedChromo);  // Then set it.
                }

                done = true;  // Flag this iteration as done.

            }
            else  // Otherwise this chromosome is not selected so lets increment to look at the next one.
            {
                selectCounter += 1;
            }

        }while (!done);

    }
}

void mating(tours &population, cityMapCoords map[], int &nextMutation, int &offspringCount, int &mutationCount)
{
    int getRand;  // Variable to hold the random number we generate.
    int numberOfCitySwaps;  // Variable that holds the number of cities swaps that occurred.
    int firstParent;  // Variable that holds the index of the first parent.
    int secondParent;  // Variable that holds the index of the second parent.
    int newOffspringIndex;  // Variable that holds the index of the new offspring.
    tourChroms offspringChrom;  // Variable to hold the new offspring.

    // Lets create our offspring.
    for(int i = 0; i <= offspringCreated - 1; i++)
    {
        firstParent = tournamentSelection(population);  // Grab the first parent used for the offspring.

        getRand = getRandomNumber(0, 100);  // Will this parent get to mate?

        if(getRand <= R_RATE * 100)  // If this parent is able to mate....
        {
            secondParent = tournamentSelection(population);  // Grab the second parent.

            newOffspringIndex = population.addTour(offspringChrom);  // Used to hold the index of the offspring chromosome.

            // Perform the crossover now that we have both parents.
            partiallyMappedCrossover(population, firstParent, secondParent, newOffspringIndex);

            if(offspringCount == nextMutation)  //If this offspring is able to mutate in the process...
            {
                // Get the number of swaps to perform for mutation.
                numberOfCitySwaps = getRandomNumber(0, maxCities - 1);

                // Now we perform the mutation on the offspring.
                exchangeMutation(population, newOffspringIndex, numberOfCitySwaps, mutationCount);
            }

            getTotalDistance(population, map, newOffspringIndex);  //Get the distance of the new offspring tour.

            offspringCount += 1;  // We created an offspring, lets make sure we keep track of that!

            // We need to schedule the next time another offspring gets mutated.
            if(offspringCount % static_cast<int>(1 / mutationChance) == 0)
            {
                // So lets pick the next time we perform a mutation.
                nextMutation = offspringCount + getRandomNumber(0, static_cast<int>(1 / mutationChance));
            }
        }
    }
}

int tournamentSelection(tours &population)
{
    bool done = false;  // Variable that flags when a valid parent is found.

    // Variables that hold the random index choices for the parents in the tournament.
    int firstIndexChoice = 0;
    int secondIndexChoice = 0;

    // Variables that hold the fitness' for the parents.
    double firstFitness;
    double secondFitness;

    // Variables that hold the parent chromosomes.
    tourChroms firstParentSelection;
    tourChroms secondParentSelection;

    while (!done)
    {
        // Grab random index number for the first parent in the tournament.
        firstIndexChoice = getRandomNumber(0, population.getTourCount() - 1);
        population.getTour(firstIndexChoice, firstParentSelection);  // Grab the chromosome.
        if (firstParentSelection.getSelected())  // If that chromosome is one selected from roulette...
        {
            done = true;  // We have one parent.
        }
    }

    done = false;

    while (!done)
    {
        // Grab random index number for the first parent in the tournament.
        secondIndexChoice = getRandomNumber(0, population.getTourCount() - 1);
        population.getTour(secondIndexChoice, secondParentSelection);  // Grab the chromosome.
        if (secondParentSelection.getSelected())  // If that chromosome is one selected from roulette...
        {
            done = true;  // We have one parent.
        }
    }

    // Now that we have the parent indexes, lets get the fitness'

    population.getTour(firstIndexChoice, firstParentSelection);  // Grab the first chromosome.
    firstFitness = firstParentSelection.getFitness();  // Get its fitness value.

    population.getTour(secondIndexChoice, secondParentSelection);  // Grab the second chromosome.
    secondFitness = secondParentSelection.getFitness();  // Get its fitness value.

    // If the first parent's fitness is larger than or equal to the second
    // parent's fitness, it won the tournament and we want that index.
    if (firstFitness >= secondFitness)
    {
        return firstIndexChoice;
    }
    else  // Else the second parent is better and we want that one.
    {
        return secondIndexChoice;
    }
}

void partiallyMappedCrossover(tours &population, int firstChrom, int secondChrom, int &OffspringIndex)
{
    // Variable that is used to swap the crosspoints. (Only if the second crosspoint is smaller than the first.)
    int crosspointSwap;

    // Variables that hold the crosspoints.
    int crossPoint1;
    int crossPoint2;

    // Variables that hold the cities that are getting swapped.
    int swapCity1;
    int swapCity2;

    // Variables that hold the positions of the swapped cities in the offspring.
    int swapOffspringPos1;
    int swapOffspringPos2;

    // Variables that grant access to the chromosomes tours and data.
    tourChroms chrom1;
    tourChroms chrom2;
    tourChroms offspringChrom;

    // Get the tours for our chromosomes.
    population.getTour(firstChrom, chrom1);
    population.getTour(secondChrom, chrom2);
    population.getTour(OffspringIndex, offspringChrom);

    // Get the random crosspoints we will use.
    crossPoint1 = getRandomNumber(0, maxCities - 1);
    crossPoint2 = getRandomNumber(0, maxCities - 1);

    // We want to make sure they are not the same!
    // This loop really should not enter at all (at most once).
    // The loop just ensures we get two different crosspoints for sure.
    while (crossPoint1 == crossPoint2)
    {
        crossPoint2 = getRandomNumber(0, maxCities - 1);
    }

    // If our second crosspoint is before our first crosspoint, lets just swap them so everything is back to normal.
    if(crossPoint2 < crossPoint1)
    {
        crosspointSwap = crossPoint1;  // Let the farther crosspoint be put in a temp variable to swap.
        crossPoint1 = crossPoint2;  // Give the smallest crosspoint to the first crosspoint variable.
        crossPoint2 = crosspointSwap;  // Now we can give the further point to the second crosspoint variable.
    }

    // Now we copy the first parents data into the offspring.
    for(int i = 0; i <= maxCities - 1; i++)
    {
        offspringChrom.setData(i, chrom1.getData(i));
    }

    // Now we grab two cities to swap at a time, one from each parent within the crosspoints.
    for(int i = crossPoint1; i <= crossPoint2; i++)
    {
        //Get the two cities to swap.
        swapCity1 = chrom1.getData(i);
        swapCity2 = chrom2.getData(i);

        //Get the positions of those cities in the offspring.
        for(int j = 0; j <= maxCities - 1; j++)
        {
            if(offspringChrom.getData(j) == swapCity1)  // If the first city being swapped is found...
            {
                swapOffspringPos1 = j;  // Get its position.
            }
            else if(offspringChrom.getData(j) == swapCity2)  // If the second city being swapped is found...
            {
                swapOffspringPos2 = j;  // Get its position.
            }
        }

        // As long as it is not the same city, we can swap them.
        if(swapCity1 != swapCity2)
        {
            offspringChrom.setData(swapOffspringPos1, swapCity2);
            offspringChrom.setData(swapOffspringPos2, swapCity1);
        }

    }

    // Then we save the offspring's resulting tour.
    population.setTour(OffspringIndex, offspringChrom);
}

void exchangeMutation(tours &population, int index, int exchanges, int &mutationCount)
{
    int i;
    int tempData;
    int firstCity;
    int secondCity;
    tourChroms thisChromo;
    bool done = false;

    population.getTour(index, thisChromo);
    i = 0;
    while(!done)
    {
        firstCity = getRandomNumber(0, maxCities - 1);
        secondCity = getRandomNumber(0, maxCities - 1);

        // We want to make sure they are not the same!
        // This loop really should not enter at all (at most once).
        // The loop just ensures we get two different genes for sure.
        while (firstCity == secondCity)
        {
            secondCity = getRandomNumber(0, maxCities - 1);
        }

        // Exchange the chosen genes.
        tempData = thisChromo.getData(firstCity);
        thisChromo.setData(firstCity, thisChromo.getData(secondCity));
        thisChromo.setData(secondCity, tempData);

        if(i == exchanges)
        {
            done = true;
        }
        i += 1;
    }
    population.setTour(index, thisChromo);

    mutationCount += 1;
}

void prepNextGen(tours &population)
{
    int popSize;  // Variable that holds the population size.
    tourChroms thisChromo;

    // Reset flags for selected individuals.
    popSize = population.getTourCount();
    for(int i = 0; i <= popSize - 1; i++)
    {
        population.getTour(i, thisChromo);
        thisChromo.setSelected(false);
        population.setTour(i, thisChromo);
    }
}

void printBestFromPopulation(tours &population)
{
    int popSize;  // Variable that holds the size of the population of chromosomes.
    tourChroms currentChrom;  // Variable that creates a chromosome object to access its functions.

    popSize = population.getTourCount();  // Get the size of the population.

    for(int i = 0; i <= popSize - 1; i++)  // For every chromosome in the population...
    {
        population.getTour(i, currentChrom);  // Grab the chromosome.

        if(currentChrom.getFitness() > 80.0)  // If the chromosome's fitness is better than 80...
        {
            std::cout << "\nPath of the salesman: ";
            for(int j = 0; j <= maxCities - 1; j++)  // Print out the tour.
            {
                if (j == maxCities - 1)
                {
                    std::cout << currentChrom.getData(j);
                }
                else
                {
                    std::cout << currentChrom.getData(j) << " -> ";
                }
            }

            std::cout << "\n\nDistance(fitness) of Tour = " << currentChrom.getTotal();
        }
    }
}

int getRandomNumber(int low, int high)
{
    //Generate random value between low and high.
    return (rand() % ((high + 1) - low)) + low;
}

void getTotalDistance(tours &population, cityMapCoords map[], int chromoIndex)
{
    tourChroms currentChromo;
    double temp;

    population.getTour(chromoIndex, currentChromo);

    for(int i = 0; i <= maxCities - 1; i++)
    {
        if(i == maxCities - 1)
        {
            temp = currentChromo.getTotal();
            temp += getDistance(map, currentChromo.getData(maxCities - 1), currentChromo.getData(0));
            currentChromo.setTotal(temp);
        }
        else
        {
            temp = currentChromo.getTotal();
            temp += getDistance(map, currentChromo.getData(i), currentChromo.getData(i + 1));
            currentChromo.setTotal(temp);
        }
    }

    population.setTour(chromoIndex, currentChromo);
}

double getDistance(cityMapCoords map[], int firstCity, int secondCity)
{
    // Variables that allow us to access the values and functions for the city's map coordinates.
    cityMapCoords cityOne;
    cityMapCoords cityTwo;

    // Variables that hold the X-coordinate and Y-coordinate distances from the two cities.
    double cityXDistance;
    double cityYDistance;

    cityOne = map[firstCity];  // Get the first city so we have its coordinates.
    cityTwo = map[secondCity];  // Get the second city so we have its coordinates.

    // Applying the distance formula here... sqrt((x1-x2)^2 + (y1-y2)^2)
    cityXDistance = pow(abs(cityOne.getX() - cityTwo.getX()), 2);  // Get the difference in X-coordinate values.
    cityYDistance = pow(abs(cityOne.getY() - cityTwo.getY()), 2);  // Get the difference in Y-coordinate values.

    return sqrt(cityXDistance + cityYDistance);  // Now square root the result for our distance.

}

int minimum(tours &population)
{
    //Returns an array index.
    int popSize;  // Variable that holds the population size.
    int winner = 0;
    tourChroms thisChromo;
    tourChroms thatChromo;
    bool foundNewWinner;
    bool done = false;

    do
    {
        foundNewWinner = false;
        popSize = population.getTourCount();
        for(int i = 0; i <= popSize - 1; i++)
        {
            if(i != winner)             // Avoid self-comparison.
            {
                population.getTour(i, thisChromo);
                population.getTour(winner, thatChromo);
                // The maximum has to be in relation to the Target.
                if(abs(TARGET - thisChromo.getTotal()) <
                   abs(TARGET - thatChromo.getTotal()))
                {
                    winner = i;
                    foundNewWinner = true;
                }
            }
        }

        if(foundNewWinner == false)
        {
            done = true;
        }

    }
    while(!done);

    return winner;

}

int maximum(tours &population)
{
    //Returns an array index.
    int popSize;  // Variable that holds the population size.
    int winner = 0;
    tourChroms thisChromo;
    tourChroms thatChromo;
    bool foundNewWinner;
    bool done = false;

    do
    {
        foundNewWinner = false;
        popSize = population.getTourCount();
        for(int i = 0; i <= popSize - 1; i++)
        {
            if(i != winner)             // Avoid self-comparison.
            {
                population.getTour(i, thisChromo);
                population.getTour(winner, thatChromo);
                // The maximum has to be in relation to the Target.
                if(abs(TARGET - thisChromo.getTotal()) > abs(TARGET - thatChromo.getTotal()))
                {
                    winner = i;
                    foundNewWinner = true;
                }
            }
        }

        if(foundNewWinner == false)
        {
            done = true;
        }

    }
    while(!done);

    return winner;
}
