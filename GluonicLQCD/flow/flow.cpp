#include "flow.h"
#include "links.h"
#include "parallelization/indexorganiser.h"
#include "functions.h"

/*
 * A class for performing Wilson flow on a gauge field configuration.
 */

Flow::Flow(unsigned int *N, double beta)
{
    for (int i = 0; i < 4; i++) m_N[i] = N[i];
    I.identity();
    m_beta = beta;
}

void Flow::flowGaugeField(int NFlows, Links *lattice)
{

    for (int i = 0; i < NFlows; i++) {
        runFlow(lattice);
    }
}

void Flow::runFlow(Links *lattice)
{
    for (unsigned int x = 0; x < m_N[0]; x++) {
        for (unsigned int y = 0; y < m_N[1]; y++) {
            for (unsigned int z = 0; z < m_N[2]; z++) {
                for (unsigned int t = 0; t < m_N[3]; t++) {
                    for (unsigned int mu = 0; mu < 4; mu++) {
                        smearLink(lattice[m_Index->getIndex(x,y,z,t)].U[mu]);
                    }
                }
            }
        }
    }
}

SU3 Flow::exponentiate(SU3 X)
{

}

void Flow::smearLink(SU3 V)
{
    // Take derivative of action

//    // Set W0
//    W[0] = V;
//    // Set W1
//    W[1] = exponentiate(0.25 * epsilon * m_S->computeStaple()) * W[0];
//    // Set W2
//    W[2] = exponentiate(8.0/9 * Z1 - 17/36.*Z0)* W[1];
//    // Set V_{t+eps}
//    VNew = exponentiate(0.75*Z2 - 8/9.*Z1 + 17/36.*Z0)*W[2];

//    QSquared = Q*Q;
//    QCubed = Q*QSquared;
//    c0 = 0.3333333333333333*QCubed.Trace();
//    c1 = 0.5*QSquared.Trace();
//    u = sqrt(0.3333333333333333*c1) * cos(0.3333333333333333*)
}

void Flow::setIndexHandler(IndexOrganiser *Index)
{
    m_Index = Index;
}
