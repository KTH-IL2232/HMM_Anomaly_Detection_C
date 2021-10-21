#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#ifdef DiscreteEmisDensity
#include "DiscreteModelFunc.h"

int extractObservationSequence(int *O, int *SL, int i, int *buf){
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

int Ot(int *O, int t){
    // return O[t] - 1; // if V = [1, ..., M]
    return O[t]; // if V = [0, ..., M - 1]
}

long double biOt(long double *b, int i, int *O, int t, int nF){
    int start_id = nF * i;
    return b[start_id + Ot(O, t)];
}

long double aij(long double *a, int i, int j, int nC){
    return a[i * nC + j];
}

int printObservation(int *O, int length){
    printf("Printing O with length %d\n", length);
    for (int i = 0; i < length; i++){
        printf("O[%d] = %d\n", i, O[i]);
    }
    printf("End of O\n");
    return 0;
}
#endif
