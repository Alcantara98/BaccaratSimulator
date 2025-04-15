#ifndef CARD_DEALER_H
#define CARD_DEALER_H

/// @brief Macro to print a breakpoint message for debugging purposes.
#define BREAKPOINT                                                             \
  {                                                                            \
    std::cerr << "BREAKPOINT at " << __FILE__ << ":" << __LINE__ << " in "     \
              << __func__ << "\n";                                             \
  }

#include <array>
#include <iostream>
#include <random>
#include <string>
#include "bet_type.h"
#include "casino_player.h"

namespace BACCARAT
{
/**
 * @brief A class to simulate the dealing of cards in a game of Baccarat.
 *
 * @details The Baccarat class handles the initialization and dealing of cards
 * for a game of Baccarat.
 *
 * @remarks The class simulates the game with 8 decks of cards for a true
 * Baccarat experience.
 *
 * @note See 'https://en.wikipedia.org/wiki/Baccarat' for more
 * information about the rules of Baccarat.
 */
class CardDealer
{
public:
  /**
   * @brief Default Constructor for the CardDealer class.
   */
  CardDealer();

  /**
   * @brief Handles a round of Baccarat.
   *
   * @details This function simulates dealing cards from the deck using
   * Baccarat rules. It prints the cards dealt to the console.
   * Example:
   *
   * Player Cards: Q,3
   * Banker Cards: 6,3
   * Banker Wins!
   *
   */
  void play_round(BetType& outcome);

  /**
   * @brief Deals cards to the player and banker.
   *
   * @param player_cards The cards dealt to the player.
   * @param banker_cards The cards dealt to the banker.
   * @param player_hand_value The value of the player's hand.
   * @param banker_hand_value The value of the banker's hand.
   */
  void deal_player_and_banker_cards(std::string &player_cards,
                                    std::string &banker_cards,
                                    int &player_hand_value,
                                    int &banker_hand_value);

  /**
   * @brief Resets the deck of cards when all cards have been drawn.
   *
   * @details This function resets the drawn_card_counter array to zero,
   * effectively resetting the deck of cards.
   */
  void reset_deck();

  /**
   * @brief Prints the drawn card counter.
   *
   * @details This function prints the number of times each card has been
   * drawn from the deck.
   *
   * @note This function is used for debugging purposes (or for cheating).
   */
  void print_drawn_card_counter();

  /**
   * @brief Pays out the bets to the player.
   *
   * @details This function simulates paying out the bets to the player based on
   * the outcome of the game.
   *
   * @param player The player to pay out the bets to.
   */
  void pay_out_bets(const BetType& outcome, CasinoPlayer* player);

private:
  /// @brief The number of unique cards in a standard deck used in Baccarat.
  static constexpr int NUM_OF_UNIQUE_CARDS = 13;

  /// @brief The maximum number of times a card can be drawn from the deck.
  /// @note Baccarat uses 8 decks of cards, each deck has 4 cards of each type,
  /// hence the maximum number of times a card can be drawn is 32 (8 x 4).
  static constexpr int MAX_DRAWS_PER_CARD = 32;

  /// @brief The number of unique cards in a standard deck used in Baccarat.
  /// @details There are 8 decks of cards, each deck has 52 cards, hence the
  /// total number of cards in a deck is 416 (8 x 52).
  static constexpr int TOTAL_CARDS_IN_DECK = 416;

  /// @brief The maximum number of cards that can be drawn from the deck for the
  /// player and banker.
  static constexpr int MAX_CARDS_DRAWN = 3;

  /// @brief Player can only draw a third card if the value of the first two
  /// cards is equal or less than 5.
  static constexpr int THRESHOLD_FOR_THIRD_CARD = 5;

  /// @brief Natural 8 is the second highest possible hand value in Baccarat.
  /// @note If either the player or banker has a natural hand value, no more
  /// cards are drawn.
  static constexpr int NATURAL_EIGHT = 8;

  /// @brief Natural 9 is the highest possible hand value in Baccarat.
  /// @note If either the player or banker has a natural hand value, no more
  /// cards are drawn.
  static constexpr int NATURAL_NINE = 9;

  /// @brief When the player has 3 cards, this table is used to determine if the
  /// banker should draw a third card. Index one is the value of the banker's
  /// first two cards and the second index is the value of the player's third
  /// card.
  static constexpr std::array<std::array<bool, 10>, 8> BANKER_STAND_OR_HAND = {
      {{true, true, true, true, true, true, true, true, true, true},
       {true, true, true, true, true, true, true, true, true, true},
       {true, true, true, true, true, true, true, true, true, true},
       {true, true, true, true, true, true, true, true, false, true},
       {false, false, true, true, true, true, true, true, false, false},
       {false, false, false, false, true, true, true, true, false, false},
       {false, false, false, false, false, false, true, true, false, false},
       {false, false, false, false, false, false, false, false, false, false}}};

  /// @brief The values of the cards in a standard deck used in Baccarat.
  /// @note The index represents the card type. See get_string_card_type method
  /// for more information.
  static constexpr std::array<int, 13> CARD_VALUES = {1, 2, 3, 4, 5, 6, 7,
                                                      8, 9, 0, 0, 0, 0};

  static constexpr double PAYOUT_TIE = 8.0; // Payout for a tie bet

  static constexpr double PAYOUT_BANKER = 1.0; // Payout for a banker bet

  static constexpr double PAYOUT_PLAYER = 1.0; // Payout for a player bet

  static constexpr double PAYOUT_BANKER_COMMISSION = 0.05; // Commission for banker

  /// @brief Keeps track of how many times each card has been drawn.
  /// @note Each card can be drawn a maximum of 32 times (4 decks of 8 cards).
  /// @note The index represents the card type. See get_string_card_type method
  /// for more information.
  std::array<int, NUM_OF_UNIQUE_CARDS> drawn_card_counter = {};

  /// @brief The number of cards drawn from the deck.
  int total_cards_drawn = 0;

  /// @brief Random number generator for drawing cards.
  std::mt19937 gen;

  /// @brief Random number distribution for drawing cards.
  /// @note The range is from 0 to NUM_OF_UNIQUE_CARDS - 1.
  std::uniform_int_distribution<> dist =
      std::uniform_int_distribution<>(0, NUM_OF_UNIQUE_CARDS - 1);

  /**
   * @brief Deals player cards.
   *
   * @details This function simulates dealing cards to the player or banker and
   * will update the cards and hand value.
   *
   * @param cards The cards dealt to either the player or banker.
   * @param hand_value The value of the hand of either the player or banker.
   *
   * @return The card type dealt.
   */
  auto deal_a_card(std::string &cards, int &hand_value) -> int;

  /**
   * @brief Determines if the banker can draw a third card.
   *
   * @param banker_hand_value The value of the banker's hand.
   * @param player_third_card The value of the player's third card.
   *
   * @return true if the banker can draw a third card, false otherwise.
   */
  static auto banker_can_draw_third_card(int banker_hand_value,
                                         int player_third_card) -> bool;

  /**
   * @brief Determines if the player or banker has a natural hand.
   *
   * @param player_hand_value The value of the player's hand.
   * @param banker_hand_value The value of the banker's hand.
   *
   * @return true if either the player or banker has a natural hand, false
   * otherwise.
   */
  static auto
  player_or_banker_has_natural_hand(const int &player_hand_value,
                                    const int &banker_hand_value) -> bool;

  /**
   * @brief Draws a card from the deck.
   *
   * @details This function simulates drawing a card from the deck using random
   * number generation.
   *
   * @return The card drawn from the deck. The card type is represented by an
   * int, see get_string_card_type method for more information.
   *
   * @note Returns -1 if there are no cards left to draw.
   */
  auto draw_card() -> int;

  /**
   * @brief Converts the card type to a string.
   *
   * @details This function maps an int to a string representation of the card.
   *
   * @example 0 is "A", 1 is "2", 2 is "3", ..., 9 is "10", 10 is "J",
   * 11 is "Q", and 12 is "K".
   *
   * @param card_type The card type to convert.
   *
   * @return The string representation of the card type.
   */
  static auto get_string_card_type(const int &card_type) -> std::string;
};
} // namespace BACCARAT

#endif // CARD_DEALER_H