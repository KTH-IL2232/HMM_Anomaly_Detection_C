#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileio.h"

int readFile_singleNumber(const char *root_path, const char *cat_path,
                          int *buf){
    const int path_length_max = 512;
    const int line_width_max = 512;

    FILE* fp = NULL;
    char path[path_length_max]; // stores temporal path
    char line[line_width_max]; // stores temporal line
    strcpy(path, root_path);
    strcat(path, cat_path);
    
    fp = fopen(path, "r");
    if (fgets(line, sizeof(line), fp)) {
        *buf = (int)strtol(line, NULL, 10);
    }
    else {
        printf("Failure: %s is empty!", path);
        return -1;
    }
    fclose(fp);
    
    return 0;
}

int readFile_long(const char *root_path, const char *cat_path,
                  long double *buf){
    const int path_length_max = 512;
    const int line_width_max = 512;

    FILE* fp = NULL;
    char path[path_length_max];
    char line[line_width_max];
    int line_num_file = 0;
    strcpy(path, root_path);
    strcat(path, cat_path);
    
    fp = fopen(path, "r");
    line_num_file = 0;
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%Lf", &buf[line_num_file]);
        line_num_file++;
        
    }
    fclose(fp);
    return 0;
}

int readFile_long_int(const char *root_path, const char *cat_path,
                  int *buf){
    const int path_length_max = 512;
    const int line_width_max = 512;

    FILE* fp = NULL;
    char path[path_length_max];
    char line[line_width_max];
    int line_num_file = 0;
    strcpy(path, root_path);
    strcat(path, cat_path);
    
    fp = fopen(path, "r");
    line_num_file = 0;
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d", &buf[line_num_file]);
        line_num_file++;
        
    }
    fclose(fp);
    return 0;
}

int saveFileLongDouble(const char *root_path, const char *cat_path,
                       long double *buf, int length){
    FILE* fp = NULL;
    // obtain path
    const int path_length_max = 512;
    char path[path_length_max];
    strcpy(path, root_path);
    strcat(path, cat_path);
    // write to file
    fp = fopen(path, "w");
    for (int i = 0; i < length; i++) {
          fprintf(fp, "%Lf\n", buf[i]);
       }
    fclose(fp);
    return 0;
}


int read_hmm_size(const char* path_hmm, int* num_components, int* num_features)
{
	const int path_length_max = 512;
	const int line_width_max = 512;

	FILE* fp = NULL;
	char path[path_length_max]; // stores temporal path
	char line[line_width_max];

	// Read number of components (states)
	strcpy(path, path_hmm);
	strcat(path, "/N_Components.txt");
	fp = fopen(path, "r");
	if (fgets(line, sizeof(line), fp)) {
		*num_components = (int)strtol(line, NULL, 10);
	}
	else {
		printf("Failure: N_Components.txt is empty!");
		return -1;
	}
	fclose(fp);

	// Read number of features (observations)
	strcpy(path, path_hmm);
	strcat(path, "/N_Features.txt");
	fp = fopen(path, "r");
	if (fgets(line, sizeof(line), fp)) {
		*num_features = (int)strtol(line, NULL, 10);
	}
	else {
		printf("Failure: N_Features.txt is empty!");
		return -1;
	}
	fclose(fp);

	return 0;
}

int read_hmm_coef(const char* path_hmm, long double* transition_mat,
	long double* emission_mat, long double* initial_mat) {
	const int path_length_max = 512;
	const int line_width_max = 512;

	FILE* fp = NULL;
	char path[path_length_max];
	char line[line_width_max];
	int line_num_file = 0;

	// Read transition probability matrix
	strcpy(path, path_hmm);
	strcat(path, "/Transition_Probability_Matrix.txt");
	fp = fopen(path, "r");
	line_num_file = 0;
	while (fgets(line, sizeof(line), fp)) {
		sscanf(line, "%Lf", &transition_mat[line_num_file]);
		line_num_file++;
		
	}
	fclose(fp);

	// Read emission probability matrix
	strcpy(path, path_hmm);
	strcat(path, "/Emission_Probability_Matrix.txt");
	fp = fopen(path, "r");
	line_num_file = 0;
	while (fgets(line, sizeof(line), fp)) {
		sscanf(line, "%Lf", &emission_mat[line_num_file]);
		line_num_file++;
	}
	fclose(fp);

	// Read initial probability matrix
	strcpy(path, path_hmm);
	strcat(path, "/Initial_Probability_Matrix.txt");
	fp = fopen(path, "r");
	line_num_file = 0;
	while (fgets(line, sizeof(line), fp)) {
		sscanf(line, "%Lf", &initial_mat[line_num_file]);
		line_num_file++;
	}
	fclose(fp);

	return 0;
}
