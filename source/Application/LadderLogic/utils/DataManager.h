#pragma once
//This "Data_Manager" module is meant to track and modify all information about the user object;

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>

#include "Console.h"

#define C Manager->ConsoleHook
#define LOG Manager->ConsoleHook->LogHook

class DataManager {
private:

				int m_TotalScriptLines; //Static int to keep track of the total amount of users.
				int m_TotalLogicGates;

				int CurrentUserID = 0; //Static int to keep track of the current (logged in) user.
				std::string CurrentUserUsername = "NULL"; //Static string to keep track of the current (logged in) user.

public:
				Console *ConsoleHook;

				DataManager(); //Set up a constructor to generate a random amount of storage for the services to use and allocate it to heap.
				~DataManager();

				int getm_TotalScriptLines() const; //Function to get the total user amount.
				void addTom_TotalScriptLines(); //Function to increment the total user amount by 1.
				void subtractFromm_TotalScriptLines(); //Function to deduct 1 form the total user amount.

				int getm_TotalLogicGates() const; //Function to get the total user amount.
				void addTom_TotalLogicGates(); //Function to increment the total user amount by 1.
				void subtractFromm_TotalLogicGates(); //Function to deduct 1 form the total user amount.

				int getCurrentUserID() const; //Function to get the current ID of the user that is logged in now.
				void
				setCurrentUserID(int NewID); //Function to set the current ID of the user (logging out, switching user(-s)).

				std::string
				getCurrentUserUsername(); //Function to get the current username of the user that is logged in now.
				void setCurrentUserUsername(
								const std::string &NewUsername); //Function to set the current username (e.g. when logging out, set to NULL)
};