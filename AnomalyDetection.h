/*
 This header file describes functions used for anomaly detection.
 The anomaly detection strategy can be changed in the implementation.
 */

#ifndef anomalydetection_h
#define anomalydetection_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// pi: initial matrix, a: transition probability matrix
// b: emission probability matrix
// stores each log P(Sample) to dir specified by *path_statistics
int anomalyDetection(long double *pi, long double *a, long double *b,
                     int *observation_sequence_set,
                     int *observation_length_set,
                     int *label_sequence,
                     int n_components, int n_features,
                     int n_samples,
                     const char *path_statistics);

// tests whether the current oberservation sequence is an anomaly
// Currently, the detection is based on threshold comparison.
// This feature could be changed inside the implementation.
int testPositive(double *TP, double *FP, double *TN, double *FN,
                 long double P, int label);

// calculate statistics: precision, recall and F-score
int calcStat(double TP, double FP, double TN, double FN);

#endif
