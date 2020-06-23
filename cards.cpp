#include <string>
#include <iostream>
#include "cards.h"

using namespace std;
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

// default ctor
Card::Card()
	:rank(RANK_ACE), suit(SUIT_SPADES) {}

// custom ctor
Card::Card(const string& rank_in, const string& suit_in) 
	:rank(rank_in), suit(suit_in) {}

string Card::get_rank() const {
	return rank;
}

string Card::get_suit() const {
	return suit;
}

bool operator==(const Card& lhs, const Card& rhs) {
	if (lhs.get_rank() == rhs.get_rank()) {
		return true;
	}
	return false;
}

bool operator!=(const Card& lhs, const Card& rhs) {
	if (lhs.get_rank() == rhs.get_rank()) {
		return false;
	}
	return true;
}

ostream& operator<<(ostream& output, const Card& card) {
	output << card.get_rank() << " of " << card.get_suit();
	return output;
}