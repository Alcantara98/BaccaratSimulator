#include "baccarat.h"
#include "casino_player.h"
#include <cctype>
#include <algorithm>

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
    if (handle_player_input(input))
    {
      continue;
    }
  }
}

void Baccarat::game_state()
{
  printf("\n--- Starting a game of Baccarat! ---\n\n");

  CasinoPlayer* player = new CasinoPlayer();

  while (!exit_state)
  {
    printf("Your current balance is: $%.2f\n", player->check_balance());

    printf("Enter your bet type (PLAYER, BANKER, TIE) and amount (e.g., PLAYER 100): ");

    std::string bet_type;
    double bet_amount = 0.0;

    std::cin >> bet_type >> bet_amount;

    std::transform(bet_type.begin(), bet_type.end(), bet_type.begin(),
                   [](unsigned char c) { return std::toupper(c); });

    if (bet_type == "PLAYER")
    {
      player->place_bet(BetType::PLAYER, bet_amount);
    }
    else if (bet_type == "BANKER")
    {
      player->place_bet(BetType::BANKER, bet_amount);
    }
    else if (bet_type == "TIE")
    {
      player->place_bet(BetType::TIE, bet_amount);
    }
    else
    {
      printf("Invalid bet type. Do you wish to continue? (yes/no)\n");
      std::string response;
      std::cin >> response;
      if (response == "no")
      {
        update_game_state(&Baccarat::main_menu_state);
        break;
      }
      else if (response == "yes")
      {
        continue;
      }
      else
      {
        printf("Invalid response. Exiting...\n");
        exit(0);
      }
    }

    printf("Press 'enter' to deal cards...\n");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
    {
      card_dealer.play_round(current_outcome);
      card_dealer.pay_out_bets(current_outcome, player);
    }
    else if (handle_player_input(input))
    {
      continue;
    }
  }
}

auto Baccarat::handle_player_input(const std::string &user_input) -> bool
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
  else
  {
    printf("Invalid command. Type 'help' for available commands.\n");
    return false;
  }
}

} // namespace BACCARAT