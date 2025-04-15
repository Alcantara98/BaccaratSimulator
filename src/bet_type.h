#ifndef BET_TYPE_H
#define BET_TYPE_H

#include <array>
#include <string>

namespace BACCARAT
{

/**
 * @brief Enum class to represent the different bet types in Baccarat.
 */
enum class BetType : std::uint8_t
{
  PLAYER,
  BANKER,
  TIE,
  NONE
};

/**
 * @brief Convert a BetType enum to a string representation.
 *
 * @param bet_type The BetType enum value.
 *
 * @return The string representation of the bet type.
 */
[[nodiscard]] static auto
get_string_bet_type(const BetType &bet_type) -> std::string
{
  static const std::array<std::string, 3> BET_TYPE_STRINGS = {"PLAYER",
                                                              "BANKER", "TIE"};
  return BET_TYPE_STRINGS[static_cast<std::size_t>(bet_type)];
}

} // namespace BACCARAT

#endif // BET_TYPE_H