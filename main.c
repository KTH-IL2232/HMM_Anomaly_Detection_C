#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "macros.h"
#include "fileio.h"
#include "Forward.h"
#include "AnomalyDetection.h"

#ifdef DiscreteEmisDensity
#include "DiscreteModelFunc.h"
#endif

#ifdef GaussianEmisDensity
#include "GaussianModelFunc.h"
#endif

// HMM has Discrete emission density, Gaussian emission density,
// or GMM emission density.
// Define the emission density type in "macros.h".
// Then everything will be taken care of, since we are using this macro
// throughout the code.

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
    int n_components, n_samples, l_samples_file;
    readFile_singleNumber(path_hmm, "/N_Components.txt",
                          &n_components);
    readFile_singleNumber(path_dataset, "/Test_anomaly_set_samples.txt",
                          &n_samples);
    readFile_singleNumber(path_dataset,
                          "/Test_anomaly_set_array_size.txt",
                          &l_samples_file);
    
    // special single number for each model
#ifdef DiscreteEmisDensity
    int n_features;
    readFile_singleNumber(path_hmm, "/N_Features.txt", &n_features);
#endif

    // read pi, A, which is same for all models
    long double* transition_mat = malloc(n_components * n_components
        * sizeof(long double));
    long double* initial_mat = malloc(n_components
        * sizeof(long double));
    readFile_long(path_hmm, "/Transition_Probability_Matrix.txt",
                  transition_mat);
    
    readFile_long(path_hmm, "/Initial_Probability_Matrix.txt",
                  initial_mat);
    
    // read B, model specific
#ifdef DiscreteEmisDensity
    long double* emission_mat = malloc(n_components * n_features
        * sizeof(long double));
    readFile_long(path_hmm, "/Emission_Probability_Matrix.txt",
                  emission_mat);
#endif

#ifdef GaussianEmisDensity
    long double *expectancy_mat = malloc(n_components
                                         * sizeof(long double));
    readFile_long(path_hmm, "/Expectancy_Matrix.txt", expectancy_mat);
    long double *std_variance_mat = malloc(n_components
                                         * sizeof(long double));
    readFile_long(path_hmm, "/Std_Variance_Matrix.txt", std_variance_mat);
#endif
    
    // read dataset, shared part
    int *observation_length_set = malloc(n_samples * sizeof(int));
    int *label_sequence = malloc(n_samples * sizeof(int));
    readFile_long_int(path_dataset, "/Test_anomaly_set_label.txt",
                      label_sequence);
    readFile_long_int(path_dataset, "/Test_anomaly_set_length.txt",
                      observation_length_set);
    
    // read dataset, model specific
#ifdef DiscreteEmisDensity
    int *observation_sequence_set = malloc(l_samples_file *
                                 sizeof(int));
    readFile_long_int(path_dataset, "/Test_anomaly_set_array.txt",
                      observation_sequence_set);
#endif
#ifdef GaussianEmisDensity
    long double *observation_sequence_set = malloc(l_samples_file *
                                 sizeof(long double));
    readFile_long(path_dataset, "/Test_anomaly_set_array.txt",
                      observation_sequence_set);
#endif
    
    // anomaly detection, model specific
#ifdef DiscreteEmisDensity
    anomalyDetection(initial_mat, transition_mat, emission_mat,
                     observation_sequence_set,
                     observation_length_set,
                     label_sequence,
                     n_components, n_features,
                     n_samples,
                     path_statistics);
#endif
    
#ifdef GaussianEmisDensity
    anomalyDetection(initial_mat, transition_mat,
                     expectancy_mat, std_variance_mat,
                     observation_sequence_set,
                     observation_length_set,
                     label_sequence,
                     n_components,
                     n_samples,
                     path_statistics);
#endif
    
    // ends the program
    free(transition_mat);
    free(initial_mat);
    free(observation_sequence_set);
    free(observation_length_set);
#ifdef DiscreteEmisDensity
    free(emission_mat);
#endif
    
#ifdef GaussianEmisDensity
    free(expectancy_mat);
    free(std_variance_mat);
#endif
    
    //nothing should be added here!
    return 0;
}
