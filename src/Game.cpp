#include "Game.hpp"

namespace game {

    Game::Game(algo::Number::SizeType size,
               const double complexity,
               std::optional<Number::SizeType> similar_digits) noexcept
    try : _algo {
            size,
            complexity,
            similar_digits 
            }
    {}
    catch (std::exception &e) {
        Logger::get()->critical(e.what());
        std::terminate();
    }

    auto Game::my_turn() noexcept -> Game::TurnResult
    {
        try {
            const auto asked = _algo.ask();
            if (!asked.has_value()) {
                incorrect_input();
                _winner = Player::None;
                return TurnResult::Unsuccesful;
            }
            my_assumption(asked.value());
            const BullsCows bc = users_answer();

            if (bc.bulls == _algo.num_size()) {
                _winner = Player::Machine;
                return TurnResult::Succesful;
            }

            _algo.prune(asked.value(), bc);

            return TurnResult::Succesful;
        }
        catch (std::exception &e) {
            Logger::get()->critical(e.what());
            std::terminate();
        }
    }

    void Game::run() noexcept
    {

        if (first_turn() == Player::User) {
            while (users_turn() == TurnResult::Unsuccesful)
            {}
        }
        while (_winner == Player::None) {
            while (my_turn() == TurnResult::Unsuccesful)
            {}

            if (_winner != Player::None) {
                break;
            }
            while (users_turn() == TurnResult::Unsuccesful)
            {}
        }
        if (_winner != Player::None) {
            winner(_winner, (_winner == Player::Machine
                                ? std::make_optional(_algo.num())
                                : std::nullopt));
        }
    }

    auto Game::users_turn() noexcept -> TurnResult
    {
        const Number assumption = users_assumption(_algo.num_size());
        try {

            if (!assumption.valid()) {
                incorrect_input();
                return TurnResult::Unsuccesful;
            }
            const BullsCows respond = _algo.respond(assumption);
            my_answer(respond);

            if (respond.bulls == _algo.num_size()) {
                _winner = Player::User;
                return TurnResult::Succesful;
            }

            return TurnResult::Succesful;
        }
        catch (std::exception &e)
        {
            Logger::get()->critical(e.what());
            std::terminate();
        }
    }
} 
