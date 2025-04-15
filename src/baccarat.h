#ifndef BACCARAT_H
#define BACCARAT_H

#include "card_dealer.h"
#include "bet_type.h"

namespace BACCARAT
{

/**
 * @brief A class to simulate a game of Baccarat.
 *
 * @details The Baccarat class handles player inputs, and uses CardDealer to
 * simulate the dealing of cards for a game of Baccarat.
 *
 * @note The class does not manage the game logic or player interactions. This
 * simply allows players to play the game without needing a deck of cards or
 * a dealer.
 *
 * @note See 'https://en.wikipedia.org/wiki/Baccarat' for more
 * information about the rules of Baccarat.
 */
class Baccarat
{

public:
  /**
   * @brief Default Constructor for the Baccarat class.
   */
  Baccarat();

  /**
   * @brief Runs the current state of the game.
   */
  void state_machine();

private:
  /// @brief  The type for the state pointer for this class.
  using StateType = void (Baccarat::*)();

  /// @brief The current state of the game.
  StateType current_state = &Baccarat::main_menu_state;

  bool exit_state = false;

  /// @brief The CardDealer object to handle card dealing.
  CardDealer card_dealer;

  BetType current_outcome = BetType::NONE;

  /**
   * @brief Updates the game state.
   *
   * @param new_state The new state function to transition to.
   */
  void update_game_state(StateType new_state);

  /**
   * @brief Main menu state. This is the entry point of the game.
   */
  void main_menu_state();

  /**
   * @brief Game state, where the player can play the game.
   */
  void game_state();

  /**
   * @brief Handles user input for exiting or changing game states.
   *
   * @param user_input The string input provided by the user.
   *
   * @return bool true if the user input is valid, false otherwise.
   */
  auto handle_player_input(const std::string &user_input) -> bool;
};
} // namespace BACCARAT

#endif // BACCARAT_H