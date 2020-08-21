#include <string>
#include <deque>
#include "cards.h"
#include "players.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

// HUMAN PLAYER CLASS
class Human : public Player {
public: 
	// custom ctor; intalizes name and score
	Human(string name_in)
		:name(name_in), score(0) {}

	// prints the hand in a readable format
	void print_hand() {
		for (size_t i = 0; i < hand.size(); ++i) {
			cout << "Human player " << name << "'s hand: [" << i << "] "
				<< hand[i].Card::get_rank() << " of " << hand[i].Card::get_suit() <<
				endl;
		}
	}

	// gets the player's name
	const string& get_name() const override {
		return name;
	}

	// adds the cards currently being given to the player's hand
	vector<Card> get_cards_being_given() override {
		// create temporary storage
		vector <Card> cards;
		// fill up the temporary storage
		for (size_t i = 0; i < cards_being_given.size(); ++i) {
			cards.push_back(cards_being_given[i]);
		}
		// clear the current cards being given
		cards_being_given.clear();
		return cards;
	}

	// gets the score
	const int& get_score() const override {
		return score;
	}

	// checks to see if the player's hand is empty
	bool empty() override {
		return hand.size() == 0;
	}

	// checks to see if the player has a requested rank
	bool has_req_card(string rank) override {
		for (size_t i = 0; i < hand.size(); ++i) {
			if (hand[i].get_rank() == rank) {
				return true;
			}
		}
		return false;
	}

	// checks to see if a player has a group of four, and deletes it
	void check_for_group() override {
		sort_hand();
		for (size_t i = 0; i < hand.size(); ++i) {
			int count = 0;
			for (size_t j = 0; j < hand.size(); ++j) {
				if (hand[i].get_rank() == hand[j].get_rank()) {
					++count;
					if (count == 4) {
						hand.erase(hand.begin() + i, hand.begin() + j + 1);
						++score; // add one to the player's score
						cout << name << " got a group of four!" << endl;
					}
				}
			}
		}
	}

	// asks the player which rank they want to ask for
	Card make_card_query() override {
		sort_hand();
		print_hand();
		size_t card_selection = 0;
		cout << "Select a card to request: " << endl;		
		cin >> card_selection;
		// male sure their input is valid
		while (card_selection < 0 || card_selection > hand.size() - 1) {
			cout << "ERROR: PLEASE SELECT A CARD FROM YOUR HAND USING ITS ASSIGNED NUMBER" << endl;
			cin >> card_selection;
		}
		return hand[card_selection];
	}
	
	// asks the player which player they want to request from
	int make_player_query() override {
		int player_selction;
		cout << "Select a player to request from: " << endl;
		cin >> player_selction;
		return player_selction;
	}

	// USELESS FOR THIS CLASS
	Card make_card_queryAI(map<string, string> card_requests) override {
		assert(false);
		Card c;
		return c;
	}
	int make_player_queryAI(map<string, string> card_requests, vector<string> name_vec) override {
		assert(false);
		return 0;
	}
	void add_count() override {
		assert(false);
	}

	// deletes all cards of a selected rank from the player's hand after recording them
	int give_cards(string rank) override {
		int count = 0;
		for (size_t i = 0; i < hand.size(); ++i) {
			if (hand[i].get_rank() == rank) {
				// record the cards being given
				cards_being_given.push_back(hand[i]);
				// delete the cards being given from this player's hand
				hand.erase(hand.begin() + i);
				--i;
				++count;
			}
		}
		return count;
	}
	
	// reciever functions that give the player a certain number of cards
	void receive_1card(const Card &card) override {
		hand.push_front(card);
	}
	void receive_2card(const Card &card1, const Card &card2) override {
		hand.push_front(card1);
		hand.push_front(card2);
	}
	void receive_3card(const Card &card1, const Card &card2, const Card &card3) override {
		hand.push_front(card1);
		hand.push_front(card2);
		hand.push_front(card3);
	}

	// sorts the player's hand
	void sort_hand() override {
		sort(hand.begin(), hand.end());
	}

private:
	// the player's name
	string name;
	// the player's score
	int score;
	// a deque holding the player's hand
	deque<Card> hand;
	// a vector holdig the current cards being given by a player
	vector<Card> cards_being_given;
	// USELESS FOR THIS CLASS
	map<string, int> card_age;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

// AI PLAYER CLASS
class AI : public Player {
public:

	// custom ctor; initalizes name and score
	AI(string name_in)
		:name(name_in), score(0) {}

	// gets name
	const string& get_name() const override {
		return name;
	}

	// gets score
	const int& get_score() const override {
		return score;
	}

	// prints hand; used for testing purposes
	void print_hand() {
		for (size_t i = 0; i < hand.size(); ++i) {
			cout << "Human player " << name << "'s hand: [" << i << "] "
				<< hand[i].get_rank() << " of " << hand[i].get_suit() <<
				endl;
		}
	}

	// USELESS FOR THIS CLASS
	Card make_card_query() override {
		assert(false);
		Card c;
		return c;
	}
	int make_player_query() override {
		assert(false);
		return 0;
	}

	// adds the cards currently being given to the player's hand
	vector<Card> get_cards_being_given() override {
		// temporary storage
		vector <Card> cards;
		// fill up the temporary storage
		for (size_t i = 0; i < cards_being_given.size(); ++i) {
			cards.push_back(cards_being_given[i]);
		}
		// clear the current cards being given
		cards_being_given.clear();
		return cards;
	}

	// checks to see if the player's hand is empty
	bool empty() override {
		return hand.size() == 0;
	}

	// AI algorithm for choosing a rank
	Card make_card_queryAI(map<string, string> card_requests) override {
		sort_hand();
		// first, play the highest rank that has been asked for by another player
		for (size_t i = 0; i < hand.size(); ++i) {
			if ((card_requests.find(hand[i].get_rank()) != card_requests.end()) && 
				(card_requests.at(hand[i].get_rank()) != name)) {
				return hand[i];
			}
		}
		// second, play the highest rank with a frequency greater than one
		Card c = hand[0];
		int max = 0;
		for (size_t i = 0; i < hand.size(); ++i) {
			int count = 0;
			for (size_t j = 0; j < hand.size(); ++j) {
				if (hand[i].get_rank() == hand[j].get_rank()) {
					++count;
				}
			}
			if (count >= max) {
				max = count;
				c = hand[i];
			}
		}
		if (max > 1) {
			return c;
		}
		// otherwise, play the newest card in the player's hand
		else {
			int min = card_age[hand[0].get_rank()];
			string card = hand[0].get_rank();
			for (auto it = card_age.begin(); it != card_age.end(); ++it) {
				int age = it->second;
				if (age < min) {
					min = age;
					card = it->first;
				}
			}
			for (size_t i = 0; i < hand.size(); ++i) {
				if (hand[i].get_rank() == card) {
					return hand[i];
				}
			}
		}
		return hand[0];
	}

	// AI algorithm for choosing a player
	int make_player_queryAI(map<string, string> card_requests, vector<string> name_vec) override {
		// first, find the highest rank asked for by another player, and choose that player
		for (size_t i = 0; i < hand.size(); ++i) {
			if (card_requests.find(hand[i].get_rank()) != card_requests.end() &&
				(card_requests.at(hand[i].get_rank()) != name)) {
				string name = card_requests[hand[i].get_rank()];
				for (size_t i = 0; i < name_vec.size(); ++i) {
					if (name_vec[i] == name) {
						return i;
					}
				}
			}
		}

		// POSSIBLE OTHER METHOD HERE (most cards)

		// otherwise, ask the first player that doesn't share this player's name
		for (size_t i = 0; i < name_vec.size(); ++i) {
			if (name_vec[i] != name) {
				return i;
			}
		}
		return 0;
	}

	// checks to see if the player has a requested rank
	bool has_req_card(string rank) override {
		for (size_t i = 0; i < hand.size(); ++i) {
			if (hand[i].get_rank() == rank) {
				return true;
			}
		}
		return false;
	}

	// checks to see if a player has a group of four, and deletes it from all records
	void check_for_group() override {
		sort_hand();
		for (size_t i = 0; i < hand.size(); ++i) {
			int count = 0;
			for (size_t j = 0; j < hand.size(); ++j) {
				if (hand[i].get_rank() == hand[j].get_rank()) {
					++count;
					if (count == 4) {
						cout << name << " got a group of four!" << endl;
						// deletes from card_age map
						map<string, int>::iterator it;
						if (card_age.find(hand[i].get_rank()) != card_age.end()) {
							it = card_age.find(hand[i].get_rank());
							card_age.erase(it);
						}
						// deletes from hand
						hand.erase(hand.begin() + i, hand.begin() + j + 1);
						++score; // add one to the player's score
					}
				}
			}
		}
	}

	// deletes all cards of a selected rank from the player's hand after recording them
	int give_cards(string rank) override {
		int count = 0;
		for (size_t i = 0; i < hand.size(); ++i) {
			if (hand[i].get_rank() == rank) {
				// record the cards being given
				cards_being_given.push_back(hand[i]);
				// delete the cards being given from this player's hand
				hand.erase(hand.begin() + i);
				--i;
				// deletes from card_age map
				map<string, int>::iterator it;
				if (card_age.find(rank) != card_age.end()) {
					it = card_age.find(rank);
					card_age.erase(it);
				}
				++count;
			}
		}
		return count;
	}

	// reciever functions that give the player a certain number of cards
	void receive_1card(const Card& card) override {
		hand.push_front(card);
		card_age[card.get_rank()] = 0;
	}
	void receive_2card(const Card& card1, const Card& card2) override {
		hand.push_front(card1);
		hand.push_front(card2);
		card_age[card1.get_rank()] = 0;
	}
	void receive_3card(const Card& card1, const Card& card2, const Card& card3) override {
		hand.push_front(card1);
		hand.push_front(card2);
		hand.push_front(card3);
		card_age[card1.get_rank()] = 0;
	}

	// sorts the player's hand
	void sort_hand() override {
		sort(hand.begin(), hand.end());
	}

	// increments the age of the cards in a player's hand by one
	void add_count() override {
		for (auto it = card_age.begin(); it != card_age.end(); ++it) {
			string rank = it->first;
			++card_age[rank];
		}
	}

private:
	// the player's name
	string name;
	// the player's score
	int score;
	// a deque holding the player's hand
	deque<Card> hand;
	// a vector holdig the current cards being given by a player
	vector<Card> cards_being_given;
	// a map matching each rank in a player's hand with its age
	map<string, int> card_age;
};

// creates a new player based on their type
Player* Player_factory(const string& name, const string& strategy) {
	if (strategy == "AI") {
		return new AI(name);
	}
	if (strategy == "Human") {
		return new Human(name);
	}
	assert(false);
	return nullptr;
}

// prints out a player by their name
std::ostream& operator<<(std::ostream& os, const Player& p) {
	os << p.get_name();
	return os;
}