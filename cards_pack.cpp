#include "cards_pack.h"
#include <random>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

Pack::Pack()
	:current_card_index(0) {
	int i = 0;
	// iterate through the suits
	for (int suit = 0; suit < 4; ++suit) {
		//iterate throug the ranks
		for (int rank = 7; rank < 13; ++rank) {
			// initialize the card at index i with the rank and suit at their current indecies
			Card card(RANK_NAMES_BY_WEIGHT[rank],
				SUIT_NAMES_BY_WEIGHT[suit]);
			cards[i] = card;
			// increment i
			++i;
		}
	}
}

Card Pack::pick_one() {
	Card card = cards[current_card_index];
	++current_card_index;
	return card;
}

void Pack::reset_current() {
	current_card_index = 0;
}

bool Pack::empty_pack() const {
	if (current_card_index == 52) {
		return true;
	}
	else {
		return false;
	}
}

void Pack::shuffle_pack() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
	reset_current();
}