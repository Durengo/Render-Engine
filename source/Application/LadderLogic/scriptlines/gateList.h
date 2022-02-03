#pragma once

//#include<iostream>

#include "../utils/DataManager.h"
#include "../utils/Console.h"
#include "../gates/logicGate.h"
#include "node.h"

class gateList {
public:
				node *head = nullptr; //Initialize head pointer to nullptr
				node *tail = nullptr; //Initialize tail pointer to nullptr

				DataManager *Manager;

				int m_UniqueGateListID;

				explicit gateList(DataManager *ManagerInstance);

				~gateList();

				void executeGateLogic(int nodeselect);

				int checkGateType(node *current);

				int m_GatesInList;

				bool SearchForUsernameDuplicate(node *newGate);

				int getm_GatesInList() const;

				void setm_GatesInList(int gatesInList);

				void createGate(ladderLogic::gateType);

				void displayList() const; //Function for displaying all elements in a linked list.
				int length() const; //Function to count the length of the linked list.

				void
				deleteHead(); //Function to delete ONLY the initial element of a linked list (leaving other elements still linked).

				void
				deleteTail(); //Function to delete ONLY the terminal element of a linked list (leaving other elements still linked).

				void deleteByPos(
								int position); //Function to delete an element from a linked list by a given position. Runs through multiple cases to either run the deleteHead() function or the deleteTail() function; else call the deletePos() function.

				void deletePos(
								int position) const; //Function to delete any element from a linked list, but not the initial or terminal element.
};