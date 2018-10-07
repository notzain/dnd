#ifndef DND_RNG_H
#define DND_RNG_H

#include <random>

class RNG {
    struct Impl {
        std::mt19937 rng;
        Impl();
    };
    static Impl impl;

public:
    static int generate(int min, int max)
    {
        std::uniform_int_distribution<std::mt19937::result_type> distribution(
            static_cast<unsigned long>(min),
            static_cast<unsigned long>(max));

        return static_cast<int>(distribution(impl.rng));
    }
};

#endif //DND_RNG_H
