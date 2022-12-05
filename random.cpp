#include <memory>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

unique_ptr<pair<int, int> []> randomMineLocations(int width,
                                                  int height,
                                                  int excludeX,
                                                  int excludeY,
                                                  int amount)
{
    if (amount > width * height - 1)
        return nullptr;

    // This code uses std::vector and some standard library algorithms, which we haven't covered in class yet
    random_device rd;
    default_random_engine g{rd()};

    vector<pair<int, int>> v;
    for (int i {0}; i < width; ++i)
    {
        for (int j {0}; j < height; ++j)
        {
            if (i != excludeX || j != excludeY)
                v.emplace_back(i, j);
        }
    }

    shuffle(v.begin(), v.end(), g);

    auto p {make_unique<pair<int, int> []>(amount)};
    for (int i {0}; i < amount; ++i)
    {
        p[i] = v[i];
    }
    return p;
}
