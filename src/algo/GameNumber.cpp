#include "GameNumber.hpp"
#include "../Utils.hpp"
#include "Aliases.hpp"

#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <random>
#include <cmath>


namespace game::algo {

    auto Number::from_int(Number::IntegerRepr num, SizeType length) -> std::optional<Number>
    {
        const auto converted = std::to_string(num);

        if (converted.size() > length) {
            return std::nullopt;
        }

        Number res;
        for (auto i = 0; i < length - converted.size(); ++i)
        {
            res.str.append("0");
        }
        return Number{std::move(res.str) + std::move(converted)};
    }

    auto Number::random(const SizeType size) -> Number
    {
        static thread_local std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<Number::IntegerRepr> dist{0, std::pow(10, size) - 1};
        auto random = from_int(dist(gen), size).value();
        while (!random.valid())
        {
            random = from_int(dist(gen), size).value();
        }
        return random;
    }

    auto Number::valid() const -> bool
    {
        auto copied{str};
        ranges::sort(copied);
        return ranges::adjacent_find(copied) == copied.end();
    }

    auto Number::with_similar_digits(Number other, const Number::SizeType digits) -> Number
    {
        Number result{std::move(other)};
        static thread_local std::mt19937 gen {std::random_device{}()};
        ranges::shuffle(result.str, gen);

        auto unused_indexes = ranges::views::iota(std::size_t{}, result.str.size())
                            | ranges::to<std::vector>();

        auto unused_digits = ranges::views::iota (0, 10) 
                           | ranges::views::transform ([] (auto digit) {
                                 return '0' + digit;
                            })
                           | ranges::views::filter ([&] (auto digit) {
                                 return ranges::find(result.str, digit) == result.str.end();
                            })
                           | ranges::to<std::vector>();

        ranges::shuffle(unused_digits, gen);   

        for (const auto [index, digit] : ranges::views::zip(unused_indexes, unused_digits)
                                       | ranges::views::take (result.str.size() - digits)) 
        {
            result.str[index] = digit;
        }
        return result;
    }

} // namespace game::algo
