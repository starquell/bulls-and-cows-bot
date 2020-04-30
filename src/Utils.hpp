#pragma once

#include <random>
#include <thread>
#include <chrono>
#include <concepts>

namespace game {

    using namespace std::chrono_literals;

    namespace utils {

        template <std::integral Integer = int>
        auto random_integral (const Integer min, const Integer max) -> Integer
        {
            static thread_local std::mt19937 gen{std::random_device{}()};
            std::uniform_int_distribution <Integer> dist{min, max};
            return dist(gen);
        }

        template <std::floating_point Floating = double>
        auto random_floating (const Floating min, const Floating max) -> Floating
        {
            static thread_local std::mt19937 gen{std::random_device{}()};
            std::uniform_real_distribution <Floating> dist{min, max};
            return dist(gen);
        }

        auto true_with_chance (const double chance) -> bool;

        using std::this_thread::sleep_for;
    }
}