#ifndef PLAYERS_H
#define PLAYERS_H
#include <string>
#include "cards.h"
#include <vector>
#include <map>
using namespace std;

class Player {
public:
	// getters
	virtual const int& get_score() const = 0;
	virtual const string& get_name() const = 0;
	// checks if a player has a group of four
	virtual void check_for_group() = 0;
	// retrieves the cards being given by a player
	virtual vector<Card> get_cards_being_given() = 0;
	// checks if a player's hand is empty
	virtual bool empty() = 0;
	// checks what card a player wants to play
	virtual Card make_card_query() = 0;
	virtual Card make_card_queryAI(map<string, string> card_requests) = 0;
	// checks what player a player wants to request cards from
	virtual int make_player_query() = 0;
	virtual int make_player_queryAI(map<string, string> card_requests, vector<string> name_vec) = 0;
	// checks if the requested player has the requested rank
	virtual bool has_req_card(string rank) = 0;
	// deletes all cards in a rank from a player's hand, effectivley "giving" them away
	virtual int give_cards(string rank) = 0;
	// reciever functions to recieve cards from a player
	virtual void receive_1card(const Card &card) = 0;
	virtual void receive_2card(const Card &card1, const Card &card2) = 0;
	virtual void receive_3card(const Card &card1, const Card &card2, const Card &card3) = 0;
	// sorts hand
	virtual void sort_hand() = 0;
	// increments the age of the cards in a player's hand by one
	virtual void add_count() = 0;
	virtual ~Player() {}
};

// constructs new players
Player * Player_factory(const string& name, const string& type);

#endif