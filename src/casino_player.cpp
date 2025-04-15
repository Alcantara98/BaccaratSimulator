#include "casino_player.h"
#include <cstdio>

namespace BACCARAT
{

CasinoPlayer::CasinoPlayer() = default;

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

  printf("Bet placed: %s %.2f\n\n", get_string_bet_type(bet_type).c_str(),
         amount);
}

auto CasinoPlayer::check_balance() const -> double { return balance; }

auto CasinoPlayer::get_current_bet_type() const -> BetType
{
  return current_bet_type;
}

auto CasinoPlayer::get_current_bet_amount() const -> double
{
  return current_bet_amount;
}

void CasinoPlayer::add_to_balance(double amount)
{
  balance += amount;
  printf("Balance updated: %.2f\n\n", balance);
}

} // namespace BACCARAT