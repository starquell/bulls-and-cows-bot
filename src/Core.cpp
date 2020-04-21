#include "Core.hpp"
#include "Utils.hpp"
#include "CoreDefs.hpp"

#include <cmath>
#include <iostream>

namespace game::core {


    Core::Core(uint8_t size)
            : _num (Number::random(size))
    {
        const auto variants_size = std::pow(10, size);
        _variants.reserve(variants_size);

        for (auto&& num : views::iota (1, variants_size) |
                          views::transform ([size] (const auto num) {
                             return Number::from_int(num, size);
                          }) |
                          views::filter ([] (const auto num) {
                              return num.is_valid();
                          }))
        {
            _variants.push_back(PossibleNumber{std::forward<Number>(num)});
        }

        _variants.shrink_to_fit();

        for (auto num : _variants) {
            std::cout << num.num.str << ' ';
        }
    }
}
