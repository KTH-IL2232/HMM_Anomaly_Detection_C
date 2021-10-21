/*
 This header file describes the functions needed to perform the forward
 algorithm for HMM.
 The HMM can be either discrete, Gaussian, or Gaussian Mixture.
 To choose HMM type, change the macro defined in main.c.
 Then the proper header file will be automatically included.
*/

#ifndef forward_h
#define forward_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"

// alpha_t(i) = val, t \in [0, T - 1]
int alpha_t_i_assign(long double *alpha, int t, int i, long double val, int nC);


// return alpha_t(i)
long double alpha_t_i_get(long double *alpha, int t, int i, int nC);

// print the entire list of alpha_t
int alpha_t_print(long double *alpha, int t,
                  int nC);

// print the entire alpha
int alpha_print(long double *alpha, int SL, int nC);

#ifdef DiscreteEmisDensity
// evaluate one single output sequence
// return P(O|lambda)
long double forward(long double *pi, long double *b, long double *a,
            int *O, int nC, int nF, int SL);
#endif

#ifdef GaussianEmisDensity
long double forward(long double *pi,
                    long double *expectancy, long double *std_variance,
                    long double *a,
                    long double *O, int nC, int SL);
#endif

#endif
