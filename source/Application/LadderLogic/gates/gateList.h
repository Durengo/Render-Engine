#pragma once

//#include<iostream>

#include "../utils/DataManager.h"
#include "logicGate.h"
#include "node.h"
#include "../wrapper/IOBuffer.h"
#include "../wrapper/plc.h"

namespace ladderLogic {

				class gateList {
				public:
								node *head = nullptr; //Initialize head pointer to nullptr
								node *tail = nullptr; //Initialize tail pointer to nullptr

								bool isModified;
								bool isComplete;

								gateList();

								explicit gateList(DataManager *ManagerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource);

								~gateList();

								//void linkPLCandBuffers();

								void switchINPUT();

								void switchOUTPUT();

								void construct();

								int* gateOUTtogateIN();

								void execute();

								//void constructGates(std::vector<int> INSTRUCTIONSET, std::string INPUTBUFFER[], std::string OUTPUTBUFFER[]);

								//void executeSpecificGateLogic(int nodeselect);



				private:
								DataManager *Manager;

								PLC::plc *plcsource;

								PLC::IOBuffer *iobuffersource;

								std::pair<std::vector<int*>, std::vector<std::string*>> INPUTS;
								std::pair<std::vector<int*>, std::vector<std::string*>> OUTPUTS;

								std::pair<std::pair<std::vector<int*>, std::vector<int>>, std::vector<std::string>> GTGIB;//Gate-to-gate input buffer
								std::pair<std::pair<std::vector<int*>, std::vector<int>>, std::vector<std::string>> GTGOB;//Gate-to-gate output buffer

								std::pair<std::vector<int*>, std::vector<std::string>> gatetogateIO;

								void addGTGIB(node* newGate);

								void addGTGOB(node* newGate);

								void linkGTGBuffers(int count);

								int m_GatesInList;

								int m_GateListSpecificID;

								int m_UniqueGateListID;

								int checkGateType(node *current);

								int getm_GateListSpecificID() const;

								void setm_GateListSpecificID();

								bool SearchForGateDuplicates(node *newGate);

								int getm_GatesInList() const;

								void setm_GatesInList(int m_GatesInList);

								// 1 INPUT ONE OUTPUT
								//IN: GATE | OUT: OB
								void createGate_1_0IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, const std::string& outputlabel);
								void createGate_1_0IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int *outputlabel);

								//IN: GATE | OUT: GATE
								void createGate_1_0IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, const std::string& inputlabel, const std::string& outputlabel);
								//IN: IB | OUT: OB
								void createGate_1_1IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, const std::string& inputlabel, const std::string& outputlabel);
								//IN: IB | OUT: GATE
								void createGate_1_1IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int* outputlabel);
								//IN: GATE | OUT: GATE
								void createGate_1_GATEIN_GATEOUT(ladderLogic::gateType type, int *firstPin);

								// 2 INPUTS ONE OUTPUT
								//INTO GATE:
								//IN: GATE;GATE | OUT: GATE
								void createGate_2_0IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& inputlabel);
								//IN: GATE;IB; IB;GATE; | OUT: GATE
								void createGate_2_1IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& inputlabel);
								//IN: IB;IB | OUT: GATE
								void createGate_2_2IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& inputlabel, const std::string& inputlabel2);
								//INTO OB:
								//IN: GATE;GATE | OUT: OB
								void createGate_2_0IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& outputlabel);
								//IN: GATE;IB; IB;GATE; | OUT: OB
								void createGate_2_1IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& inputlabel, const std::string& outputlabel);
								//IN: IB;IB | OUT: OB
								void createGate_2_2IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int* secondPin, const std::string& inputlabel, const std::string& inputlabel2, const std::string& outputlabel);


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