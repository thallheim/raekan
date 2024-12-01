#include "RandGen.hpp"
#include <random>

cRandGen::cRandGen() {}
cRandGen::~cRandGen() {}

/// Returns a random int in the range [0, RAND_MAX].
int cRandGen::getInt() {
  return rand();
}

/// Returns a random int in the given range.
/// Uniform distribution using the `mt19937` generator.
///
int cRandGen::getInt(int min, int max) {
  std::random_device rdev;
  std::mt19937 generator(rdev());
  std::uniform_int_distribution<> distrib(min, max);
  return distrib(generator);
}

int cRandGen::getSeed() {
  return m_Seed1;
}

void cRandGen::setSeed(int seed) {
  m_Seed1 = seed;
}
