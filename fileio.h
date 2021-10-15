/*
 This file describes functions used for reading or writing files.
 The user must pay attention to the type of arguments.
*/

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

// equivalent reading file for int value
// I did not find a good soltion such as template
int readFile_long_int(const char *root_path, const char *cat_path,
                  int *buf);

// REQUIRE: buf is allocated length * sizeof(long double)
// EFFECTS: save the sequence in buf to the file at "root_path/cat_path"
int saveFileLongDouble(const char *root_path, const char *cat_path,
                       long double *buf, int length);


// functions below are no longer used, but they are implemented correctly
int read_hmm_size(const char* path_hmm,
    int* num_components, int* num_features);

int read_hmm_coef(const char* path_hm, long double* transition_mat,
    long double* emission_mat, long double* initial_mat);
#endif
