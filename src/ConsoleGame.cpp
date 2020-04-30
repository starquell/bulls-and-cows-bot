#include "ConsoleGame.hpp"

namespace game {


    ConsoleGame::ConsoleGame(const algo::Number::SizeType size,
                             const double complexity,
                             std::optional<Number::SizeType> similar_digits)
            : Game {size,
                    complexity,
                    similar_digits}
    {}

    auto ConsoleGame::first_turn() noexcept -> Game::Player
    {
        std::cout << "Game started! Prescribe your number and press any key when you'll be ready\n\n";
        std::cin.get();
        std::cout << "First turn will be...\t";
        const Player first = utils::random_integral(0, 1) == 1 ? Player::User : Player::Machine;
        std::cout << (first == Player::Machine ? "Mine!" : "Yours!") << "\n\n";
        return first;
    }

    void ConsoleGame::winner(const Game::Player player, const std::optional<Number>& my_num) noexcept
    {
        std::cout << (player == Player::User
                      ? "You won this battle, human, but not a war\n"
                      : "Predictable, but i won. ");
        if (player == Player::Machine) {
            std::cout << "My number was " << my_num.value().str << "\n\n";
        }
    }

    auto ConsoleGame::users_answer() noexcept -> BullsCows
    {
        std::cout << "Give you answer in format \"N M\", where N - number of bulls, M - cows\t";
        Number::SizeType bulls{}, cows{};
        std::cin >> bulls >> cows;
        return {bulls, cows};
    }

    void ConsoleGame::my_answer(BullsCows bc) noexcept
    {
        std::cout << "\nHm...\t";
        utils::sleep_for(1s);
        std::cout << bc.bulls << " bulls and " << bc.cows << " cows\n\n";
        std::cout << "Press Enter when you'll be ready\n";
        std::cin.get();
    }

    auto ConsoleGame::users_assumption(const algo::Number::SizeType size) noexcept -> algo::Number
    {
        std::cout << "Your turn! Try to guess my number\n";

        Number::IntegerRepr temp;
        std::cin >> temp;
        auto result = Number::from_int(temp, size);

        while (!result.has_value() || !result.value().valid()) {
            incorrect_input();
            std::cin >> temp;
            result = Number::from_int(temp, size);
        }

        return result.value();
    }

    void ConsoleGame::my_assumption(const algo::Number &num) noexcept
    {
        std::cout << "I think you number is...  ";
        utils::sleep_for(1s);
        std::cout << num.str << "\n\n";
    }

    void ConsoleGame::incorrect_input() noexcept
    {
        std::cout << "you donkey\n\n";
    }
}