#pragma once

#include "algo/Algorithm.hpp"
#include "Logger.hpp"
#include "Utils.hpp"

#include <functional>
#include <optional>
#include <concepts>
#include <random>

namespace game {

    class Game
    {
    public:
        using Number = algo::Number;

        enum class Player
        {
            None,
            User,
            Machine
        };

        explicit Game(const algo::Number::SizeType size,
                      const double complexity = 1.0,
                      std::optional<Number::SizeType> similar_digits = std::nullopt) noexcept;

        void run() noexcept;

    private:
        enum class TurnResult
        {
            Succesful,
            Unsuccesful
        };

        auto my_turn() noexcept -> TurnResult;

        auto users_turn() noexcept -> TurnResult;

        virtual auto first_turn() noexcept -> Player = 0;

        virtual void winner(const Player player, const std::optional<Number> &my_num = std::nullopt) noexcept = 0;

        virtual auto users_answer() noexcept -> BullsCows = 0;

        virtual void my_answer(const BullsCows bc) noexcept = 0;

        virtual auto users_assumption(const Number::SizeType size) noexcept -> Number = 0;

        virtual void my_assumption(const Number &num) noexcept = 0;

        virtual void incorrect_input() noexcept = 0;

    private:
        algo::Algorithm _algo;
        Player _winner = Player::None;
    };

    template <class T>
    concept ConfiguredGame = std::derived_from <T, Game>;

    template <ConfiguredGame GameType>
    auto easy_game (const Game::Number::SizeType size) -> GameType
    {
        if (utils::true_with_chance(0.5)) {
            return GameType {size, 0.5, size};
        }
        else {
            return GameType {size, 0.3, 0};
        }
    }

    template <ConfiguredGame GameType>
    auto medium_game (const Game::Number::SizeType size) -> GameType 
    {
        if (utils::true_with_chance (0.3)) {
            if (utils::true_with_chance (0.5)) {
                return GameType {size, 0.65, 0};
            }
            else {
                return GameType {size, 0.75, size};
            }
        }
        else {
            return GameType {size, 0.5};
        }
    }

    template <ConfiguredGame GameType>
    auto hard_game (const Game::Number::SizeType size) -> GameType 
    {
         if (utils::true_with_chance (0.2)) {
            if (utils::true_with_chance (0.5)) {
                return GameType {size, 0.75, 0};
            }
            else {
                return GameType {size, 0.85, size};
            }
        }
        else {
            static thread_local std::mt19937 gen {std::random_device{}()};
            std::uniform_int_distribution <Game::Number::SizeType> dist {1, size - 1};
            return GameType {size, 0.6, dist(gen)};
        }
    }
}
