#pragma once

#include<iostream>

#include "DataManager.h"
#include "Console.h"

class UserList {
public:
  DataManager *Manager;
  std::string UserFlag;
  enum UserFlagList {
    Admin, Lecturer, Learner, Guest
  };

  //UserList(); //Constructor for our linked lists.

  UserList(DataManager *ManagerInstance, UserFlagList type);

  virtual ~UserList();

  void setUserFlagList(UserFlagList type);

};