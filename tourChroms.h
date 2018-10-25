#ifndef QAPGENETICALGORITHM_CCHROMOSOME_H
#define QAPGENETICALGORITHM_CCHROMOSOME_H

#include "globals.h"

class tourChroms
{

private:
    int     chromData[maxCities];
    //int     chromRegion;
    double  chromTotal;
    double  chromFitness;
    bool    isChromSelected;
    int     chromAge;
    double  chromSelectionProbability;

public:
    tourChroms();
    tourChroms(const tourChroms& aChromosome); // copy constructor.
    const tourChroms& operator= (const tourChroms& aChromosome); // Assignment operator overload.
    int     getData(int index) const;
    void    setData(int index, int value);
    //int     getRegion() const;
    double  getTotal() const;
    void    setTotal(double totalValue);
    double  getFitness() const;
    void    setFitness(double fitnessValue);
    bool    getSelected() const;
    void    setSelected(bool selectedValue);
    int     getAge() const;
    double  getSelectionProbability() const;
    void    setSelectionProbability(double spValue);

};

#endif //QAPGENETICALGORITHM_CCHROMOSOME_H
