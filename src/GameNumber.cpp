#include "GameNumber.hpp"
#include "CoreDefs.hpp"

#include <cassert>
#include <random>
#include <cmath>

namespace game::core {

    auto Number::from_int (Number::IntegerRepr num, std::size_t length) noexcept -> Number
    {
        try {
            const auto converted = std::to_string(num);

            assert((length - converted.size() >= 0 && "Number must be sorter than vec size."));

            Number res;
            for (auto i = 0; i < length - converted.size(); ++i) {
                res.str.append("0");
            }
            return Number{std::move(res.str) + std::move(converted)};
        }
        catch (std::exception& e) {
            //TODO
            std::terminate();
        }
    }

    auto Number::random (uint8_t size) noexcept -> Number
    {
        try {
            static std::mt19937 gen{std::random_device{}()};
            static std::uniform_int_distribution<Number::IntegerRepr> dist{0, std::pow(10, size) - 1};
            return from_int(dist(gen), size);
        }
        catch (std::exception& e) {
            //TODO
            std::terminate();
        }
    }

    auto Number::valid() noexcept -> bool
    {
        auto copied {str};
        rng::sort(copied);
        return rng::adjacent_find(copied.begin(), copied.end()) == copied.end();
    }
}
