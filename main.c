#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "fileio.h"
#include "Forward.h"
#include "DiscreteModelFunc.h"
#include "AnomalyDetection.h"

int main()
{
    // Windows path
    // const char *path_hmm = "./Model_Parameters";
    // const char *path_statistics = "./obtained_statistics";
    // const char *path_dataset = ./dataset";
    // MAC path
    const char *path_statistics =
    "/Users/yang/Desktop/IL2232/MyCode/CVersionHMM/HMM_Anomaly_Detection_C/obtained_statistics";
    const char* path_hmm =
    "/Users/yang/Desktop/IL2232/MyCode/CVersionHMM/HMM_Anomaly_Detection_C/Model_Parameters";
    const char *path_dataset =
    "/Users/yang/Desktop/IL2232/MyCode/CVersionHMM/HMM_Anomaly_Detection_C/dataset";

    // read single numbers
    int n_components, n_features, n_samples, l_samples_file;
    readFile_singleNumber(path_hmm, "/N_Components.txt",
                          &n_components);
    readFile_singleNumber(path_hmm, "/N_Features.txt",
                          &n_features);
    readFile_singleNumber(path_dataset, "/Test_anomaly_set_samples.txt",
                          &n_samples);
    readFile_singleNumber(path_dataset,
                          "/Test_anomaly_set_array_size.txt",
                          &l_samples_file);

    // read pi, A, B
    long double* transition_mat = malloc(n_components * n_components
        * sizeof(long double));
    long double* emission_mat = malloc(n_components * n_features
        * sizeof(long double));
    long double* initial_mat = malloc(n_components
        * sizeof(long double));
    readFile_long(path_hmm, "/Transition_Probability_Matrix.txt",
                  transition_mat);
    readFile_long(path_hmm, "/Emission_Probability_Matrix.txt",
                  emission_mat);
    readFile_long(path_hmm, "/Initial_Probability_Matrix.txt",
                  initial_mat);
    
    // read dataset
    int *observation_sequence_set = malloc(l_samples_file *
                                 sizeof(int));
    int *observation_length_set = malloc(n_samples *
                                                 sizeof(int));
    int *label_sequence = malloc(n_samples * sizeof(int));
    readFile_long_int(path_dataset, "/Test_anomaly_set_array.txt",
                      observation_sequence_set);
    readFile_long_int(path_dataset, "/Test_anomaly_set_length.txt",
                      observation_length_set);
    readFile_long_int(path_dataset, "/Test_anomaly_set_label.txt",
                      label_sequence);
    
    anomalyDetection(initial_mat, transition_mat, emission_mat,
                     observation_sequence_set,
                     observation_length_set,
                     label_sequence,
                     n_components, n_features,
                     n_samples,
                     path_statistics);
    
    // ends the program
    free(transition_mat);
    free(emission_mat);
    free(initial_mat);
    free(observation_sequence_set);
    free(observation_length_set);
    
    //nothing should be added here!
    return 0;
}
