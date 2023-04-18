#pragma once
#ifndef optimizeIncluded
#define optimizeIncluded

#include <math.h>
#include <limits>

#define Detectors 18
#define NUMBER_OF_FILES 9
#define resolution 10
#define nSim 10000000
#define Activity 10000
#define MinCount 400


extern double Edep;
extern int MinIndex;
extern int MaxIndex;
extern double bestScoreSoFar;
extern double HighestScoreSoFar;
extern double bestWeights[NUMBER_OF_FILES];
extern double Try[Detectors][NUMBER_OF_FILES];


void FindOptimalExposure(double* SetOfAttempts); //function that is passed to each thread. Passed in as "work" and a few other parameters 

void increment_index_array(int* index, int n, int k);

void work(unsigned long long beggining, unsigned long long end); //FindOptimalExposure and necessary parameters wrapped in a simple package to send to each thread. Simply as a way to simplify code later on

#endif