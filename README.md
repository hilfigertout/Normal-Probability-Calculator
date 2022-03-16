# Normal-Probability-Calculator

This project implements a C program to compute normal distribution probabilities without special libraries. 

## USAGE:

To use, first compile the program by downloading and executing the makefile with the following terminal command:

> make

Once the program is compiled, it can be executed with the following command:

> ./pnorm [low] [high] [mu, default=0] [sigma, default=1]

where "low" and "high" denote the values to calculate the probability between, mu denotes the mean, and sigma denotes the standard deviation. The mu and sigma parameters are **optional**, and they default to 0 and 1 respectively, i.e. the standard normal curve. 

## EXAMPLES:

Let Z denote a standard normal random variable, with mean 0 and standard deviation 1. Let X denote a normal random variable with mean *mu* and standard deviation *sigma*. 

> ./pnorm 0 1

This will calculate P(0 < Z < 1), which works out to 0.341345

> ./pnorm 4 6 4 2

This will calculate P(4 < X < 6), where *mu*=4 and *sigma*=6. This also works out to 0.341345.

> ./pnorm -2 1 1 2

This will calculate P(-2 < X < 1), where *mu*=-2 and *sigma*=2. This works out to 0.433193.

> ./pnorm 5 10

This will calculate P(5 < Z < 10), which works out to 0.000000. See the next section for why this is.


## ROUNDING ERROR:

This model uses 14 terms of the Taylor series to approximate the CDF of the standard normal distribution. However, this Taylor series has notoriously poor convergence for values of Z with a large magnitude. As such, to limit the amount of error introduced, this program assumes that P(Z < -3.1674) = 0 and P(Z < 3.1674) = 1. These values were determined experimentally, and are considered the limits of what this program can compute. This assumption should result in values that are close enough for most purposes when computing normal probabilities. 

Unfortunately, there appears to be no way to fix this issue. Computing values of Z with a larger magnitude than 3.1674 introduces significant error because the 14 terms of the Taylor series aren't enough to approximate the CDF for values that extreme. However, simply computing more terms of the series is not feasible, as the denominator of terms 15 and beyond exceed the maximum value of an unsigned long integer in C, which means that adding more series terms introduces overflow bugs and generally results in even more error. Thus, this program appears to be the limit of what standard C can do with the Taylor series for the standard normal CDF. Other methods for approximating this CDF may yield more scaleable results. 

## PERSONAL NOTE

This project wasn't meant to be used in any practical setting. (It can be, but it wasn't meant to be.) It's just something I wrote over Spring Break to stay in practice and to gain a better understanding for computing continuious probabilities. I learned a bit about the limitations of using Taylor series and the work involved in creating all those functions that I use in R without a second thought. 

If you want to use the code in this project for anything, go right ahead! This project is under the MIT License, it's free and open-source for anyone to use. 
