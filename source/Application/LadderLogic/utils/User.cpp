#include "User.h"

User::User(std::string name, std::string pass)
        : Username(std::move(name)), Password(std::move(pass)), Unique_ID(0)
{

}

void User::setUsername(const std::string &username)
{ //Setter for Username.
  Username = username;
}

const std::string &User::getUsername() const
{ //Getter for Username.
  return Username;
}

void User::setPassword(const std::string &username)
{ //Setter for Password.
  Password = username;
}

const std::string &User::getPassword() const
{ //Getter for Password.
  return Password;
}

int User::getUniqueId() const
{
  return Unique_ID;
}

void User::setUniqueId(int uniqueId)
{
  Unique_ID = uniqueId;
}