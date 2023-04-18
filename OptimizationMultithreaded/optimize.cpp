#include "optimize.h"


double Edep = 8.2;


//starting best score. starts at -1 so that the first result overwrites it immediately. all threads compete to maximize this score
double bestScoreSoFar = -1.0;
double HighestScoreSoFar = 0.0;
int BestDet;
int WorstDet;
int MinIndex;
int MaxIndex;

//array that saves the best weights found up to that point
double bestWeights[NUMBER_OF_FILES];

//matrix containing all counts for every detector. Commented out the diretionality detectors to make each run faster
//double Try[Detectors][NUMBER_OF_FILES] = { {0, 1, 1586, 1, 2, 2, 7, 16, 2},
//	{2, 4, 356, 9, 16, 11, 16, 92, 5}, {0, 0, 270, 12, 19, 20, 20, 98, 8 }, {0, 6, 196, 11, 17, 23, 21, 108, 28}, {0, 7, 163, 12, 28, 30, 20, 123,15 },
//	{1, 1, 118, 17, 31, 59, 22, 168, 22}, {1, 0, 81, 15, 39, 64, 28, 164, 22}, {0, 3, 84, 59, 143, 265, 32, 154, 44}, {637, 4, 6, 9, 16, 14, 61, 10, 79},
//	{332, 26, 31, 46, 74, 52, 314, 75, 363}, {85, 11, 25, 64, 65, 50, 343, 71, 406}, {78, 16, 33, 41, 54, 46, 340, 66, 369}, {73, 13, 48, 96, 91, 60, 488, 99, 517},
//	{41, 9, 47, 122, 142, 69, 733, 131, 662}, {52, 29, 132, 849, 738, 497, 5001, 813, 4396}, {261, 78, 182, 3440, 2273, 822, 4898, 814, 3344}, {24, 9297, 149, 198, 443, 278, 344, 217, 301},
//	{46, 1444, 235, 707, 1364, 892, 1105, 683, 720} } /*{0, 0, 0, 0, 2, 0, 0, 0}, {0, 0, 2, 0, 0, 0, 0, 0}, {0, 0, 2, 1, 1, 0, 2, 0}, {0, 0, 1, 2, 2, 0, 0, 2} ,
//	{0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 0, 2, 3, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 2, 1, 0, 1}, {0, 0, 0, 0, 1, 1, 0, 1} ,{0, 0, 0, 1, 1, 1, 1, 1}, {0, 0, 1, 2, 0, 0, 0, 0},
//	{0, 0, 0, 0, 2, 0, 0, 0}, {0, 0, 0, 1, 0, 2, 0, 0}, {0, 0, 0, 0, 2, 0, 0, 1}, {0, 0, 1, 2, 3, 0, 0, 0}, {0, 0, 3, 1, 1, 0, 0, 0}, {0, 0, 1, 0, 1, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 1, 1},
//	{0, 0, 1, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 0}, {0, 0, 1, 1, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0},
//	{0, 0, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 0, 0, 0}, {1, 0, 1, 1, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0, 0, 0}, {0, 2, 0, 0, 1, 0, 0, 0} }*/;


double Try[Detectors][NUMBER_OF_FILES] = { {0, 1, 1586, 1, 2, 2, 7, 16, 2},{2, 4, 356, 9, 16, 11, 16, 92, 5}, {0, 0, 270, 12, 19, 20, 20, 98, 8 }, {0, 6, 196, 11, 17, 23, 21, 108, 28}, {0, 7, 163, 12, 28, 30, 20, 123,15 },{1, 1, 118, 17, 31, 59, 22, 168, 22}, {1, 0, 81, 15, 39, 64, 28, 164, 22}, {0, 3, 84, 59, 143, 265, 32, 154, 44}, {637, 4, 6, 9, 16, 14, 61, 10, 79},{332, 26, 31, 46, 74, 52, 314, 75, 363}, {85, 11, 25, 64, 65, 50, 343, 71, 406}, {78, 16, 33, 41, 54, 46, 340, 66, 369}, {73, 13, 48, 96, 91, 60, 488, 99, 517},{41, 9, 47, 122, 142, 69, 733, 131, 662}, {52, 29, 132, 849, 738, 497, 5001, 813, 4396}, {261, 78, 182, 3440, 2273, 822, 4898, 814, 3344}, {24, 9297, 149, 198, 443, 278, 344, 217, 301},{46, 1444, 235, 707, 1364, 892, 1105, 683, 720} };
//will work
double Try1[Detectors][NUMBER_OF_FILES] = { { 0, 1, 1179, 0, 1, 2, 3, 10, 1 }, { 0, 2, 173, 6, 5, 9, 9, 49, 1 }, { 0, 0, 128, 10, 8, 8, 12, 62, 3 }, { 0, 2, 108, 6, 9, 7, 11, 55, 20 }, { 0, 4, 81, 8, 15, 16, 14, 80, 7 }, { 1, 0, 68, 11, 17, 34, 16, 100, 17 }, { 1, 0, 46, 10, 28, 34, 20, 102, 17 }, { 0, 2, 41, 40, 88, 163, 14, 82, 17 }, { 506, 2, 5, 3, 9, 5, 37, 5, 42 }, { 223, 12, 17, 28, 35, 32, 195, 35, 200 }, { 35, 7, 15, 34, 38, 28, 197, 43, 233 }, { 39, 11, 16, 21, 30, 14, 206, 37, 229 }, { 41, 7, 34, 55, 46, 34, 290, 59, 321 }, { 27, 7, 29, 64, 74, 43, 440, 76, 400 }, { 29, 16, 79, 482, 440, 315, 3125, 506, 3029 }, { 202, 55, 115, 2169, 1435, 460, 2823, 454, 2208 }, { 12, 7292, 77, 128, 259, 150, 172, 99, 152 }, { 20, 1024, 95, 441, 901, 560, 549, 279, 316} };
//will work
double Try2[Detectors][NUMBER_OF_FILES] = { {0, 0, 710, 0, 0, 1, 2, 4, 0 }, { 0, 1, 84, 2, 3, 6, 6, 21, 0 }, { 0, 0, 58, 2, 4, 2, 3, 30, 0 }, { 0, 0, 57, 2, 4, 4, 5, 32, 11 }, { 0, 2, 42, 4, 12, 5, 8, 40, 3 }, { 1, 0, 38, 4, 10, 16, 9, 60, 7 }, { 0, 0, 29, 5, 16, 21, 11, 58, 7 }, { 0, 1, 21, 20, 59, 86, 5, 37, 9 }, { 270, 1, 2, 1, 4, 4, 18, 2, 26 }, { 134, 5, 5, 9, 13, 14, 80, 12, 87 }, { 15, 2, 9, 13, 19, 8, 95, 15, 125 }, { 17, 6, 8, 13, 14, 8, 87, 19, 112 }, { 20, 2, 18, 31, 22, 16, 120, 31, 148 }, { 15, 3, 13, 31, 40, 28, 256, 38, 222 }, { 14, 4, 40, 232, 216, 163, 1731, 288, 1875 }, { 115, 32, 63, 1165, 779, 257, 1575, 223, 1320 }, { 3, 3803, 30, 69, 143, 88, 79, 37, 64 }, { 8, 609, 36, 224, 480, 295, 242, 102, 123} };
//will work
double Try3[Detectors][NUMBER_OF_FILES] = { {0, 0, 364, 0, 0, 1, 1, 3, 0},{ 0, 0, 33, 1, 1, 3, 4, 8, 0},{ 0, 0, 17, 2, 1, 1, 1, 14, 0},{ 0, 0, 25, 2, 2, 0, 0, 11, 5},{ 0, 1, 15, 1, 3, 1, 3, 20, 1},{ 1, 0, 15, 2, 6, 5, 4, 24, 4},{ 0, 0, 14, 1, 7, 4, 4, 28, 3},{ 0, 0, 9, 8, 34, 49, 1, 18, 1},{ 116, 0, 0, 1, 1, 3, 6, 0, 7},{ 64, 2, 1, 6, 4, 7, 33, 4, 34},{ 3, 0, 2, 1, 1, 1, 40, 8, 51},{ 10, 3, 1, 4, 4, 3, 37, 8, 42},{ 9, 0, 6, 11, 8, 8, 45, 9, 63},{ 7, 2, 7, 12, 19, 13, 121, 24, 120},{ 7, 2, 16, 97, 99, 83, 851, 152, 1105},{ 62, 21, 43, 537, 388, 127, 763, 113, 718},{ 0, 1402, 12, 17, 41, 27, 21, 13, 20},{ 5, 331, 13, 105, 209, 142, 95, 36, 36} };
//will work
double Try4[Detectors][NUMBER_OF_FILES] = { {0, 0, 106, 0, 0, 0, 1, 0, 0},{ 0, 0, 8, 0, 0, 0, 1, 2, 0},{ 0, 0, 3, 0, 0, 0, 0, 5, 0},{ 0, 0, 5, 1, 0, 0, 0, 3, 1},{ 0, 0, 3, 0, 0, 0, 1, 4, 0},{ 0, 0, 3, 1, 2, 1, 0, 7, 1},{ 0, 0, 2, 0, 1, 1, 1, 7, 1},{ 0, 0, 2, 3, 6, 20, 0, 6, 0},{ 44, 0, 0, 0, 0, 0, 1, 0, 2},{ 17, 0, 0, 0, 1, 2, 8, 0, 6},{ 0, 0, 0, 0, 0, 0, 9, 0, 11},{ 3, 1, 0, 0, 2, 0, 2, 2, 6},{ 2, 0, 1, 2, 1, 3, 12, 2, 14},{ 4, 0, 2, 6, 3, 3, 43, 4, 43},{ 3, 0, 3, 40, 38, 35, 376, 66, 553},{ 28, 10, 10, 158, 108, 45, 311, 38, 340},{ 0, 506, 0, 4, 1, 3, 1, 5, 4},{ 1, 103, 3, 34, 64, 50, 17, 8, 7} };
//won't work
double Try5[Detectors][NUMBER_OF_FILES] = { { 0, 0, 7, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 1, 0},{ 0, 0, 0, 1, 0, 0, 0, 1, 0},{ 0, 0, 0, 0, 0, 0, 0, 4, 0},{ 0, 0, 0, 0, 0, 0, 0, 2, 0},{ 5, 5, 0, 0, 0, 0, 0, 0, 0},{ 5, 5, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 1, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 1, 1, 0, 3},{ 0, 0, 1, 1, 0, 0, 12, 1, 9},{ 1, 1, 2, 5, 9, 11, 132, 24, 226},{ 11, 11, 3, 22, 11, 4, 119, 16, 133},{ 0, 0, 0, 0, 0, 1, 0, 0, 0},{ 0, 0, 0, 0, 4, 0, 1, 1, 0} };
//won't work
double Try6[Detectors][NUMBER_OF_FILES] = { { 0, 0, 5, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 1, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 1, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 0, 0, 0},{ 0, 0, 0, 0, 0, 0, 6, 1, 19},{ 1, 0, 0, 5, 0, 0, 6, 2, 15},{ 0, 12, 0, 0, 0, 0, 0, 0, 0},{ 0, 2, 0, 0, 0, 0, 0, 1, 0} };


//Takes a weight vector that will be genetared later and multiplies it by the detection matrix. Compares the best score so far to the one calculated for each weight vector
//and saves both the score and the weight vector if it's a superior combination
void FindOptimalExposure(double* SetOfAttempts) {
	double VectorSum = 0, CollumnSum, AttemptMin = std::numeric_limits<double>::max(); // AttempdMin starts at maximum possible value
	double AttemptMax = 0;
	unsigned int j;


	// Normalizing weights vector
	for (int i = 0; i < NUMBER_OF_FILES; i++) VectorSum += SetOfAttempts[i];
	if (VectorSum == 0) return;
	for (j = 0; j < NUMBER_OF_FILES; ++j) SetOfAttempts[j] = SetOfAttempts[j] / VectorSum;

	// Multiplying weights by matrix
	for (int detector = 0; detector < Detectors; detector++) { //loops through all the detector indexes to create a vector of sums per collumn 
		CollumnSum = 0;
		for (int file = 0; file < NUMBER_OF_FILES; file++) 		//multiplying the weight vector with the corresponding matrix collumn 
			CollumnSum += SetOfAttempts[file] * Try[detector][file] / nSim * Activity;

		if (CollumnSum < AttemptMin) {//evaluates the minimum element for each weight vector and saves it as the score for comparison later on 
			AttemptMin = CollumnSum;
			MinIndex = detector;
		}

		if (CollumnSum > AttemptMax) { //evaluates the maximum element for each weight vector
			AttemptMax = CollumnSum;
			MaxIndex = detector;
		}

	}

	if (AttemptMin > bestScoreSoFar) { //compares the minimum saved for each attempt and compares it with the attempt to that point 
		bestScoreSoFar = AttemptMin;
		MinIndex = WorstDet;
		for (j = 0; j < NUMBER_OF_FILES; j++)
			bestWeights[j] = SetOfAttempts[j];

		if (AttemptMax > HighestScoreSoFar) {
			HighestScoreSoFar = AttemptMax;
			MaxIndex = BestDet;
		}

	}




	return;
}



//auxiliary functions to distribute the work between all the threads
//Each permutation is obtained by moving indexes along a set number of positions, and that number of positions depends on the number of files aka n. of simulations
//Permutations of n Elements in k groups. Given a specific permutation index we try to figure out what permutation corresponds to an index. An example could be like being given a number and determining what that number
//is on a specific base
void place_index_array(int* index, int n, int k, int permutation) {
	for (int i = k - 1; i >= 0; i--) {
		index[i] = permutation % n;
		permutation /= n;
	}
}


void increment_index_array(int* index, int n, int k) {
	while (--k >= 0) {
		if (index[k] < n - 1) {
			index[k]++;
			return;
		}
		else
			index[k] = 0;
	}
}


//what we feed each thread. This function takes in a specific starting point and end point within the entire set of permutations and iterates from the first permutation of that subset to the last permutation 
//of that subset. Por each permutation it calls the FindOptimalExposure function that multiples the weight vector with the matrix and evaluates the score of each permutation and saves the weight vector if there's
//a winning score. Heap assigned arrays just to fix some issues.
void work(unsigned long long beginning, unsigned long long end) {
	double* attempt = new double[NUMBER_OF_FILES];
	int* index = new int[NUMBER_OF_FILES];

	place_index_array(index, resolution, NUMBER_OF_FILES, beginning);

	for (unsigned long long j = beginning; j < end; j++) {

		for (int i = 0; i < NUMBER_OF_FILES; i++) {
			attempt[i] = ((double)index[i]) / ((double)resolution - 1);
		}

		FindOptimalExposure(attempt);

		increment_index_array(index, resolution, NUMBER_OF_FILES);
	}

	delete[] attempt;
	delete[] index;
}

