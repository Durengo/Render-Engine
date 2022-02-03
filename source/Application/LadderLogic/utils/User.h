#pragma once

#include <iostream>
#include <utility>

#include "DataManager.h"

class User {
private:
  std::string Username;
  std::string Password;
  int Unique_ID;

public:
  User(std::string name, std::string pass);

  void setUsername(const std::string &username);

  const std::string &getUsername() const;

  void setPassword(const std::string &username);

  const std::string &getPassword() const;

  int getUniqueId() const;

  void setUniqueId(int uniqueId);

};