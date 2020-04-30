#pragma once

#include "GameNumber.hpp"
#include "AsyncCache.hpp"

#include <vector>

namespace game::algo {

    class NumbersGenerator {
    private:
        explicit NumbersGenerator();
    public:
        NumbersGenerator (const NumbersGenerator&) = delete;
        NumbersGenerator (NumbersGenerator&&) = delete;

        NumbersGenerator& operator= (const NumbersGenerator&) = delete;
        NumbersGenerator& operator= (NumbersGenerator&&) = delete;

        ~NumbersGenerator() = default;

        static auto get() -> NumbersGenerator&;

        auto operator() (const Number::SizeType size) -> std::vector<Number>;

    private:
        AsyncCache<Number::SizeType, std::vector<Number>>& _cache;
    };
}
