#include "casino_player.h"
#include <cstdio>

namespace BACCARAT
{

CasinoPlayer::CasinoPlayer()
{
}

CasinoPlayer::~CasinoPlayer()
{
}

void CasinoPlayer::place_bet(BetType bet_type, double amount)
{
    if (amount > balance)
    {
        printf("Insufficient balance to place the bet. Balance: %.2f\n", balance);
        return;
    }

    current_bet_type = bet_type;
    current_bet_amount = amount;
    balance -= amount;

    printf("Bet placed: %s %.2f\n\n", bet_type == BetType::PLAYER ? "Player" :
                                      bet_type == BetType::BANKER ? "Banker" : "Tie",
           amount);
}

double CasinoPlayer::check_balance() const
{
    return balance;
}

BetType CasinoPlayer::get_current_bet_type() const
{
    return current_bet_type;
}

double CasinoPlayer::get_current_bet_amount() const
{
    return current_bet_amount;
}

void CasinoPlayer::add_to_balance(double amount)
{
    balance += amount;
    printf("Balance updated: %.2f\n\n", balance);
}

} // namespace BACCARAT