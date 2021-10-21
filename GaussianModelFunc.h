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

#include "macros.h"

#ifdef GaussianEmisDensity
// SL is Sample Length = T
// REQUIRE: buf has been allocated enough memory space
//          i = [0, ..., n_Samples - 1]
// EFFECTS: extract the ith observation sequence to buf
long double extractObservationSequence(long double *O,
                                       int *SL, int i, long double *buf);
#endif

// REQUIRE: t = [0, ..., T - 1]
// EFFECTS: quantize [1, ..., M] to [0, ..., M - 1]
long double Ot(long double *O, int t);

// bi(Ot) ~ N (Ot, expectancy, std_variance)
long double biOt(long double *expectancy, long double *std_variance,
                 int i, long double *O, int t);

// a_{ij}
long double aij(long double *a, int i, int j, int nC);

// print all data in the observation sequence
long double printObservation(long double *O, int length);

#endif
