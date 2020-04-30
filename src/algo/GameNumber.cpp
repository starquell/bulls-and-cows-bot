#include "GameNumber.hpp"
#include "Aliases.hpp"
#include "../Utils.hpp"

#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <random>
#include <cmath>

namespace game::algo
{

auto Number::from_int(Number::IntegerRepr num, SizeType length) -> std::optional<Number>
{
    const auto converted = std::to_string(num);

    if (static_cast<int64_t>(length) - static_cast<int64_t>(converted.size()) < 0)
    {
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
    rng::sort(copied);
    return rng::adjacent_find(copied.begin(), copied.end()) == copied.end();
}

auto Number::with_similar_digits(Number other, const Number::SizeType digits) -> Number
{
    Number result{std::move(other)};
    static thread_local std::mt19937 gen {std::random_device{}()};
    std::shuffle(result.str.begin(), result.str.end(), gen);

    std::vector<Number::SizeType> unused_indexes;
    for (int i = 0; i < result.str.size(); ++i)
    {
        unused_indexes.push_back(i);
    }
    std::vector<char> unused_digits;
    for (int i = 0; i < 10; ++i)
    {
        unused_digits.push_back('0' + i);
    }
    for (auto digit : result.str)
    {
        unused_digits.erase(std::find (unused_digits.begin(), unused_digits.end(), digit));
    }
    rng::shuffle(unused_indexes, gen);
    rng::shuffle(unused_digits, gen);

    for (int i = 0; i < result.str.size() - digits; ++i)
    {
        result.str[unused_indexes.back()] = unused_digits.back();
        unused_indexes.pop_back();
        unused_digits.pop_back();
    }
    return result;
}

} // namespace game::algo
