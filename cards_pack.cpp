#include "cards_pack.h"
#include <random>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

// default ctor; assembles the pack in sorted order
Pack::Pack()
	:current_card_index(0) {
	int i = 0;
	// iterate through the suits
	for (int suit = 0; suit < 4; ++suit) {
		//iterate throug the ranks
		for (int rank = 0; rank < 13; ++rank) {
			// initialize the card at index i with the rank and suit at their current indecies
			Card card(RANK_NAMES_BY_WEIGHT[rank],
				SUIT_NAMES_BY_WEIGHT[suit]);
			cards[i] = card;
			// increment i
			++i;
		}
	}
}

// "picks one" by incrementing the current index in the pack by one
Card Pack::pick_one() {
	Card card = cards[current_card_index];
	++current_card_index;
	return card;
}

// resets the pack by moving the current index back to zero
void Pack::reset_current() {
	current_card_index = 0;
}

// checks if the pack is empty by seeing if thte current index is 52
bool Pack::empty_pack() const {
	if (current_card_index == 52) {
		return true;
	}
	else {
		return false;
	}
}

// shuffles the pack randomly using a time-generated seed
void Pack::shuffle_pack() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	// reset the current index
	reset_current();
}