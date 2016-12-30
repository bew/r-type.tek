/**
 * @file Account.hpp
 * @brief Struct for a player's account
 * @author Benoit de Chezelles
 */

#ifndef ACCOUNT_HPP_
# define ACCOUNT_HPP_

# include <string>

/**
 * Represent a player's account
 */
struct Account
{
  /**
   * The username
   */
  std::string username;

  /**
   * The password
   */
  std::string password;
};

#endif /* !ACCOUNT_HPP_ */
