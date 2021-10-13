#ifndef fileio_h
#define fileio_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// REQUIRE: path_hmm is a valid path to dir Model_Parameters
// MODIFIE: *num_components, *num_features
// EFFECTS: reads the file N_Components.txt and N_Features.txt
//          stores the parameters in *num_components, *num_features
//          returns 0 on success, -1 on failure
int read_hmm_size(const char *path_hmm,
                  int *num_components, int *num_features);

int read_hmm_coef(const char *path_hm, long double* transition_mat,
                  long double* emission_mat, long double* initial_mat);

#endif
