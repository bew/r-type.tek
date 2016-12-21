/**
 * @file Account.hpp
 * @brief Class for a player's account
 * @author Benoit de Chezelles
 */

#ifndef ACCOUNT_HPP_
# define ACCOUNT_HPP_

# include <string>

/**
 * Represent a player's account
 */
class Account
{
public:
  /**
   * Construct an account
   *
   * @param username The username to initialize the account with
   * @param password The password to initialize the account with
   */
  Account(std::string const & username = "", std::string const & password = "");

  /**
   * Construct an account by copy
   *
   * @param other the other account to copy from.
   */
  Account(Account const & other);

  /**
   * Construct an account by assignation
   *
   * @param other the other account to copy from.
   */
  Account & operator=(Account const & other);

  /**
   * Destructor for an account
   */
  ~Account();

public:
  /**
   * Get the username
   *
   * @return the username associated with this account
   */
  std::string const & getUsername() const;

  /**
   * Get the password
   *
   * @return the password associated with this account
   */
  std::string const & getPassword() const;

  /**
   * Set the username
   *
   * @param username the username to be associated with this account
   */
  void setUsername(std::string const & username);

  /**
   * Set the password
   *
   * @param password the password to be associated with this account
   */
  void setPassword(std::string const & password);

private:
  /**
   * Store the username
   */
  std::string _username;

  /**
   * Store the password
   */
  std::string _password;
};

#endif /* !ACCOUNT_HPP_ */
