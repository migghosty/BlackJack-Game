#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>
#include <locale>

// assign a random shuffle to the deck so it is different every time
int shuffle_deck(int i)
{
    srand(time(NULL));
    return rand()%i;
}

/////////////////
// CONSTRUCTOR //
/////////////////

Game::Game()
{
	char response;
    std::cout << intro << std::endl;
    std::cout << "Enter amount of players: ";
    std::cin >> n_players;
    initialize_players();
	response = get_response("Do you want to debug? [Y]/[N]");
	debug = (response == 'Y') ? true : false;
}

/////////////////////////////
// PUBLIC MEMBER FUNCTIONS //
/////////////////////////////

// Runs the game
void Game::run()
{
    bool continue_playing;

    // plays the game and starts asking the players
    // if they want to hit or not
    do {
        std::cout << "NEW GAME\n--------------------------" << std::endl;
        // initializes the deck
        initialize_deck();
        // initialize players hand
        initialize_hand();

        // display their hands
        display_players();

        continue_playing = play_game();
    } while (continue_playing);
}

// for testing purposes, omit the randomization
void Game::testing()
{
}

//////////////////////////////
// PRIVATE MEMBER FUNCTIONS //
//////////////////////////////


//Initializes the deck to be ready to play
void Game::initialize_deck()
{
    // clear the deck
    deck.clear();

    // iterate through all 13 cards
    for (size_t i=1; i <= n_cards; ++i)
    {
        // each card has 4 types (clover,spade,heart,diamond)
        // add each of those 4 cards
        deck.push_back(Card(i, CardType::Clover));
        deck.push_back(Card(i, CardType::Spade));
        deck.push_back(Card(i, CardType::Heart));
        deck.push_back(Card(i, CardType::Diamond));
    }

    // shuffle the deck at the end
    std::random_shuffle(deck.begin(),deck.end(),shuffle_deck);
}

// initializes all players
void Game::initialize_players()
{
    // clear the players
    players.clear();
    std::string name;

    // iterate through all 13 cards
    for (size_t i=0; i < n_players; ++i)
    {
        std::cout << "Player " << i+1 << " name: ";
        std::cin >> name;
        players.push_back(Player(name));
    }
}

void Game::initialize_hand()
{
    // first clear all players hands
    dealer.hand.clear();
    for (auto& player : players)
        player.hand.clear();

    // then give each player one card, do this twice (also account for the dealer)
    for (size_t i=0; i < 2; ++i)
    {
        for (auto& player : players)
            give_player_card(player);

        give_dealer_card();
    }
}

// get a card from the deck
Card Game::get_card()
{
    Card res = deck.back();
    deck.pop_back();
    return res;
}

// gives the player a card
void Game::give_player_card(Player& player)
{
    // player already busted
    if (player.current_sum() > 21)
        return;

    Card cur_card = get_card();
    player.give_card(cur_card);
}

// gives the dealer his set of cards
void Game::give_dealer_card()
{
    // the dealer will always at least 17
    if (dealer.current_sum() > dealer_min)
        return;
    
    Card cur_card = get_card();
    dealer.give_card(cur_card);
}

char Game::get_response(std::string question)
{
    char response;

    while (1)
    {
		std::cout << question << std::endl;
        std::cin >> response;
        response = std::toupper(response);
        switch (response)
        {
            case 'Y':
            case 'N':
                return response;
            
            default:
                std::cout << "invalid command" << std::endl;
        }
    }
	return ' '; // should never happen
}

void Game::give_dealer_his_cards()
{
    // give the dealer his set of cards
    while (dealer.current_sum() < dealer_min)
        give_dealer_card();
}

bool Game::play_game()
{
    char response;

    // ask the players if they want to hit or not
    // keep asking them until they decide no or they go over 21 (busted)
    for (auto& player : players)
    {
        response = ' ';
        while (response != 'N')
        {
            // show the players current number
            if (player.has_ace)
                std::cout << player.name << " you have " << player.current_sum() << '*' << std::endl;
            else
                std::cout << player.name << " you have " << player.current_sum() << std::endl;
            // ask if this player wants to hit
			response = get_response(player.name + ", do you want to hit? [Y]/[N] ");

            switch (response)
            {
                case 'Y':
                    // give the player a card
                    give_player_card(player);
                    
                    // if the player now has over 21, he busted so move to the next player
                    if (player.current_sum() > 21)
                    {
                        display_player(player);
                        std::cout << "Sorry " << player.name << ", you busted!" << std::endl;
                        response = 'N';
                    }
                    break;
                
                case 'N':
                    // go to the next player, no need to do anything
                    break;
            }
        }
    }

    // give the dealer his set of cards
	give_dealer_his_cards();

    std::cout << "\nFinal results below\n----------------------------" << std::endl;
    display_players();
    display_dealer();
    std::cout << "----------------------------" << std::endl;

	response = get_response("\nDo you want to play again? [Y]/[N]");
	return (response == 'Y') ? true : false;
}

bool Game::play_game_testing()
{
	return false;
}


// displays a given players hand
void Game::display_player(const Player& player) const
{
    // it will be displayed in the following format
    // [player_name] has [current_sum]
    if (player.current_sum() > 21)
        std::cout << player.name << " has " << player.current_sum() << "(busted)" << std::endl;
    
    else if (player.current_sum() == 21)
        std::cout << player.name << " has " << player.current_sum() << "(PERFECT SCORE)" << std::endl;
    else
        std::cout << player.name << " has " << player.current_sum() << std::endl;
}

// displays the current state of the game for the players
void Game::display_players() const
{
    // it will be displayed in the following format
    // [player_name] has [current_sum]
    for (const auto& player : players)
    {
        display_player(player);
    }
    std::cout << std::endl;
}

// displays the dealers hand
void Game::display_dealer() const
{
    display_player(dealer);
}
