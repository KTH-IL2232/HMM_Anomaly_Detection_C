#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"

int main()
{
    // Windows path
    // const char *path_hmm = "./Model_Parameters";
    // MAC path
    const char* path_hmm = "/Users/yang/Desktop/IL2232/MyCode/CVersionHMM/HMM_Anomaly_Detection_C/Model_Parameters";

    // read the number of components and number of features
    int n_components, n_features;
    readFile_singleNumber(path_hmm, "/N_Components.txt",
                          &n_components);
    readFile_singleNumber(path_hmm, "/N_Features.txt",
                          &n_features);

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
    
    // ends the program
    free(transition_mat);
    free(emission_mat);
    free(initial_mat);
    
    printf("nc = %d, nf = %d\n",n_components, n_features);
    printf("T[0] = %Lf, T[end] = %Lf\n",transition_mat[0], transition_mat[899]);
    printf("E[0] = %Lf, E[end] = %Lf\n",emission_mat[0], emission_mat[239]);
    printf("I[0] = %Lf, I[end] = %Lf\n",initial_mat[0], initial_mat[29]);
    return 0;
}
