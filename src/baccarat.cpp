#include "baccarat.h"

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
  printf("Enter 'start' to play or 'exit' to quit: ");

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
  printf("\nStarting a game of Baccarat!\n");
  printf("Simply press enter to deal cards... \n\n");

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (!exit_state)
  {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
    {
      card_dealer.play_round();
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
           "-enter to deal cards\n");
    return true;
  }
  else
  {
    printf("Invalid command. Type 'help' for available commands.\n");
    return false;
  }
}

} // namespace BACCARAT