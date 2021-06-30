#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <random>
#include "Player.hpp"
#include "Card.hpp"

constexpr int dealer_min = 17;

class Game
{

public:
    // constructor
    Game();

    // runs the game
    void run();
	void testing();

    // destructor
    ~Game() = default;

private:
    // ADD MEMBER VARIABLES HERE //
    std::vector<Card> deck;
    unsigned n_players;
    std::vector<Player> players;
    Player dealer{"Dealer"};
	bool debug;
    std::string intro = " The game is BlackJack.\n \
The point of the game is to get as close to 21 as possible.\n \
Jacks, Queens, and Kings all serve as 10 points, and the numbers \
2-10 serve as their number respectively.\n \
An Ace is special. It can either serve as an 11 or 1.\n \
To show that you have an Ace worth 11, you will have \
a * next to the amount you have.\n \
HAVE FUN PLAYING!!\n";

    // ADD MEMBER FUNCTIONS HERE //
    void initialize_deck();
    void initialize_players();
    Card get_card();
    void give_player_card(Player& player);
    void give_dealer_card();
    void initialize_hand();
    bool play_game();
	bool play_game_testing();
    void display_player(const Player& player) const;
    void display_players() const;
    void display_dealer() const;
	char get_response(std::string question);
	void give_dealer_his_cards();
	int get_card_number();

};

#endif
