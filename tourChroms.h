#ifndef QAPGENETICALGORITHM_CCHROMOSOME_H
#define QAPGENETICALGORITHM_CCHROMOSOME_H

#include "globals.h"

class tourChroms
{

private:
    int     chromData[maxCities];
    double  chromTotal;
    double  chromFitness;
    bool    isChromSelected;
    int     chromAge;
    double  chromSelectionProbability;

public:
    tourChroms();
    tourChroms(const tourChroms& chrom); // copy constructor.
    const tourChroms& operator= (const tourChroms& chrom); // Assignment operator overload.
    int     getData(int index) const;
    void    setData(int index, int value);
    double  getTotal() const;
    void    setTotal(double totalValue);
    double  getFitness() const;
    void    setFitness(double fitnessValue);
    bool    getSelected() const;
    void    setSelected(bool isSelected);
    double  getSelectionProbability() const;
    void    setSelectionProbability(double probValue);

};

#endif //QAPGENETICALGORITHM_CCHROMOSOME_H
