#pragma once

//#include<iostream>

#include "../utils/DataManager.h"
#include "logicGate.h"
#include "node.h"
#include "../wrapper/IOBuffer.h"

namespace ladderLogic {

				class gateList {
				public:
								node *head = nullptr; //Initialize head pointer to nullptr
								node *tail = nullptr; //Initialize tail pointer to nullptr

								DataManager *Manager;

								IOBuffer *ioBuffer;

								bool m_InitialInput, m_InitialOutput;

								void switchm_InitialInput();

								void switchm_InitialOutput();

								int m_UniqueGateListID;

								gateList();

								explicit gateList(DataManager *ManagerInstance, ladderLogic::IOBuffer *buffer);

								~gateList();

								bool isModified;

								std::pair<std::string, bool> *inputBufferPTR;

								std::pair<std::string, bool> *outputBufferPTR;

								std::vector<int> instructionSet;

								void constructGates(std::vector<int> INSTRUCTIONSET, std::string INPUTBUFFER[], std::string OUTPUTBUFFER[]);

								void executeAllGates();

								void executeSpecificGateLogic(int nodeselect);

								int checkGateType(node *current);

								int m_GatesInList;

								int m_GateListSpecificID;

								int getm_GateListSpecificID() const;

								void setm_GateListSpecificID();

								bool SearchForGateDuplicates(node *newGate);

								int getm_GatesInList() const;

								void setm_GatesInList(int m_GatesInList);

								void createGate(ladderLogic::gateType, int firstPin); //for one input gates

								void createGate(ladderLogic::gateType, int firstPin, int secondPin); //for two input gates

								void displayList() const; //Function for displaying all elements in a linked list.
								int length() const; //Function to count the length of the linked list.

								void
								deleteHead(); //Function to delete ONLY the initial element of a linked list (leaving other elements still linked).

								void
								deleteTail(); //Function to delete ONLY the terminal element of a linked list (leaving other elements still linked).

								void deleteByPos(
												int position); //Function to delete an element from a linked list by a given position. Runs through multiple cases to either run the deleteHead() function or the deleteTail() function; else call the deletePos() function.

								void deletePos(
												int position); //Function to delete any element from a linked list, but not the initial or terminal element.
				};

}