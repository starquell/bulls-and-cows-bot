#pragma once

#include <string>

namespace game::core {

    struct Number {

        std::string str;

        using IntegerRepr = unsigned;

        static auto from_int (IntegerRepr num, const std::size_t length) -> Number;
        static auto random (const uint8_t size) noexcept -> Number;

        auto valid () -> bool;
    };
}


