#ifndef DNA_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define DNA_H

#include <random>
#include <chrono>
#include <vector>

int random (int lim);
std::vector<int> dna(int nbrEspace,int nbrEtoile,int orientation);

#endif
