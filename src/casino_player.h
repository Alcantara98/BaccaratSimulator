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
class CasinoPlayer {
public:
    CasinoPlayer();

    ~CasinoPlayer();

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
    double check_balance() const;

    /**
     * @brief Get the current bet type.
     *
     * @return The current bet type.
     */
    BetType get_current_bet_type() const;
    /**
     * @brief Get the current bet amount.
     *
     * @return The current bet amount.
     */
    double get_current_bet_amount() const;
    /**
     * @brief Add to the player's balance.
     *
     * @param amount The amount to add to the balance.
     */
    void add_to_balance(double amount);
    /**
     * @brief Subtract from the player's balance.
     *
     * @param amount The amount to subtract from the balance.
     */

private:
    double balance = 5000.0; // Starting balance for the player

    BetType current_bet_type = BetType::NONE; // Default bet type

    double current_bet_amount = 0.0;
};

} // namespace BACCARAT

#endif // CASINO_PLAYER_H