
#include "src/ConsoleGame.hpp"
#include "src/Logger.hpp"
#include <iostream>

auto main (int argc, char** argv) -> int
{

//    game::algo::Algorithm a {3};
//    a.prune(game::algo::Number(std::string("210")), game::BullsCows{2, 1});

    game::Logger::get()->log(spdlog::level::warn, "sds");

    auto game = game::medium_game<game::ConsoleGame>(4);
    game.run();

    return 0;
}

