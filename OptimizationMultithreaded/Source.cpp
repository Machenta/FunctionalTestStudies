#include <thread>
#include <iostream>
#include <string>
#include <map>
#include "optimize.h"


const int numThreads = 12;

int main() {

	std::map<int, std::string> DetectorIDs;
	std::string DetectorID[] = { "HISD-0", "HISD-1",
		"PSD-1", "PSD-2", "PSD-3", "PSD-4", "PSD-5", "PSD-6", "PSD-7", "PSD-8",
		"ESD-1", "ESD-2", "ESD-3", "ESD-4", "ESD-5", "ESD-6", "ESD-7", "ESD-8" };

	for (int i = 0; i < 18; i++) {
		DetectorIDs.insert(std::pair <int, std::string>(i, DetectorID[i]));
	}


	int i, j;
	std::thread worker[numThreads];
	unsigned long long workToDo = pow(resolution, NUMBER_OF_FILES); //evaluates the number of total permutations that need to be tried. Permutations with repetition of nFiles^resolution
	unsigned long long blockSize = (workToDo + 1) / numThreads; // Assigns a certain number of thos permutations to each thread

	//how we distribute the work between the threads. We feed it a work function that encompasses all the calculations we need done and give it the necessary parameters
	for (i = 0; i < numThreads; i++) {
		worker[i] = std::thread(work, i * blockSize, (i + 1) * blockSize);
	}

	//standard thread practice
	for (i = 0; i < numThreads; i++) {
		worker[i].join();
	}

	//can be improved. How we output end result
	std::cout << "Best Combination is ";
	for (int i = 0; i < NUMBER_OF_FILES; ++i)
		std::cout << std::to_string(bestWeights[i]) + (i == NUMBER_OF_FILES - 1 ? "\n" : ",");

	std::cout << "Best Score:" + std::to_string(bestScoreSoFar) << std::endl;

	std::cout << "Highest Score:" + std::to_string(HighestScoreSoFar) << std::endl;

	double time = MinCount / bestScoreSoFar;

	double FastestDetector = MinCount / HighestScoreSoFar;

	std::cout << "Slower Detector:" + std::to_string(time) + "s" << std::endl;

	std::cout << "Fastest Detector:" + std::to_string(FastestDetector) + "s" << std::endl;

	std::cout << "Worst Detector:" + std::to_string(MinIndex) + ", " + DetectorIDs[MinIndex] << std::endl;

	std::cout << "Best Detector:" + std::to_string(MaxIndex) + ", " + DetectorIDs[MaxIndex] << std::endl;
}
