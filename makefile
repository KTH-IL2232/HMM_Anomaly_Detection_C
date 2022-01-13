
mymake: main.c AnomalyDetection.c DiscreteModelFunc.c Forward.c GaussianModelFunc.c fileio.c
	gcc -o work AnomalyDetection.c DiscreteModelFunc.c Forward.c GaussianModelFunc.c fileio.c main.c
