#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.hpp"

// A player will consist of an id
// and a vector of cards they are holding, as well as their current sum
struct Player
{
    std::string name;
    std::vector<Card> hand;
    bool has_ace{false};

    Player(std::string n);

    void give_card(Card& card);
    int current_sum() const;
};

#endif