/**
 * @file Account.cpp
 * @author Benoit de Chezelles
 * @brief Implementation for an Account
 */

#include "Account.hpp"

Account::Account(std::string const & username, std::string const & password) :
  _username(username),
  _password(password)
{}

Account::Account(Account const & other) :
  _username(other._username),
  _password(other._password)
{}

Account::~Account()
{}

Account & Account::operator=(Account const & other)
{
  _username = other._username;
  _password = other._password;
  return *this;
}

std::string const & Account::getUsername() const
{
  return _username;
}

std::string const & Account::getPassword() const
{
  return _password;
}

void Account::setUsername(std::string const & username)
{
  _username = username;
}

void Account::setPassword(std::string const & password)
{
  _password = password;
}
