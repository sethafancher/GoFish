// go_fish.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "cards_pack.h"
#include "players.h"
#include <cassert>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

// exception object for player chososing another invalid player
class PlayerSelectionError{};

// ADT COVERING ALL GAME FUNCTIONALITY 
class GameADT {
public:

// ctor; intializes players, score, and pack
GameADT(char* argv[], int argc)
: scores(), pack() {
	for (int i = 1; i < argc; i = i + 2) {
		if (strcmp(argv[i + 1], "Human") == 0) {
			string name = argv[i];
			player_vec.push_back(Player_factory(name, "Human"));
			player_map[name] = "Human";
			name_vec.push_back(name);
		}
		else {
			string name = argv[i];
			player_vec.push_back(Player_factory(name, "AI"));
			player_map[name] = "AI";
			name_vec.push_back(name);
		}
	}
}

// shuffles the pack and deals five cards to each player
void game_setup() {
	pack.shuffle_pack();
	for (size_t i = 0; i < player_vec.size(); ++i) {
		for (int j = 0; j < 5; ++j) {
			player_vec[i]->receive_1card(pack.pick_one());
		}
	}
}

// prints the players' names in a readable format
void print_players(int current_player) {
	if (current_player == 0) {
		for (size_t i = 1; i < player_vec.size(); ++i) {
			cout << "Player: " << player_vec[i]->get_name() << " [" << i << "] " << endl;
		}
	}
	else if (current_player == 1) {
		for (size_t i = 2; i < player_vec.size(); ++i) {
			cout << "Player: " << player_vec[i]->get_name() << " [" << i << "] " << endl;
		}
		cout << "Player: " << player_vec[0]->get_name() << " [" << 0 << "] " << endl;
	}
	else if (current_player == 2) {
		for (size_t i = 3; i < player_vec.size(); ++i) {
			cout << "Player: " << player_vec[i]->get_name() << " [" << i << "] " << endl;
		}
		cout << "Player: " << player_vec[0]->get_name() << " [" << 0 << "] " << endl;
		cout << "Player: " << player_vec[1]->get_name() << " [" << 1 << "] " << endl;
	}
	if (current_player == 3) {
		cout << "Player: " << player_vec[0]->get_name() << " [" << 0 << "] " << endl;
		cout << "Player: " << player_vec[1]->get_name() << " [" << 1 << "] " << endl;
		cout << "Player: " << player_vec[2]->get_name() << " [" << 2 << "] " << endl;
	}
}

// prints the cards in a readable format
void print_cards_being_given(string player, vector<Card> cards_being_given, string player2) {
	cout << player << " gives their ";
	for (size_t i = 0; i < cards_being_given.size(); ++i) {
		cout << cards_being_given[i] << ", ";
	}
	cout << "to " << player2 << endl;
}

// plays a single player's turn
bool turn(int current_player) {
	// intialize variables
	int count;
	Card card;
	size_t player_index = 0;
	// separate turns with a line
	cout << "----------------------------------------------" << endl;
	// print out the current player and let them know it's their turn
	cout << player_vec[current_player]->get_name() << "'s Turn" << endl;
	// if the player's hand is empty, draw a card from the deck
	if (player_vec[current_player]->empty()) {
		player_vec[current_player]->receive_1card(pack.pick_one());
	}
	// call the make_card_query function, allowing the player to choose a card
	if (player_map[player_vec[current_player]->get_name()] == "Human") {
		card = player_vec[current_player]->make_card_query();
		print_players(current_player);
	}
	else {
		card = player_vec[current_player]->make_card_queryAI(card_requests);
		player_vec[current_player]->add_count();
	}

	// make sure that the player chose another valid player
	try {

		// update each player's hand size

		// call the make_player_query function, allowing the player to choose a player
		if (player_map[player_vec[current_player]->get_name()] == "Human") {
			player_index = player_vec[current_player]->make_player_query();
		}
		else {
			player_index = player_vec[current_player]->make_player_queryAI(card_requests, name_vec);
		}
		// throw the exception if needed
		if ((player_index == current_player) || (player_index > player_vec.size() - 1) || (player_index < 0)) {
			throw PlayerSelectionError();
		}
		// print out the player's choices
		if (card.get_rank() == "Six") { // "Six" has a different form of plural than other numbers
			cout << player_vec[current_player]->get_name() << " asks " << player_vec[player_index]->get_name() << " if they have any " << card.get_rank() << "es" << endl;
		}
		else {
			cout << player_vec[current_player]->get_name() << " asks " << player_vec[player_index]->get_name() << " if they have any " << card.get_rank() << "s" << endl;
		}
		// update the info in the card_requessts map with the player's choices
		card_requests[card.get_rank()] = player_vec[current_player]->get_name();
		// check to see if the requested player has the requested card
		if (player_vec[player_index]->has_req_card(card.get_rank())) {
			// if they do, see how many of those cards they have, while taking them from their deck
			count = player_vec[player_index]->give_cards(card.get_rank());
			// retrieve the cards being given from the requested player
			vector<Card> cards_being_given = player_vec[player_index]->get_cards_being_given();
			// print out the cards that are being taken from the requested player
			cout << player_vec[player_index]->get_name() << " has the requested card, and ";
			print_cards_being_given(player_vec[player_index]->get_name(), cards_being_given, player_vec[current_player]->get_name());
			// run the retrieving function needded for the matching amount of cards
			if (count == 1) {
				player_vec[current_player]->receive_1card(cards_being_given[0]);
			}
			else if (count == 2) {
				player_vec[current_player]->receive_2card(cards_being_given[0], cards_being_given[1]);
			}
			else {
				player_vec[current_player]->receive_3card(cards_being_given[0], cards_being_given[1], cards_being_given[2]);
			}
		}
		// if the requested player doesn't have the requested card, make the current player draw from the deck
		else {
			cout << player_vec[player_index]->get_name() << " does not have the requested card" << endl;
			cout << player_vec[current_player]->get_name() << " goes fishing..." << endl;
			if (!pack.empty_pack()) {
				player_vec[current_player]->receive_1card(pack.pick_one());
			}
		}
		// at the end of the turn, see if the current player has a group of four
		player_vec[current_player]->check_for_group();
	}

	// catch the exception if needed
	catch (const PlayerSelectionError& error) {
		cout << "ERROR: MUST CHOOSE A PLAYER FROM THE GIVEN LIST USING ITS ASSIGNED NUMBER. TURN ENDED AS PENALTY." << endl;
	}
	// print out a turn separation line
	cout << endl;

	// check if the game is ready to be ended or not
	if (pack.empty_pack() && game_end()) {
		return false; // ends the game
	}
	// allows the game to continue
	return true;
}

// plays the game
void game_player() {
	// run the game setup
	game_setup();
	// while the pack isn't empty, and the max score isn't reached, run the game
	bool max_score = true;
	while (max_score == true) {
		for (size_t i = 0; i < player_vec.size(); ++i) {
			if (max_score == true) {
				max_score = turn(i);
			}
		}
	}
	// retrieve the scores for each player
	for (size_t i = 0; i < player_vec.size(); ++i) {
		scores.push_back(player_vec[i]->get_score());
	}
	// run a maximum algorithm to find the max out of the player's scores
	int max = scores[0];
	int winning_player = 0;
	for (size_t i = 0; i < scores.size(); ++i) {
		if (scores[i] > max) {
			max = scores[i];
			winning_player = i;
		}
	}
	// print out the final game information
	cout << "The deck is empty" << endl;
	cout << "GAME OVER" << endl;
	cout << player_vec[winning_player]->get_name() << " won the game with a total of " << max << " groups of four! Congratulations!" << endl;
}

// checks if the game should end by seeing if the sum of scores is 13
bool game_end() {
	int total_score = 0;
	// add all of the scores together
	for (size_t i = 0; i < player_vec.size(); ++i) {
		total_score += player_vec[i]->get_score();
	}
	// if the total is 13, return true
	if (total_score == 13) {
		return true;
	}
	// otherwise, return false
	return false;
}

// deletes the players off of the heap
void player_deleter() {
	for (size_t i = 0; i < player_vec.size(); ++i) {
		delete player_vec[i];
	}
}

private:
	// vector holding all player scores
	vector<int> scores;
	// pack of cards
	Pack pack;
	// map matching players with their corresponding type
	map <string, string> player_map;
	// vector holding all players
	vector<Player*> player_vec;
	// vector holding all player names
	vector<string> name_vec;
	// map matching all card rnak requests with the player who most recently asked for them
		// useful for AI algorithm
	map<string, string> card_requests;
};

// checks the user inputted executable to make sure its valid for the game
bool check_input(int argc, char* argv[]) {
	// make sure there are 2-4 players
	if (!(argc == 9) && !(argc == 7) && !(argc == 5)) {
		return false;
	}
	// make sure the players are either human or AI
	if (argc == 9 &&
			(!((strcmp(argv[8], "AI")) || (strcmp(argv[8], "Human"))) ||
			!((strcmp(argv[6], "AI")) || (strcmp(argv[6], "Human"))) ||
			!((strcmp(argv[4], "AI")) || (strcmp(argv[4], "Human"))) ||
			!((strcmp(argv[2], "AI")) || (strcmp(argv[2], "Human"))))) {
		return false;
	}
	if (argc == 7 &&
		(!((strcmp(argv[6], "AI")) || (strcmp(argv[6], "Human"))) ||
			!((strcmp(argv[4], "AI")) || (strcmp(argv[4], "Human"))) ||
			!((strcmp(argv[2], "AI")) || (strcmp(argv[2], "Human"))))) {
		return false;
	}
	if (argc == 5 &&
		(!((strcmp(argv[4], "AI")) || (strcmp(argv[4], "Human"))) ||
			!((strcmp(argv[2], "AI")) || (strcmp(argv[2], "Human"))))) {
		return false;
	}
	else {
		return true;
	}
}

// prints the user inputted executable
void print_user_executeable(int argc, char* argv[]) {
	cout << "----------------------------------------------------------------" << endl;
	cout << "Welcome to Go Fish!" << endl;
	cout << endl;
	cout << "User's executable: " << endl;
	for (int i = 0; i < argc; ++i) {
		cout << argv[i] << " ";
	}
	cout << endl;
	cout << endl;
}

// MAIN FUNCTION
int main(int argc, char* argv[]) {
	// check inputs
	if (!check_input(argc, argv)) {
		cout << "ERROR: INCORRECT USAGE" << endl;
		cout << "CORRECT USAGE: go_fish.exe NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4" << endl;
		return -1;
	}
	// print executable
	print_user_executeable(argc, argv);
	// create a game object
	GameADT game(argv, argc);
	// run the game
	game.game_player();
	// delete the players
	game.player_deleter();
	return 0;
}