# Optimal Test Positioning for RADEM Engineering Model
 
This C++ program is designed to optimize testing positions for the RADEM engineering model, a high-energy particle detector developed for the JUICE mission.

## Motivation
The need for a fast and simple testing method between RADEM's environmental tests led to the development of this project. While a particle beam is ideal for testing, it is not always practical or possible due to various circumstances. As a result, this project focuses on developing a verification test to ensure all sensors function correctly using an affordable radiation source.

## Goal
The objective is to determine the optimal position(s) for placing a radiation source to irradiate the detectors in the engineering model. This ensures the validation test of the model achieves sufficient statistical significance while minimizing testing time.

## Algorithm
This algorithm evaluates a series of testing positions and calculates possible permutations of durations between the given set of positions. It then identifies the optimal combination of positions that minimizes testing time. The evaluation of each permutation is performed in a distributed manner using multithreading.
