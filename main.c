#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"

int main()
{
        // Windows path
         const char *path_hmm = "./Model_Parameters";
        // MAC path
        //const char* path_hmm = "/Users/yang/Desktop/IL2232/MyCode/CVersionHMM/HMM_Anomaly_Detection_C/Model_Parameters";

    // read the number of components and number of features
        int n_components, n_features;
        read_hmm_size(path_hmm, &n_components, &n_features);

        // read pi, A, B
        long double* transition_mat = malloc(n_components * n_components
            * sizeof(long double));
        long double* emission_mat = malloc(n_components * n_features
            * sizeof(long double));
        long double* initial_mat = malloc(n_components
            * sizeof(long double));
        read_hmm_coef(path_hmm, transition_mat, emission_mat, initial_mat);

        printf("T[0] = %g, T[end] = %g\n",
            transition_mat[0], transition_mat[899]);
        printf("E[0] = %g, E[end] = %g\n",
            emission_mat[0], emission_mat[239]);
        printf("I[0] = %g, I[end] = %g\n",
            initial_mat[0], initial_mat[29]);

        free(transition_mat);
        free(emission_mat);
        free(initial_mat);
        return 0;
}