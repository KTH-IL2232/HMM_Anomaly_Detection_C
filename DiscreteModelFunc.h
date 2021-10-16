/*
 This header file describes basic functions for HMM model with discrete
 observation densities.
 important assumtion: V = (1, ..., M) (int)
 This feature could also be changed to V = [0, ..., M - 1].
 User has to make sure that it matches with the dataset.
*/

#ifndef ModelFunc_h
#define ModelFunc_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// SL is Sample Length = T
// REQUIRE: buf has been allocated enough memory space
//          i = [0, ..., n_Samples - 1]
// EFFECTS: extract the ith observation sequence to buf
int extractObservationSequence(int *O, int *SL, int i, int *buf);

// REQUIRE: t = [0, ..., T - 1]
// EFFECTS: quantize [1, ..., M] to [0, ..., M - 1]
int Ot(int *O, int t);

// bi(Ot), i \in [0, n_components - 1], t \in [0, T - 1]
// nF = number of features
long double biOt(long double *b, int i, int *O, int t, int nF);

// a_{ij}
long double aij(long double *a, int i, int j, int nC);

// print all data in the observation sequence
int printObservation(int *O, int length);



#endif
