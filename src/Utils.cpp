#include "Utils.hpp"

namespace game::utils {

    auto true_with_chance(const double chance) -> bool {
        return random_floating<double> (0.0, 1.0) <= (chance + 0.01);
    }
}
