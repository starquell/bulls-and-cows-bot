#pragma once

#include <string>
#include <optional>

namespace game::algo {

    struct Number {

        std::string str;

        using IntegerRepr = unsigned;
        using SizeType = std::uint16_t;

        static auto from_int(IntegerRepr num, const SizeType length) -> std::optional<Number>;
        static auto with_similar_digits(Number other, const SizeType digits) -> Number;
        static auto random(const SizeType size) -> Number;

        auto valid() const -> bool;
    };
} // namespace game::algo
