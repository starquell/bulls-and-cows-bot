#pragma once

#include "GameNumber.hpp"

#include <vector>


namespace game::core {

    class Core {

        struct PossibleNumber {
            Number num;
            bool possible = true;
        };

    public:

        explicit Core (const uint8_t size);

    private:
        Number _num;
        std::vector<PossibleNumber> _variants;
    };
}