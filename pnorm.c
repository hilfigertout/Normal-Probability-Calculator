//This program calculates the probability from a normal distribution
//with mean "mu" and standard deviation "sigma".
//If mu and sigma are not specified, they will be assumed to be 0 and 1 respectively.

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MIN_SERIES_TERMS 14
#define INVERSE_SQRT_2PI 0.3989422804
#define HIGHEST_Z 3.1674  //Experimentally determined to be the bounds.
#define LOWEST_Z -3.1674

double zScore(double x, double mu, double sigma) {
	return ((x-mu)/sigma);
}


double normCDF(double z) {
	double output = z; //starting point, computed term at n=0
	int n = 0;
	double current_numerator = z;
	unsigned long denominator = 1;
	long denominator_piece = 1;
	if (z > HIGHEST_Z) {
		output = 1;
	} else if (z < LOWEST_Z) {
		output = 0;
	} else if (z == 0.0) {
		output = 0.5;
	} else {
		int total_terms = MIN_SERIES_TERMS;
		//For loop used to compute SUM((Z^(2n+1)(-1)^n)/((2n+1)(2^n)(n!))) in linear time
		for(n=1; n <= total_terms; n++) {
			current_numerator = current_numerator*z*z*(-1);
			denominator_piece = denominator_piece*n; //factorial term
			denominator_piece = denominator_piece<<1; //2^n term
			denominator = (2*n+1)*denominator_piece; //(2n+1) term
			output = output + (current_numerator / (double)denominator);
		}
		output *= INVERSE_SQRT_2PI;
		output += 0.5;
	}
	return output;
}


int main(int argc, char** argv) {
	//Read user input
	char* endptr = NULL; //This is for error checking
	if (argc < 3) {
		printf("ERROR: not enough arguments.\n");
		printf("Correct usage: pnorm [low_value] [high_value] [mu, default=0] [sigma, default=1]\n");
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

	//actual calculations start here
	double output = 0;
	if (lowX == highX) {
		output = 0.0;
	} else {
		double lowZ = zScore(lowX, mu, sigma);
		double highZ = zScore(highX, mu, sigma);
		output = normCDF(highZ) - normCDF(lowZ);
		if (output > 1.0) {
			output = 1.0;
		} else if (output < 0.0) {
			output = 0.0;
		}
	}
	//Output result
	printf("P(%f < X < %f) = %f\n", lowX, highX, output);
	return 0;
}
