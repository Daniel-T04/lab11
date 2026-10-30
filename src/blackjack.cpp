#include "blackjack.h"

#include <iostream>
#include <random>
#include <string>

#include "card.h"
#include "deck.h"
#include "hand.h"

namespace {

/// The first five cards of a deck as text. The deck is passed by value on
/// purpose: the copy is dealt from, and the caller's deck is left alone.


} // namespace

// TODO(student): Lab 11. Replace this demonstration with the game. Keep the
// Lab 10 helper above if it is useful; delete it if it is not (an unused
// function in an unnamed namespace is a compiler warning).
void play_blackjack() {
    std::random_device device{};
    std::mt19937 gen{device()};

    std::cout << "\n--- Blackjack ---\n";

    Deck deck;
    deck.shuffle(gen);

    int bankroll = 100;
    const int bet = 10;

    while (bankroll > 0) {
      std::cout << "\nBankroll: $" << bankroll << " | Current Bet: $" << bet << "\n";
        
        
        if (deck.remaining() < 15) {
            std::cout << "Reshuffling the deck...\n";
            deck = Deck();
            deck.shuffle(gen);
        }

        Hand player_hand;
        Hand dealer_hand;

    
        player_hand += deck.deal();
        dealer_hand += deck.deal();
        player_hand += deck.deal();
        dealer_hand += deck.deal();

       std::cout << "Dealer's upcard: " << dealer_hand[0] << " [Hidden]\n";
       std::cout << "Your hand: " << player_hand << " (Value: " << player_hand.value() << ")\n";

        
        if (player_hand.is_blackjack()) {
            if (dealer_hand.is_blackjack()) {
                std::cout << "Dealer also has Blackjack. Push!\n";
            } else {
                std::cout << "Blackjack! You win 3:2 payout.\n";
                bankroll += bet * 1.5;
            }
            continue;
        }

        
     bool player_busted = false;
     char choice = ' ';
     while (true) {
     std::cout << "Hit (h) or Stand (s)? ";
     std::cin >> choice;
     if (choice == 'h' || choice == 'H') {
         player_hand += deck.deal();
         std::cout << "Your hand: " << player_hand << " (Value: " << player_hand.value() << ")\n";
            if (player_hand.is_bust()) {
                std::cout << "Bust! You lose.\n";
                 player_busted = true;
                 bankroll -= bet;
                 break;
                }
            } else if (choice == 's' || choice == 'S') {
                break;
            }
        }

        if (player_busted) {
            if (bankroll <= 0) {
                std::cout << "Your bankroll is 0. Game over!\n";
               break;
            }
            std::cout << "Play another round? (y/n): ";
            char play_again;
            std::cin >> play_again;
            if (play_again == 'n' || play_again == 'N') {
                break;
            }
            continue;
        }

       
        std::cout << "Dealer's hand: " << dealer_hand << " (Value: " << dealer_hand.value() << ")\n";
        while (dealer_hand.value() < 17) {
            dealer_hand += deck.deal();
            std::cout << "Dealer hits: " << dealer_hand << " (Value: " << dealer_hand.value() << ")\n";
        }

        
        int player_val = player_hand.value();
        int dealer_val = dealer_hand.value();

        if (dealer_hand.is_bust()) {
            std::cout << "Dealer busts! You win $" << bet << ".\n";
            bankroll += bet;
        } else if (player_val > dealer_val) {
            std::cout << "You win $" << bet << "!\n";
            bankroll += bet;
        } else if (player_val < dealer_val) {
            std::cout << "Dealer wins. You lose $" << bet << ".\n";
            bankroll -= bet;
        } else {
            std::cout << "Push! Bet returned.\n";
        }

        if (bankroll <= 0) {
            std::cout << "Your bankroll has reached 0. Game over!\n";
            break;
        }

        std::cout << "Play another round? (y/n): ";
        char play_again;
        std::cin >> play_again;
        if (play_again == 'n' || play_again == 'N') {
            break;
        }
    }

    std::cout << "Thanks for playing! Final bankroll: $" << bankroll << "\n";
}
