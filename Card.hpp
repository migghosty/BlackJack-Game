#ifndef CARD_HPP
#define CARD_HPP

// amount of cards (there are 13 with King being 13) &
// card types (clover,spade,heart,diamond)
constexpr int n_cards = 13;

// type a card can have
enum class CardType
{
    Clover,
    Spade,
    Heart,
    Diamond
};

// Struct to denote a card type
struct Card
{
    // number to represent the card number
    // Ace is 1, Jack is 11, Queen is 12, King is 13
    int number;

    CardType type;

    Card(int n, CardType ct=CardType::Clover) : number{n}, type{ct} {}
};

#endif
