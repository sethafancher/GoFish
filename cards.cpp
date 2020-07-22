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
	:rank("UNDEFINED"), suit("CARD") {}

// custom ctor
Card::Card(const string& rank_in, const string& suit_in) 
	:rank(rank_in), suit(suit_in) {}

// gets rank
string Card::get_rank() const {
	return rank;
}

// gets suit
string Card::get_suit() const {
	return suit;
}

// checks if two cards have the same rank
bool operator==(const Card& lhs, const Card& rhs) {
	if (lhs.get_rank() == rhs.get_rank()) {
		return true;
	}
	return false;
}

// checks if two cards have different ranks
bool operator!=(const Card& lhs, const Card& rhs) {
	if (lhs.get_rank() == rhs.get_rank()) {
		return false;
	}
	return true;
}

// checks if one card is less than another card (used for sorting hand)
bool operator<(const Card& lhs, const Card& rhs) {
	// initialize variables
	string rankL = lhs.get_rank();
	string rankR = rhs.get_rank();
	string suitL = lhs.get_suit();
	string suitR = rhs.get_suit();
	int lhsRankIndex = 0;
	int rhsRankIndex = 0;
	int lhsSuitIndex = 0;
	int rhsSuitIndex = 0;
	// iterate through the vector until reaching the lhs rank
	while (rankL != RANK_NAMES_BY_WEIGHT[lhsRankIndex]) {
		++lhsRankIndex;
	}
	// iterate through the vector until reaching the rhs rank
	while (rankR != RANK_NAMES_BY_WEIGHT[rhsRankIndex]) {
		++rhsRankIndex;
	}
	// check if the lhs rank is less than the rhs rank
	if (lhsRankIndex < rhsRankIndex) {
		// if it is, return true
		return true;
	}
	// check if the lhs rank is equal to the rhs rank
	else if (lhsRankIndex == rhsRankIndex) {
		// if it is, perform the same algorithm in the suits
		while (suitL != SUIT_NAMES_BY_WEIGHT[lhsSuitIndex]) {
			++lhsSuitIndex;
		}
		while (suitR != SUIT_NAMES_BY_WEIGHT[rhsSuitIndex]) {
			++rhsSuitIndex;
		}
		if (lhsSuitIndex < rhsSuitIndex) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		// if it's neither, return false
		return false;
	}
}

// prints out a card
ostream& operator<<(ostream& output, const Card& card) {
	output << card.get_rank() << " of " << card.get_suit();
	return output;
}