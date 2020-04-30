#include "Algorithm.hpp"
#include "Aliases.hpp"
#include "NumberGenerator.hpp"
#include "../Utils.hpp"

#include <cmath>
#include <iostream>
#include <random>

namespace game::algo
{

    Algorithm::Algorithm(const Number::SizeType size,
                         const double rightness_chance,
                         std::optional<Number::SizeType> similar_digits)
        : _numsize{size},
          _rightness_chance{rightness_chance},
          _similar_digits{similar_digits},
          _variants{NumbersGenerator::get()(size)}
    {
    }

    void Algorithm::prescribe(const Number &guess) const
    {
        if (_similar_digits.has_value())
        {
            _prescribed = Number::with_similar_digits(guess, _similar_digits.value());
        }
        else
        {
            _prescribed = Number::random(_numsize);
        }
    }

    auto Algorithm::respond(const Number &guess) const noexcept -> BullsCows
    {
        if (!_prescribed.has_value())
        {
            prescribe(guess);
        }

        BullsCows bc;
        for (int i = 0; i < guess.str.size(); ++i)
        {

            if (guess.str[i] == _prescribed.value().str[i])
            {
                ++bc.bulls;
            }
            else if (rng::find(_prescribed.value().str.begin(),
                               _prescribed.value().str.end(), guess.str[i]) !=
                     _prescribed.value().str.end())
            {
                ++bc.cows;
            }
        }
        return bc;
    }

    void Algorithm::prune(const Number &guess, BullsCows answer)
    {
        static const auto unsuitable =
            [&](const Number &num) {
                BullsCows counted;
                for (int i = 0; i < num.str.size(); ++i)
                {
                    if (num.str[i] == guess.str[i])
                    {
                        ++counted.bulls;
                    }
                }
                if (utils::true_with_chance(_rightness_chance) && counted.bulls != answer.bulls)
                {

                    return true;
                }
                for (int i = 0; i < num.str.size(); ++i)
                {
                    for (int j = 0; j < num.str.size(); ++j)
                    {
                        if (i == j)
                        {
                            continue;
                        }
                        if (num.str[i] == guess.str[j])
                        {
                            ++counted.cows;
                        }
                    }
                }
                return counted.cows != answer.cows;
            };

        _variants.erase(std::remove_if(_variants.begin(),
                                       _variants.end(),
                                       unsuitable),
                        _variants.end());
        for (const auto &i : _variants)
        {
            std::cout << i.str << ' ';
        }
        std::cout << std::endl;
        if (_variants.empty())
        {
            std::cout << "jepa";
        }
    }

    auto Algorithm::ask() const -> std::optional<Number>
    {
        static thread_local std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<std::size_t> dist{0, _variants.size() - 1};
        return _variants.empty() ? std::nullopt : std::optional{_variants[dist(gen)]};
    }

    auto Algorithm::num() const noexcept -> Number
    {
        return _prescribed.value();
    }

    auto Algorithm::num_size() const noexcept -> Number::SizeType
    {
        return _numsize;
    }
} // namespace game::algo
