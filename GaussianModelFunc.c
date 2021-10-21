#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "macros.h"

#ifdef GaussianEmisDensity
#include "GaussianModelFunc.h"

long double extractObservationSequence(long double *O,
                                       int *SL, int i, long double *buf){
    int start_id = 0;
    if (i != 0){
        for (int j = 0; j < i; j++){
            start_id += SL[j];
        }
    }
    for (int j = 0; j < SL[i]; j++){
        buf[j] = O[start_id + j];
    }
    return 0;
}

long double Ot(long double *O, int t){
    // return O[t] - 1; // if V = [1, ..., M]
    return O[t]; // if V = [0, ..., M - 1]
}

long double biOt(long double *expectancy, long double *std_variance,
                 int i, long double *O, int t){
    long double e = expectancy[i];
    long double s = std_variance[i];
    long double o = Ot(O, t);
    long double component1 = 1 / (sqrtl(2 * M_PI) * s);
    long double component2 = expl(-0.5 * powl((o - e) / s, 2));
    return component1 * component2;
}

long double aij(long double *a, int i, int j, int nC){
    return a[i * nC + j];
}

long double printObservation(long double *O, int length){
    printf("Printing O with length %d\n", length);
    for (int i = 0; i < length; i++){
        printf("O[%d] = %Lf\n", i, O[i]);
    }
    printf("End of O\n");
    return 0;
}

#endif
