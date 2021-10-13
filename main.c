#include <stdio.h>
#include "fileio.h"
int main()
{
	int r;
	int n_components, n_features;
<<<<<<< HEAD
	long double* transition;
	long double* emission;
	long double* initial;
	//printf(" %g\n", n_features);
	r = read_hmm_coef("", &n_components, &n_features, &transition, &emission, &initial);
	
=======
	r = read_hmm_size("./Model_Parameters", &n_components, &n_features);
	long double* transition = malloc(n_components * n_components);
	long double* emission = malloc(n_components * n_features);
	long double* initial = malloc(n_components);
	printf("num of components: %i & num of features: %i\n", n_components, n_features);
	r = read_hmm_coef("./Model_Parameters", n_components, n_features, transition, emission, initial);
	printf("coef[0]: %g\n", transition[0]);
>>>>>>> parent of 36cf26a (Reading parameters from file.)
	return 0;
}