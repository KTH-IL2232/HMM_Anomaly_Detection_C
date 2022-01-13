#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "Forward.h"
#ifdef DiscreteEmisDensity
#include "DiscreteModelFunc.h"
#endif

#ifdef GaussianEmisDensity
#include "GaussianModelFunc.h"
#endif\

int alpha_t_i_assign(long double *alpha, int t, int i, long double val, int nC){
    int start_id = nC * t;
    alpha[start_id + i] = val;
    return 0;
}

long double alpha_t_i_get(long double *alpha, int t, int i, int nC){
    return alpha[nC * t + i];
}

int alpha_t_print(long double *alpha, int t,
                  int nC){
    for (int i = 0; i < nC; i++){
        printf("alpha_%d(%d) = %.10Lf; ", t, i, alpha_t_i_get(alpha, t, i, nC));
        if((i + 1) % 3 == 0){
            printf("\n");
        }
    }
    printf("\n");
    return 0;
}

int alpha_print(long double *alpha, int SL, int nC){
    for (int t = 0; t < SL; t++){
        alpha_t_print(alpha, t, nC);
    }
    return 0;
}

#ifdef DiscreteEmisDensity
long double forward(long double *pi, long double *b, long double *a,
            int *O, int nC, int nF, int SL){
    long double *alpha = malloc(SL * nC * sizeof(long double));
    
    // init phase
    long double val;
    for (int i = 0; i < nC; i++){
        val = pi[i] * biOt(b, i, O, 0, nF);
        alpha_t_i_assign(alpha, 0, i, val, nC);
    }
    
    // recursion phase
    for (int t = 1; t < SL; t++){
        for (int j = 0; j < nC; j++){
            long double sum = 0;
            for (int i = 0; i < nC; i++){
                sum += alpha_t_i_get(alpha, t - 1, i, nC)
                * aij(a, i, j, nC);
            }
            val = biOt(b, j, O, t, nF) * sum;
            alpha_t_i_assign(alpha, t, j, val, nC);
        }a
    }
    
    // termination
    long double P = 0;
    for (int i = 0; i < nC; i++){
        P += alpha_t_i_get(alpha, SL - 1, i, nC);
    }
    
    alpha_print(alpha, SL, nC);
    
    free(alpha);
    return P;
}
#endif

#ifdef GaussianEmisDensity
long double forward(long double *pi,
                    long double *expectancy, long double *std_variance,
                    long double *a,
                    long double *O, int nC, int SL){
    long double *alpha = malloc(SL * nC * sizeof(long double));
    
    // init phase
    long double val;
    for (int i = 0; i < nC; i++){
        long double pi_temp = pi[i];
        val = pi_temp * biOt(expectancy, std_variance, i, O, 0);
        alpha_t_i_assign(alpha, 0, i, val, nC);
    }
    
    // recursion phase
    for (int t = 1; t < SL; t++){
        for (int j = 0; j < nC; j++){
            long double sum = 0;
            for (int i = 0; i < nC; i++){
                sum += alpha_t_i_get(alpha, t - 1, i, nC)
                * aij(a, i, j, nC);
            }
            val = biOt(expectancy, std_variance, j, O, t) * sum;
            alpha_t_i_assign(alpha, t, j, val, nC);
        }
    }
    
    // termination
    long double P = 0;
    for (int i = 0; i < nC; i++){
        P += alpha_t_i_get(alpha, SL - 1, i, nC);
    }
    
    // alpha_print(alpha, SL, nC);
    
    free(alpha);
    return P;
}
#endif
