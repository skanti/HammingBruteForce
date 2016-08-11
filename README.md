# Haming-Brute-Force
A fast 64-bit Brute-Force Method to Match 256-bit Binary Descriptors by the Closest Haming Distance.

## Description

This is a C++ method that allows you to match two sets of binary descriptors according to the closest Haming distance.

## Performance
This method is approx. 300% faster than OpenCVs ```BruteForceHaming``` method. The reason is that I am using a 64-bit strategy
as opposed to the 8-bit strategy of OpenCV.

#### Timing for two sets of 500 256-dimensional binary descriptors:
- naive version: 60 ms
- OpenCV: 0.9 ms
- this version: 0.16 ms

## Features
- 20% speed up by using ```64-byte aligned plain arrays``` instead ```stl vectors```
- 50% speed up by using fully unrolled loops (256/64 = 4: innermost loop unrolled by 4)
- 30% speed up by using ```_popcnt64``` instead of ```_popcnt32``` on 32-byte registers. 
- 20% speed up by fully utilized instruction pipeline (Instruction-Level Parallelism)
- N speed up by OpenMP threading

## To-Do
- [x] Unroll loops by pre-processor software ```m4```.
- [ ] Writing kernel into clean assembly code.
- [ ] SS3 fast ```popcount``` version.

## Dependencies
- m4 (macro pre-processor)

# How-To Install
Have a look at the CMake file. Just run it with your individual paths.

## Contact
Feel free to contact me if you have questions or just want to chat about it.
