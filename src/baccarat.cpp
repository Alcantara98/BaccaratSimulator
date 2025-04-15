#include "baccarat.h"
#include "casino_player.h"
#include <algorithm>
#include <cctype>

namespace BACCARAT
{
Baccarat::Baccarat() = default;

void Baccarat::state_machine()
{
  while (true)
  {
    // Call the current state function
    exit_state = false;
    (this->*current_state)();
  }
}

void Baccarat::update_game_state(StateType new_state)
{
  // Update the current state to the new state.
  current_state = new_state;
  exit_state = true;
}

void Baccarat::main_menu_state()
{
  printf("\n\n--- Welcome to the Baccarat game! ---\n\n");
  printf("Enter 'start' to play or 'help' for more options: ");

  while (!exit_state)
  {
    std::string input;
    std::cin >> input;

    if (input == "start")
    {
      update_game_state(&Baccarat::game_state);
      break;
    }
    if (handle_general_user_commands(input))
    {
      continue;
    }
  }
}

void Baccarat::game_state()
{
  printf("\n--- Starting a game of Baccarat! ---\n\n");
  printf("--------------------------------------\n\n");

  CasinoPlayer player = CasinoPlayer();

  std::string user_input;
  while (!exit_state)
  {
    // If we are handling player bets, print the current balance and ask for the
    // bet type and amount.
    if (!deal_cards_only)
    {
      printf("Your current balance is: $%.2f\n", player.check_balance());

      printf("Enter your bet type (PLAYER, BANKER, TIE) and amount (e.g., "
             "PLAYER-100): ");
    }

    if (deal_cards_only)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::getline(std::cin, user_input);
    }
    else
    {
      std::cin >> user_input;
    }

    if (handle_general_user_commands(user_input))
    {
      continue;
    }
    if (deal_cards_only && user_input.empty())
    {
      card_dealer.play_round(current_outcome);
      continue;
    }
    if (!deal_cards_only && handle_player_round(player, user_input))
    {
      continue;
    }
  }
}

auto Baccarat::handle_general_user_commands(const std::string &user_input)
    -> bool
{
  // Handle user input for exiting or changing game states.
  if (user_input == "exit")
  {
    printf("Exiting the game...\n");
    exit(0);
  }
  else if (user_input == "menu")
  {
    update_game_state(&Baccarat::main_menu_state);
    return true;
  }
  else if (user_input == "reset")
  {
    card_dealer.reset_deck();
    printf("Deck has been reset.\n");
    return true;
  }
  else if (user_input == "help")
  {
    printf("Available commands:\n  -start\n  -exit\n  -menu\n  -reset\n  "
           "-draw-counts\n  -help\n  -press 'enter' to deal cards\n");
    return true;
  }
  else if (user_input == "draw-counts")
  {
    card_dealer.print_drawn_card_counter();
    return true;
  }

  return false;
}

auto Baccarat::handle_player_round(CasinoPlayer &player,
                                   std::string &user_input) -> bool
{
  // NOTE: Use Regex here instead.

  std::string bet_type;
  std::string bet_amount_string;

  double bet_amount = 0.0;

  size_t pos = user_input.find('-');
  if (pos == std::string::npos)
  {
    printf("\nInvalid input format. Please enter in the format: BET_TYPE-BET "
           "AMOUNT\n\n");
    return false;
  }

  bet_type = user_input.substr(0, pos);
  bet_amount_string = user_input.substr(pos + 1);

  try
  {
    // Try to convert the bet amount to a double.
    bet_amount = std::stod(bet_amount_string);
  }
  catch (const std::invalid_argument &e)
  {
    printf("\nInvalid Bet\n\n");
    return false;
  }
  catch (const std::out_of_range &e)
  {
    printf("\nBet amount is out of range\n\n");
    return false;
  }

  if (bet_amount < 0.0)
  {
    printf("\nBet amount cannot be negative.\n\n");
    return false;
  }

  // Transform the bet type to uppercase.
  std::transform(bet_type.begin(), bet_type.end(), bet_type.begin(),
                 [](unsigned char bet_type_char)
                 { return std::toupper(bet_type_char); });

  if (bet_type == "PLAYER")
  {
    player.place_bet(BetType::PLAYER, bet_amount);
  }
  else if (bet_type == "BANKER")
  {
    player.place_bet(BetType::BANKER, bet_amount);
  }
  else if (bet_type == "TIE")
  {
    player.place_bet(BetType::TIE, bet_amount);
  }
  else
  {
    printf("\nInvalid Bet Type.\n\n");
    return false;
  }

  // Deal the cards and determine the outcome.
  card_dealer.play_round(current_outcome);
  BACCARAT::CardDealer::pay_out_bets(current_outcome, player);
  printf("\n--------------------------------------\n\n");
  return true;
}

} // namespace BACCARAT