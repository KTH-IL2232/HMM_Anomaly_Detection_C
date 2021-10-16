#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "AnomalyDetection.h"
#include "DiscreteModelFunc.h"
#include "Forward.h"
#include "fileio.h"

int anomalyDetection(long double *pi, long double *a, long double *b,
                     int *observation_sequence_set,
                     int *observation_length_set,
                     int *label_sequence,
                     int n_components, int n_features,
                     int n_samples,
                     const char *path_statistics){
    // anomaly detection
    double TP = 0., FP = 0., TN = 0., FN = 0.;
    long double *P_s = malloc(n_samples * sizeof(long double));
    for (int i = 0; i < n_samples; i++){
        //extract the observation sequence from the set
        int *O = malloc(observation_length_set[i] * sizeof(int));
        extractObservationSequence(observation_sequence_set,
                                   observation_length_set, i, O);
        // evaluate P (O | lambda)
        long double P = 0;
        P = forward(pi, b, a, O,
                    n_components, n_features, observation_length_set[i]);
        P = logl(P); // log likelihood
        P_s[i] = P;
        
        testPositive(&TP, &FP, &TN, &FN, P, label_sequence[i]);
        
        free(O);
    }
    
    // save results to file
    saveFileLongDouble(path_statistics, "/P.txt", P_s, n_samples);

    calcStat(TP, FP, TN, FN);
    free(P_s);
    return 0;
}

int testPositive(double *TP, double *FP, double *TN, double *FN,
                 long double P, int label){
    int is_anomaly = 0;
    long double threshold = -10.;
    if (P < threshold){
        is_anomaly = 1;
    }
    int ground_truth = label;
    if (is_anomaly == 1){
        if (ground_truth == 1){
            *TP += 1;
        }else{
            *FP += 1;
        }
    }else{
        if (ground_truth == 1){
            *FN += 1;
        }else{
            *TN += 1;
        }
    }
    return 0;
}

int calcStat(double TP, double FP, double TN, double FN){
    double precision, recall, f_score;
    precision = TP / (TP + FP);
    recall = TP / (TP + FN);
    f_score = 2 * TP / (2 * TP + FP + FN);
    // print statistics
    printf("precision = %lf, recall = %lf, f_score = %lf\n",
           precision, recall, f_score);
    return 0;
}
