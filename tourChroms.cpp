#include "tourChroms.h"

tourChroms::tourChroms()
{
    chromTotal = 0.0;
    chromAge = 0;
    chromSelectionProbability = 0.0;
}

tourChroms::tourChroms(const tourChroms& aChromosome)
{
    // Copy constructor.
    for(int i = 0; i <= maxCities - 1; i++)
    {
        chromData[i] = aChromosome.getData(i);
    }
    //chromRegion = aChromosome.getRegion();
    chromTotal = aChromosome.getTotal();
    chromFitness = aChromosome.getFitness();
    isChromSelected = aChromosome.getSelected();
    chromAge = aChromosome.getAge();
    chromSelectionProbability = aChromosome.getSelectionProbability();
}

const tourChroms& tourChroms::operator= (const tourChroms& aChromosome)
{
    // Assignment operator overload.
    if(this != &aChromosome)
    {
        for(int i = 0; i <= maxCities - 1; i++)
        {
            chromData[i] = aChromosome.getData(i);
        }
        //chromRegion = aChromosome.getRegion();
        chromTotal = aChromosome.getTotal();
        chromFitness = aChromosome.getFitness();
        isChromSelected = aChromosome.getSelected();
        chromAge = aChromosome.getAge();
        chromSelectionProbability = aChromosome.getSelectionProbability();
    }

    return *this;
}

int tourChroms::getData(int index) const
{
    return chromData[index];
}

void tourChroms::setData(int index, int value)
{
    chromData[index] = value;
}

//int tourChroms::getRegion() const
//{
  //  return chromRegion;
//}

double tourChroms::getTotal() const
{
    return chromTotal;
}

void tourChroms::setTotal(double totalValue)
{
    chromTotal = totalValue;
}

double tourChroms::getFitness() const
{
    return chromFitness;
}

void tourChroms::setFitness(double fitnessValue)
{
    chromFitness = fitnessValue;
}

bool tourChroms::getSelected() const
{
    return isChromSelected;
}

void tourChroms::setSelected(bool selectedValue)
{
    isChromSelected = selectedValue;
}

int tourChroms::getAge() const
{
    return chromAge;
}

double tourChroms::getSelectionProbability() const
{
    return chromSelectionProbability;
}

void tourChroms::setSelectionProbability(double spValue)
{
    chromSelectionProbability = spValue;
}