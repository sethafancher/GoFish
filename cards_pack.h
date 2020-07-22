#ifndef CARDS_PACK_H
#define CARDS_PACK_H
#include "cards.h"
#include <array>
using namespace std;

class Pack {
public:
	// default constructs a pack in sorted order
	Pack();
	// "picks one" by incrementing the current index in the pack by one
	Card pick_one();
	// shuffles the pack randomly using a time-generated seed
	void shuffle_pack();
	// resets the pack by moving the current index back to zero
	void reset_current();
	// checks if the pack is empty
	bool empty_pack() const;
private:
	array<Card, 52> cards; // array of cards
	int current_card_index; // index of next card to be dealt
};
#endif

