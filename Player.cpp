#include "Player.hpp"
#include <iostream>

/////////////////
// CONSTRUCTOR //
/////////////////

Player::Player(std::string n)
    : name{n}
{
}

/////////////////////////////
// PUBLIC MEMBER FUNCTIONS //
/////////////////////////////

// give the player a certain card
void Player::give_card(Card& card)
{
    // if adding the new card results in busting, check if they have an Ace (would be worth 11)
    // and change it to a 1
    if (current_sum()+card.number > 21)
    {
        if (has_ace)
        {
            for (auto& cur_card : hand)
            {
                if (cur_card.number == 11)
                {
					std::cout << "trying to change 11 to 1" << std::endl;
                    cur_card.number = 1;
                    has_ace = false;
                    break;
                }
            }
        }
    }

    // if it is an Ace, check if you can add 11, if not add 1
    if (card.number == 1)
    {
        if (current_sum()+11 <= 21)
        {
            card.number = 11;
            has_ace = true;
        }
    }

    // cards like Jack, Queen, and King are worth 10
    else if (card.number > 10)
        card.number = 10;

    hand.push_back(card);
}

// calculates the sum of the players hand
int Player::current_sum() const
{
    int res = 0;
    for (const auto& card : hand)
    {
        res += card.number;
    }
    return res;
}
