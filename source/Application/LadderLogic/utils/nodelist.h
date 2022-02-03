#pragma once

#include<iostream>

#include "node.h"
#include "UserList.h"

class nodelist : public UserList {
public:
				node *head = nullptr; //Initialize head pointer to nullptr
				node *tail = nullptr; //Initialize tail pointer to nullptr

				explicit nodelist(DataManager *ManagerInstance, UserFlagList type);

				void DisplayList() const; //Function for displaying all elements in a linked list.
				void CreateUser(const std::string &username,
																				const std::string &password); //Function for creating new users (nodes/elements in the linked list) and allocating them to heap.
				bool SearchForUsernameDuplicate(
								const std::string &username) const; //Function used when creating new users to check for duplicate usernames.
				int length() const; //Function to count the length of the linked list.

				void
				deleteHead(); //Function to delete ONLY the initial element of a linked list (leaving other elements still linked).

				void
				deleteTail(); //Function to delete ONLY the terminal element of a linked list (leaving other elements still linked).

				void deleteByPos(
								int position); //Function to delete an element from a linked list by a given position. Runs through multiple cases to either run the deleteHead() function or the deleteTail() function; else call the deletePos() function.

				void deletePos(
								int position) const; //Function to delete any element from a linked list, but not the initial or terminal element.

				bool UserLogin() const; //Function to prompt user to log into an already existing user class object.

				bool SearchForUserLogin(std::string &username,
																												std::string &password) const; //Function which is called by UserLogin() function to check if the entered username AND password matches any user class objects in a user list.

				void
				DeleteUserByID(
								int CurrentUserID); //Function to delete a currently logged-in user (Current_User_ID).

				node *GetUserByID(
								int UniqueID) const; //Function to get a user object from a linked list by searching for their ID.
};