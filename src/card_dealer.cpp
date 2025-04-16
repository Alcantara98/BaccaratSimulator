#include "card_dealer.h"

namespace BACCARAT
{

// CONSTRUCTORS

CardDealer::CardDealer() { reset_deck(); }

// PUBLIC METHODS

void CardDealer::play_round(BetType &outcome)
{
  std::string player_cards;
  std::string banker_cards;

  int player_hand_value = 0;
  int banker_hand_value = 0;

  // Deal the cards to the player and banker.
  deal_player_and_banker_cards(player_cards, banker_cards, player_hand_value,
                               banker_hand_value);

  // Determine the winner.
  std::string winner_message;
  if (player_hand_value > banker_hand_value)
  {
    winner_message = "Player wins!";
    outcome = BetType::PLAYER;
  }
  else if (banker_hand_value > player_hand_value)
  {
    winner_message = "Banker wins!";
    outcome = BetType::BANKER;
  }
  else
  {
    winner_message = "It's a tie!";
    outcome = BetType::TIE;
  }

  // Print the cards and the winner.
  printf("Player Cards: %s\nBanker Cards: %s\n%s\n", player_cards.c_str(),
         banker_cards.c_str(), winner_message.c_str());
}

void CardDealer::deal_player_and_banker_cards(std::string &player_cards,
                                              std::string &banker_cards,
                                              int &player_hand_value,
                                              int &banker_hand_value)
{
  // Deal the two cards to the player
  deal_a_card(player_cards, player_hand_value);
  deal_a_card(player_cards, player_hand_value);

  // Deal the two cards to the banker
  deal_a_card(banker_cards, banker_hand_value);
  deal_a_card(banker_cards, banker_hand_value);

  // Check if either player or banker has a natural hand (8 or 9). If so, no
  // more cards are to be drawn.
  if (CardDealer::player_or_banker_has_natural_hand(player_hand_value,
                                                    banker_hand_value))
  {
    return;
  }

  // Is used to determine if the banker can draw a third card. A value of -1
  // indicates that the player did not draw a third card.
  int player_third_card = -1;

  // Check if the player can draw a third card
  if (player_hand_value <= THRESHOLD_FOR_THIRD_CARD)
  {
    player_third_card = deal_a_card(player_cards, player_hand_value);
  }

  // Check if the banker can draw a third card
  if (banker_can_draw_third_card(banker_hand_value, player_third_card))
  {
    deal_a_card(banker_cards, banker_hand_value);
  }
}

void CardDealer::reset_deck()
{
  drawn_card_counter.fill(0);
  total_cards_drawn = 0;

  // Initialize the random number generator with a new random seed
  // using std::random_device
  std::random_device my_random_device;
  gen = std::mt19937(my_random_device());
}

void CardDealer::print_drawn_card_counter()
{
  printf("\nDrawn Card Counter:\n");
  for (int i = 0; i < NUM_OF_UNIQUE_CARDS; ++i)
  {
    printf("%s: %d\n", get_string_card_type(i).c_str(), drawn_card_counter[i]);
  }
  printf("\n");
}

// PRIVATE METHODS

auto CardDealer::deal_a_card(std::string &cards, int &hand_value) -> int
{
  int card_type = draw_card();
  if (!cards.empty())
  {
    cards += ",";
  }
  cards += get_string_card_type(card_type);

  // Hand value is the last digit of the sum of the card values.
  // This is to ensure that the hand value is between 0 and 9.
  hand_value = (hand_value + CARD_VALUES[card_type]) % HAND_VALUE_MODULO;

  return card_type;
}

auto CardDealer::banker_can_draw_third_card(int banker_hand_value,
                                            int player_third_card) -> bool
{
  // If player_third_card is -1, it means the player did not draw a third card.
  if (player_third_card < 0)
  {
    // If the player did not draw a third card and the banker has a hand value
    // of 5 or less, the banker can draw a third card.
    return banker_hand_value <= THRESHOLD_FOR_THIRD_CARD;
  }

  // If the player drew a third card, check the BANKER_STAND_OR_HAND table to
  // determine if the banker can draw a third card.
  return BANKER_STAND_OR_HAND[banker_hand_value]
                             [CARD_VALUES[player_third_card]];
}

auto CardDealer::player_or_banker_has_natural_hand(
    const int &player_hand_value, const int &banker_hand_value) -> bool
{
  // Check if either player or banker has a natural hand (8 or 9).
  return (
      player_hand_value == NATURAL_EIGHT || player_hand_value == NATURAL_NINE ||
      banker_hand_value == NATURAL_EIGHT || banker_hand_value == NATURAL_NINE);
}

auto CardDealer::draw_card() -> int
{
  if (total_cards_drawn >= TOTAL_CARDS_IN_DECK)
  {
    // There are no more cards left to draw.
    printf(
        "All cards have been drawn from the deck. Resetting the deck...\n\n");
    reset_deck();
  }

  // Draw a random number to represent the card type
  // The range is from 0 to 12 (13 unique cards)
  int card_type = dist(gen);

  // This is to prevent an infinite loop.
  int number_of_cards_checked = 0;

  // Check if the card has already been drawn 32 times
  // If so, increment the random number until a valid card is found.
  while (number_of_cards_checked < NUM_OF_UNIQUE_CARDS)
  {
    if (drawn_card_counter[card_type] < MAX_DRAWS_PER_CARD)
    {
      ++total_cards_drawn;
      ++drawn_card_counter[card_type];
      return card_type;
    }
    card_type = (card_type + 1) % NUM_OF_UNIQUE_CARDS;
    number_of_cards_checked++;
  }

  // NOTE: Unreachable code. If there are no cards left to draw, we shouldn't
  // have reached this point.
  BREAKPOINT;
  return -1;
}

auto CardDealer::get_string_card_type(const int &card_type) -> std::string
{
  static const std::array<std::string, 13> INT_TO_STRING_CARD_TYPE_MAP = {
      "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

  return INT_TO_STRING_CARD_TYPE_MAP[card_type];
}

void CardDealer::pay_out_bets(const BetType &outcome, CasinoPlayer &player)
{
  if (player.get_current_bet_type() == BetType::NONE)
  {
    printf("\nNo bet placed.\n");
    return;
  }

  if (player.get_current_bet_type() != outcome)
  {
    printf("\nBet lost. No payout.\n");
    return;
  }

  switch (outcome)
  {
  case BetType::PLAYER:
    if (player.get_current_bet_amount() > 0)
    {
      // Player wins, payout is 1:1
      // Player's bet amount is added to the balance
      player.add_to_balance(player.get_current_bet_amount() *
                            (PAYOUT_PLAYER + 1));
    }
    break;
  case BetType::BANKER:
    if (player.get_current_bet_amount() > 0)
    {
      // Banker wins, payout is 1:1 - 5% commission
      // Player's bet amount is added to the balance
      player.add_to_balance(player.get_current_bet_amount() *
                            (PAYOUT_BANKER - PAYOUT_BANKER_COMMISSION + 1));
    }
    break;
  case BetType::TIE:
    if (player.get_current_bet_amount() > 0)
    {
      // Tie wins, payout is 8:1
      // Player's bet amount is added to the balance
      player.add_to_balance(player.get_current_bet_amount() * (PAYOUT_TIE + 1));
    }
    break;
  default:
    // Invalid bet type, unreachable code.
    BREAKPOINT;
    break;
  }
}

} // namespace BACCARAT