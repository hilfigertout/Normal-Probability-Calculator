//This program calculates the probability from a normal distribution
//with mean "mu" and standard deviation "sigma". 
//If mu and sigma are not specified, they will be assumed to be 0 and 1 respectively.

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define SERIES_TERMS 10
#define INVERSE_SQRT_2PI 0.3989422804

double zScore(double x, double mu, double sigma) {
	return ((x-mu)/sigma);
}


double normCDF(double z) {
	int i = 0;
	double current_num = z;
	int factorial_term = 1;
	
}

double normProb(double z_low, double z_high) {
	
}


int main(int argc, char** argv) {
	char* endptr = NULL; //This is for error checking
	if (argc < 3) {
		printf("ERROR: not enough arguments.\n");
		printf("Correct usage: pnorm [low_value], [high_value], [mu, default=0], [sigma, default=1]\n");
		exit(1);
	}
	double mu = 0;
	double sigma = 1;
	if (argc == 4) {
		mu = strtod(*(argv+3), &endptr);
		if (errno == ERANGE) {
			printf("Error: value %s for mu out of range.\n", *(argv+3));
			exit(1);
		}
	} else if (argc == 5) {
		mu = strtod(*(argv+3), &endptr);
		if (errno == ERANGE) {
			printf("ERROR: value %s for mu out of range\n", *(argv+3));
			exit(1);
		}
		sigma = strtod(*(argv+4), &endptr);
		if (errno == ERANGE) {
			printf("ERROR: value %s for sigma out of range\n", *(argv+4));
			exit(1);
		}
		if (sigma <= 0) {
			printf("ERROR: Sigma must be a positive value.\n");
			exit(1);
		}
	}
	double lowX = strtod(*(argv+1), &endptr);
	if (errno == ERANGE) {
		printf("ERROR: value %s for low_value out of range\n", *(argv+1));
		exit(1);
	}
	double highX = strtod(*(argv+2), &endptr);
	if (errno == ERANGE) {
		printf("ERROR: value %s for high_value out of range.\n", *(argv+2));
		exit(1);
	}
	if (lowX > highX) {
		printf("ERROR: low_value must be less than or equal to high_value.\n");
		exit(1);
	}

//	printf("low_value = %f\n", lowX);
//	printf("high_value = %f\n", highX);
//	printf("mu = %f\n", mu);
//	printf("sigma = %f\n", sigma);

	
	if (lowX == highX) {
		return 0.0;
	} else {
		lowZ = zScore(lowX, mu, sigma);
		highZ = zScore(highX, mu, sigma);
		return normProb(lowZ, highZ);
	}
}
