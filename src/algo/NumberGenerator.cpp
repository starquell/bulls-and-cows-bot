#include "NumberGenerator.hpp"
#include "Aliases.hpp"

#include <ranges>
#include <cmath>
#include <iostream>

namespace game::algo {

    auto NumbersGenerator::operator()(const Number::SizeType size) -> std::vector<Number>
    {

        if (_cache.contains(size)) {
            return _cache[size];
        }

        // std::vector <Number> result;
        // const auto variants_size = std::pow(10, size);
        // result.reserve(variants_size);

        // for (auto&& num : views::iota (1, variants_size) |
        //                   views::transform ([size] (const auto num) {
        //                       return Number::from_int(num, size).value();
        //                   }) |
        //                   views::filter ([] (const auto num) {
        //                       return num.valid();
        //                   }))
        // {
        //     result.emplace_back(std::move(num));
        // }
        // result.shrink_to_fit();

        const auto result = views::iota (1, std::pow(10, size)) |
                            views::transform ([size] (const auto num) {
                                return Number::from_int(num, size).value();
                            }) |
                            views::filter ([] (const auto num) {
                               return num.valid();
                            })
                            | ranges::to<std::vector>();

        _cache[size] = result;

//        for (const auto i : result) {
//            std::cout << i.str << ' ';
//        }
        return result;
    }

    auto NumbersGenerator::get() -> NumbersGenerator&
    {
        static NumbersGenerator gen;
        return gen;
    }

    NumbersGenerator::NumbersGenerator()
        : _cache {AsyncCache<Number::SizeType, std::vector<Number>>::get()}
    {}
}

