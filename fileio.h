#ifndef fileio_h
#define fileio_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// REQUIRE: path is valid; number to be read is decimal
// MODIFIE: *buf
// EFFECTS: concatenate (root_path, cat_path) to get the path of the file
//          stores the result in *buf
//          returns 0 on success, -1 on failure
int readFile_singleNumber(const char *root_path,
                          const char *cat_path,
                          int *buf);

// REQUIRE: path is valid; number to be read is long double
//          memory of buf is properly allocated
// MODIFIE: *buf
// EFFECTS: concatenate (root_path, cat_path) to get the path of the file
//          stores the result in *buf sequentialy
//          returns 0 on success, -1 on failure
int readFile_long(const char *root_path, const char *cat_path,
                  long double *buf);

// REQUIRE: path_hmm is a valid path to dir Model_Parameters
// MODIFIE: *num_components, *num_features
// EFFECTS: reads the file N_Components.txt and N_Features.txt
//          stores the parameters in *num_components, *num_features
//          returns 0 on success, -1 on failure
int read_hmm_size(const char* path_hmm,
    int* num_components, int* num_features);

int read_hmm_coef(const char* path_hm, long double* transition_mat,
    long double* emission_mat, long double* initial_mat);
#endif
