#include "cards.h"
#include <array>
using namespace std;

class Pack {
public:
	Pack();
	Card pick_one();
	void shuffle_pack();
	void reset_current();
	bool empty_pack() const;
private:
	array<Card, 52> cards; // array of cards
	int current_card_index; // index of next card to be dealt
};


