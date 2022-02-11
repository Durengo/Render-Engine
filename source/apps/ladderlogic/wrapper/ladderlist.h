#pragma once

//#include<iostream>

#include "../utils/DataManager.h"
//#include "logicGate.h"
#include "node.h"
#include "../wrapper/IOBuffer.h"
#include "../wrapper/plc.h"

namespace ladderLogic {

				class ladderlist {
				public:
								node *head = nullptr; //Initialize head pointer to nullptr
								node *tail = nullptr; //Initialize tail pointer to nullptr

								bool isModified;
								bool isComplete;

								//ladderlist();

								//ladderlist(DataManager *ManagerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource);
								explicit ladderlist(DataManager *ManagerInstance);

								~ladderlist();

								void createGate(ladderLogic::gateType type);

								void displayList() const;

								int length() const;

								void deleteHead();

								void deleteTail();

								void deleteByPos(int position);

								void deletePos(int position);

								node* getnodebypos(int pos);

								lgates::NO *getNOgatebypos(int pos);

								lgates::NC *getNCgatebypos(int pos);

								lgates::AND *getANDgatebypos(int pos);

								lgates::OR *getORgatebypos(int pos);

								gateType convertstringtogatetype(const std::string& gatetype);

								int NOgates;

								int NCgates;

								int ANDgates;

								int ORgates;

				private:
								DataManager *Manager;

								//PLC::plc *plcsource;

								//PLC::IOBuffer *iobuffersource;

								std::pair<std::vector<int*>, std::vector<std::string*>> INPUTS;
								std::pair<std::vector<int*>, std::vector<std::string*>> OUTPUTS;

								std::pair<std::pair<std::vector<int*>, std::vector<int>>, std::vector<std::string>> GTGIB;//Gate-to-gate input buffer
								std::pair<std::pair<std::vector<int*>, std::vector<int>>, std::vector<std::string>> GTGOB;//Gate-to-gate output buffer

								std::pair<std::vector<int*>, std::vector<std::string>> gatetogateIO;

								int m_GatesInList;

								int m_GateListSpecificID;

								int m_UniqueGateListID;

								int checkGateType(node *current);

								int getm_GateListSpecificID() const;

								void setm_GateListSpecificID();

								bool SearchForGateDuplicates(node *newGate);

								int getm_GatesInList() const;

								void setm_GatesInList(int m_GatesInList);

				};

}