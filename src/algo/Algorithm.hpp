#pragma once

#include "Aliases.hpp"
#include "GameNumber.hpp"
#include "BullsCows.hpp"

#include <vector>
#include <optional>

namespace game::algo {

    class Algorithm {
    public:
        explicit Algorithm(const Number::SizeType size,
                           const double rightness_chance,
                           std::optional<Number::SizeType> similar_digits = std::nullopt);

        auto respond(const Number &guess) const noexcept -> BullsCows;
        void prune(const Number &num, const BullsCows guess);
        auto ask() const -> std::optional<Number>;
        auto num() const noexcept -> Number;
        auto num_size () const noexcept -> Number::SizeType;

    private:
        void prescribe(const Number &guess) const;

    private:
        double _rightness_chance;
        std::optional<Number::SizeType> _similar_digits;
        Number::SizeType _numsize;
        mutable std::optional<Number> _prescribed;
        std::vector<Number> _variants;
    };
} 