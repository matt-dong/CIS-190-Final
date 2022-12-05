#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <memory>

// returns null if height <= width * height - 1
std::unique_ptr<std::pair<int, int> []> randomMineLocations(int, int, int, int, int);

#endif
