#include "Game.hpp"
#include "Utils.hpp"

#include <iostream>
#include <optional>

namespace game {

class ConsoleGame : public Game {

    public:
        ConsoleGame(const Number::SizeType size,
                    const double complexity,
                    std::optional<Number::SizeType> similar_digits = std::nullopt);

    private:
        auto first_turn() noexcept -> Player override;

        void winner(const Player player, const std::optional<Number> &my_num = std::nullopt) noexcept override;

        auto users_answer() noexcept -> BullsCows override;

        void my_answer(const BullsCows bc) noexcept override;

        auto users_assumption(const Number::SizeType size) noexcept -> Number override;

        void my_assumption(const Number &num) noexcept override;

        void incorrect_input() noexcept override;
    };
} // namespace game
