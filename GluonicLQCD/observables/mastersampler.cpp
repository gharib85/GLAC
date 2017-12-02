#include "mastersampler.h"

#include "parallelization/communicator.h"
#include "config/parameters.h"
#include "io/fieldio.h"

//using namespace LatticeOperations;

MasterSampler::MasterSampler()
{
    m_multiplicationFactor = 18.0*double(Parameters::getLatticeSize());
//    int Nx = 2, Ny = 1, Nz = 1, Nt = 1;
//    std::vector<int> dim = {Nx,Ny,Nz,Nt};
//    int latticeSize = Nx*Ny*Nz*Nt;
//    Lattice <SU3> A, B;
//    A.allocate(dim);
//    B.allocate(dim);
//    A.identity();
//    B.identity();
//    printf("\nA.N=%d B.N=%d\n",A.m_latticeSize,B.m_latticeSize);
//    B *= 1000;
//    B[latticeSize-1][1] = 10;
//    B[latticeSize-1][17] = 10;
//    Parallel::Communicator::setBarrier();
//    if (Parallel::Communicator::getProcessRank() == 0) A[latticeSize-1].print();
//    A += B;
//    Parallel::Communicator::setBarrier();
//    if (Parallel::Communicator::getProcessRank() == 0) A[latticeSize-1].print();
//    A -= B;
//    Parallel::Communicator::setBarrier();
//    if (Parallel::Communicator::getProcessRank() == 0) A[latticeSize-1].print();
//    A = A + B;

//    for (int i = 0; i < latticeSize; i++) {
//        A[i] *= 2;
//    }
//    printf("\nSumming!");
//    SU3 a = sum(A);
//    a.print();
////    A[0].print();
//    printf("\nShifting!");
//    Parallel::Communicator::setBarrier();
//    printf("\nShifting!");
//    Parallel::Communicator::setBarrier();
//    int mu = 0;
//    B.zeros();
//    A.identity();
//    A = shift(B,FORWARDS,mu);
//    B[0].print();
//    B[1].print();
//    A[0].print();
//    A[1].print();

}

void MasterSampler::calculate()
{
    // Initializes lattice
    Lattice <SU3> lattice[4];
    unsigned int N[4] = {8, 4, 8, 16};
    Parameters::setSubLatticePreset(true);
    Parameters::setN(N);
    Parallel::Index::setN(N);
    Parallel::Communicator::setN(N);
    Parallel::Communicator::initializeSubLattice();
    IO::FieldIO::init();
//    Parameters::getN(N);
    std::vector<int> dim = {int(N[0]),int(N[1]),int(N[2]),int(N[3])};
    printf("\n%d %d %d %d \n",int(N[0]),int(N[1]),int(N[2]),int(N[3]));
    for (int mu = 0; mu < 4; mu++) {
        lattice[mu].allocate(dim);
        lattice[mu].identity();
    }

    // Loads configuration into lattice
    std::string fname = "LatticeOperationsTestConfig_beta6.000000_spatial8_temporal16_threads4_config0.bin";
    IO::FieldIO::loadLatticeFieldConfiguration(fname,lattice);
//    Parallel::Communicator::setBarrier();
//    printf("\nLOADED LATTICE!");
    printf("\n");
    // Initializes samples for the
    Lattice <SU3> PTemp(dim), P(dim);
    P.zeros();


    //TEST
    PTemp.identity();
    if (Parallel::Communicator::getProcessRank() == 0) {
        for (int i = 0; i < P.m_latticeSize; i++) {
            PTemp[i] = 2;
        }
    }
    if (Parallel::Communicator::getProcessRank() == 1) {
        for (int i = 0; i < P.m_latticeSize; i++) {
            PTemp[i] = 0.11111111;
        }
    }
    Parallel::Communicator::setBarrier();
//    P[0].print();
    P = shift(PTemp,BACKWARDS,0); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,BACKWARDS,1); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,BACKWARDS,2); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,BACKWARDS,3); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,FORWARDS,0); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,FORWARDS,1); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,FORWARDS,2); // TEST ALL 8 COMBINATIONS!
//    P = shift(PTemp,FORWARDS,3); // TEST ALL 8 COMBINATIONS!
    Parallel::Communicator::setBarrier();
    if (Parallel::Communicator::getProcessRank() == 0) {
        printf("\n Rank = %d\n",Parallel::Communicator::getProcessRank());
        P[Parallel::Index::getIndex(2,0,2,2)].print(); //CHECK THAT PROC 1 RECEIVES FROM 0 AND VICA VERSA BY SETTING UP IF TEST FOR PROC AND BARRIERS!
    }
    Parallel::Communicator::setBarrier();
    if (Parallel::Communicator::getProcessRank() == 1) {
        printf("\n Rank = %d\n",Parallel::Communicator::getProcessRank());
        P[Parallel::Index::getIndex(2,0,2,2)].print();
    }
    Parallel::Communicator::setBarrier();
    exit(1);

    for (int mu = 0; mu < 4; mu++) {
        for (int nu = mu+1; nu < 4; nu++) {
            PTemp = lattice[mu];
            PTemp *= shift(lattice[nu],FORWARDS,mu);
            PTemp *= shift(lattice[mu],FORWARDS,nu).inv();
            PTemp *= lattice[nu].inv();
            P += PTemp;
        }
    }
    double observable = sum(realTrace(P))/m_multiplicationFactor;
    MPI_Allreduce(&observable,&observable,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
    printf("\nPlaquette = %20.16f\n",observable);
}