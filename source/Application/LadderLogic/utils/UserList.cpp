#include "UserList.h"

UserList::UserList(DataManager *ManagerInstance, UserFlagList type)
        : Manager(nullptr), UserFlag("!USER FLAG NOT SET!")
{
  Manager = ManagerInstance;

  C->PTC("\nData manger hooked!\n");
  C->PTC("\nUser List constructed!\n");
  setUserFlagList(type);
  LOG->PTF("\nData manger hooked!\n");
  LOG->PTF("\nUser List constructed! Type: ", UserFlag, "\n");
}

UserList::~UserList()
{
  C->PTC("\nUser list destructed!\n");
  LOG->PTF("\nUser list destructed!\n");
}

void UserList::setUserFlagList(UserFlagList type)
{
  switch (type) {
    case UserFlagList::Admin:
      UserFlag = "Admin";
      C->PTC("\nUser List type: ", "Admin", "\n");
      break;
    case UserFlagList::Lecturer:
      UserFlag = "Lecturer";
      C->PTC("\nUser List type: ", "Lecturer", "\n");
      break;
    case UserFlagList::Learner:
      UserFlag = "Learner";
      C->PTC("\nUser List type: ", "Learner", "\n");
      break;
    case UserFlagList::Guest:
      UserFlag = "Guest";
      C->PTC("\nUser List type: ", "Guest", "\n");
      break;
  }
}