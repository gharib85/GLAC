#ifndef CORRELATOR_H
#define CORRELATOR_H

#include "math/links.h"
#include "parallelization/index.h"
#include "parallelization/neighbours.h"
#include "parallelization/communicator.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

class Correlator
{
protected:
    // Lattice dimension array
    unsigned int *m_N;
    // (sub)lattice size
    double m_latticeSize;
    // Lattice spacing
    double m_a;
    // Lorentz indices
    int muIndex[4];
    int nuIndex[4];
    // Position vector for handling the shift-method in parallelization
    std::vector<int> m_position;

    inline void updateMuIndex(int mu) {
        for (int i = 0; i < 4; i++)
        {
            muIndex[i] = 0;
        }
        muIndex[mu] = 1;
    }
    inline void updateNuIndex(int nu) {
        for (int i = 0; i < 4; i++)
        {
            nuIndex[i] = 0;
        }
        nuIndex[nu] = 1;
    }
    inline int cloverIndex(int mu, int nu)
    {
        /*
         * Used for accessing the clover SU3 elements in an contigious fashion.
         */
        return (4*mu + nu);
    }
public:
    Correlator();
    virtual ~Correlator();
    virtual double calculate(Links *lattice);
//    virtual void calculate(Links * lattice);
    virtual double calculate(SU3 *U);
    virtual void setLatticeSize(int latticeSize);
    virtual void setLatticeSpacing(double a) { m_a = a; }

    // Setters
    void setN(unsigned int *N);
};


#endif // CORRELATOR_H