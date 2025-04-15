#ifndef CASINO_PLAYER_H
#define CASINO_PLAYER_H

#include "bet_type.h"

namespace BACCARAT
{

/**
 * @brief A class to represent a casino player in a game of Baccarat.
 *
 * @details The CasinoPlayer class handles the player's balance and betting
 * actions.
 */
class CasinoPlayer
{
public:
  CasinoPlayer();

  ~CasinoPlayer() = default;

  /**
   * @brief Place a bet on the game.
   *
   * @param bet_type The type of bet to place (PLAYER, BANKER, TIE).
   * @param amount The amount to bet.
   */
  void place_bet(BetType bet_type, double amount);

  /**
   * @brief Check the player's balance.
   *
   * @return The current balance of the player.
   */
  [[nodiscard]] auto check_balance() const -> double;

  /**
   * @brief Get the current bet type.
   *
   * @return The current bet type.
   */
  [[nodiscard]] auto get_current_bet_type() const -> BetType;

  /**
   * @brief Get the current bet amount.
   *
   * @return The current bet amount.
   */
  [[nodiscard]] auto get_current_bet_amount() const -> double;

  /**
   * @brief Add to the player's balance.
   *
   * @param amount The amount to add to the balance.
   */
  void add_to_balance(double amount);

private:
  /// @brief The starting balance for the player.
  static constexpr double STARTING_BALANCE = 5000.0;

  /// @brief Balance of the player.
  double balance = STARTING_BALANCE;

  /// @brief The current bet type placed by the player.
  /// @note Default is NONE.
  BetType current_bet_type = BetType::NONE;

  /// @brief The current bet amount placed by the player.
  /// @note Default is 0.0.
  double current_bet_amount = 0.0;
};

} // namespace BACCARAT

#endif // CASINO_PLAYER_H