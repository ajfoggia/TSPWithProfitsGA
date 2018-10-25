#include "tourChroms.h"

tourChroms::tourChroms()
{
    chromTotal = 0.0;
    chromAge = 0;
    chromSelectionProbability = 0.0;
}

tourChroms::tourChroms(const tourChroms& chrom)
{
    // Copy constructor.
    for(int i = 0; i <= maxCities - 1; i++)
    {
        chromData[i] = chrom.getData(i);
    }
    chromTotal = chrom.getTotal();
    chromFitness = chrom.getFitness();
    isChromSelected = chrom.getSelected();
    chromSelectionProbability = chrom.getSelectionProbability();
}

const tourChroms& tourChroms::operator= (const tourChroms& chrom)
{
    // Assignment operator overload.
    if(this != &chrom)
    {
        for(int i = 0; i <= maxCities - 1; i++)
        {
            chromData[i] = chrom.getData(i);
        }
        chromTotal = chrom.getTotal();
        chromFitness = chrom.getFitness();
        isChromSelected = chrom.getSelected();
        chromSelectionProbability = chrom.getSelectionProbability();
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

void tourChroms::setSelected(bool isSelected)
{
    isChromSelected = isSelected;
}

double tourChroms::getSelectionProbability() const
{
    return chromSelectionProbability;
}

void tourChroms::setSelectionProbability(double probValue)
{
    chromSelectionProbability = probValue;
}