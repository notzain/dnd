#include "RNG.h"

#include <ctime>

RNG::Impl RNG::impl{};

RNG::Impl::Impl()
{
    rng.seed(time(NULL));
}
