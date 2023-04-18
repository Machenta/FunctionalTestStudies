# FunctionalTestStudies
 
This is a basic C++ program designed to optimize the testing positions for RADEM engineering model, which is a a high energy particle detector designed for the JUICE mission.

The motivation behind this project comes down to the necessity to develop a test that is fast and simple to implement, meant to be performed between the environmental tests of RADEM. Ideally we’d use a particle beam for these tests, but that’s not always practical or even possible given the circumstances. This led to the development of a verification test to assure all sensors are working properly by using a cheaply available source of radiation.

The goal is to find the optimal position (or sets of positions) where a radiation source is to be placed for the detectors present in the engineering model to be irradiated for long enough for the validation test of the model to have enough statistical significance while minimizing testing time.

This particular alrogithm, when given a series of testing positions, computes and possible permutations of durations between the given set positions and finds the optimal combination of positions that minimizes testing time. This evaluation of each permuation is done ona distributed basis, using multithreading. 
