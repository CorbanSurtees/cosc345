
#include <iostream>
#include <string>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"
#include "GUI.hpp"


/**
 * Clear the terminal screen
 */
void GUI::clearScreen() {
    // Clear the screen
    std::cout << "\033[2J\033[1;1H";
}

/**
 * Get user move from the terminal
 */
string GUI::getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall) {
    // Get user move 
    // TODO: Test input validation

    // Create message to user based on possible actions
    // TODO: format nicely
    string message = "Enter your move: (";
    if (canFold) {
        message += "fold = f";
    }
    if (canCall) {
        message += ", call = c";
    }
    if (canCheck) {
        message += ", check = a";
    }
    if (canRaise) {
        message += ", raise = r";
    }
    message += ") ";


    std::string move; 
    std::cout << message;
    std::cin >> move; 
    while((move == "f" && !canFold) || 
          (move == "a" && !canCheck) || 
          (move == "c" && !canCall) || 
          (move == "r" && !canRaise) ||
          (move != "f" && move != "a" && move != "c" && move != "r")) {
        std::cout << "Invalid move. Please enter a valid move: ";
        std::cin >> move; 
    }

    return move; 
}

/**
 * Get user bet sizing from the terminal
 * 
 * @param minBet: int - Minimum bet size
 * @param maxBet: int - Maximum bet size
 */

int GUI::getBetSizing(int minBet, int maxBet) {
    // Get user bet size
    // TODO: Test bet sizing input validation
    int bet_sizing; 
    std::cout << "Enter your bet sizing: ";
    while (true) {
        std::cin >> bet_sizing;

        // Check if the input is valid
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a valid integer bet size: ";
            continue;
        }

        // Check if the bet is within the valid range
        if (bet_sizing >= minBet && bet_sizing <= maxBet) {
            break; // Valid bet size
        }

        std::cout << "Invalid bet size. Please enter a bet size between " << minBet << " and " << maxBet << ": ";
    }

    return bet_sizing;
}

/** 
 * Display community cards to the terminal
 * 
 * @param community_cards: vector<Card> - Community cards to display
 */
void GUI::displayCommunityCards(const std::vector<Card>& community_cards) {
    // Display community cards
    for (Card card : community_cards) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
}   

/** 
 * Display all player hands to the terminal
 * 
 * @param players: vector<Player*> - Players to display hands for
 */
void GUI::displayAllPlayerHands(const std::vector<Player*>& players) {
    for (Player* player : players) {
        std::cout << player->get_name() << "'s hand: " << std::endl;
        for (Card& card : player->get_hand()) {
            std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }
}

/** 
 * Display a player's hand to the terminal 
 * 
 * @param player: Player* - Player to display hand for
 */
void GUI::displayPlayerHand(Player* player) {
    std::cout << player->get_name() << "'s hand: " << std::endl;
    for (Card card : player->get_hand()) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
    std::cout << "--------------" << std::endl;
}

void GUI::displayStartScreen() {
    string title = R"(:::::::::  :::    ::: ::::    :::    ::::::::::: :::::::::::    ::::::::::: :::       ::: :::::::::::  ::::::::  :::::::::: 
:+:    :+: :+:    :+: :+:+:   :+:        :+:         :+:            :+:     :+:       :+:     :+:     :+:    :+: :+:        
+:+    +:+ +:+    +:+ :+:+:+  +:+        +:+         +:+            +:+     +:+       +:+     +:+     +:+        +:+        
+#++:++#:  +#+    +:+ +#+ +:+ +#+        +#+         +#+            +#+     +#+  +:+  +#+     +#+     +#+        +#++:++#   
+#+    +#+ +#+    +#+ +#+  +#+#+#        +#+         +#+            +#+     +#+ +#+#+ +#+     +#+     +#+        +#+        
#+#    #+# #+#    #+# #+#   #+#+#        #+#         #+#            #+#      #+#+# #+#+#      #+#     #+#    #+# #+#        
###    ###  ########  ###    ####    ###########     ###            ###       ###   ###   ###########  ########  ########## )";
    std::cout << title << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

int GUI::displayMenu() {
    std::cout << "1. Start Game (press Enter)" << std::endl;
    std::cout << "2. Quit (q)" << std::endl;

    std::string input;
    std::getline(std::cin, input);  // Read the entire line, allowing us to detect Enter

    while (input != "q" && input != "") {
        std::cout << "Invalid input. Please enter a valid option: ";
        std::getline(std::cin, input);  // Use getline to capture the next input
    }

    if (input == "q") {
        return 0;
    }
    return 1;
}


void GUI::displayPlayerStack(Player* player) {
    std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    std::cout << "    -----    " << std::endl;
}

void GUI::displayPot(int pot) {
    std::cout << "Pot: " << pot << std::endl;
    std::cout << "    -----    " << std::endl;
}