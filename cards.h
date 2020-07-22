#ifndef CARDS_H
#define CARDS_H
#include <string>
using namespace std;

class Card {
public:
	// rank and suit names
	static constexpr const char* const RANK_TWO = "Two";
	static constexpr const char* const RANK_THREE = "Three";
	static constexpr const char* const RANK_FOUR = "Four";
	static constexpr const char* const RANK_FIVE = "Five";
	static constexpr const char* const RANK_SIX = "Six";
	static constexpr const char* const RANK_SEVEN = "Seven";
	static constexpr const char* const RANK_EIGHT = "Eight";
	static constexpr const char* const RANK_NINE = "Nine";
	static constexpr const char* const RANK_TEN = "Ten";
	static constexpr const char* const RANK_JACK = "Jack";
	static constexpr const char* const RANK_QUEEN = "Queen";
	static constexpr const char* const RANK_KING = "King";
	static constexpr const char* const RANK_ACE = "Ace";

	static constexpr const char* const SUIT_SPADES = "Spades";
	static constexpr const char* const SUIT_HEARTS = "Hearts";
	static constexpr const char* const SUIT_CLUBS = "Clubs";
	static constexpr const char* const SUIT_DIAMONDS = "Diamonds";
	//default ctor
	Card();
	// custom ctor
	Card(const string& rank_in, const string& suit_in);
	// gets the rank of a card
	string get_rank() const;
	// gets the suit of a card
	string get_suit() const;

private:
	string rank;
	string suit;
};

// Suits in order from lowest suit to highest suit.
constexpr const char* const SUIT_NAMES_BY_WEIGHT[] = {
  Card::SUIT_SPADES,
  Card::SUIT_HEARTS,
  Card::SUIT_CLUBS,
  Card::SUIT_DIAMONDS
};
const int NUM_SUITS = 4;

// Ranks in order from lowest rank to highest rank.
constexpr const char* const RANK_NAMES_BY_WEIGHT[] = {
  Card::RANK_TWO,
  Card::RANK_THREE,
  Card::RANK_FOUR,
  Card::RANK_FIVE,
  Card::RANK_SIX,
  Card::RANK_SEVEN,
  Card::RANK_EIGHT,
  Card::RANK_NINE,
  Card::RANK_TEN,
  Card::RANK_JACK,
  Card::RANK_QUEEN,
  Card::RANK_KING,
  Card::RANK_ACE
};
const int NUM_RANKS = 13;

// operator overlaods
bool operator==(const Card& lhs, const Card& rhs);

bool operator!=(const Card& lhs, const Card& rhs);

bool operator<(const Card& lhs, const Card& rhs);

ostream &operator<<(ostream &output, const Card & card);

#endif