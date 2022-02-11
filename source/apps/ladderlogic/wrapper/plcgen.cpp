#include "plcgen.h"

namespace PLC {

				plcgen::plcgen(DataManager *managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
								: Manager(managerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource), IBptrs(0), OBptrs(0),
										isModified(false) {
						Ladder = new ladderLogic::ladderlist(Manager);
						construct();
						bindSourceBuffersWithExecution();
						Ladder->displayList();
						//execute();
				}

				plcgen::~plcgen() {
						delete Ladder;
				}

				void plcgen::construct() {
						if (plcsource->totalLadders == 1) {
								//create gates
								for (int j = 0; j < plcsource->totalGates; j++) {
										Ladder->createGate(Ladder->convertstringtogatetype(plcsource->gateSequence.second[j]));
								}
								//assign pointers to IB and OB
								//inputs
								for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
										if (plcsource->gateIOStructure.second.first[i] == "IB;IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
										else if (plcsource->gateIOStructure.second.first[i] == "IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																current->NOsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//NC
														case ladderLogic::gateType::NC:
																current->NCsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
								}
								//outputs
								for (int i = 0; i < plcsource->gateIOStructure.second.second.size(); i++) {
										if (plcsource->gateIOStructure.second.second[i] == "OB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																current->NOsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																break;
																//NC
														case ladderLogic::gateType::NC:
																current->NCsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO OUTPUT BUFFER FOUND\n";
																break;
												}
										}
								}
								//GATE TO GATE I/O
/*						for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
								if (plcsource->gateIOStructure.second.first[i] == "GATE" && plcsource->gateIOStructure.second.second[i] == "GATE") {
										ladderLogic::node *current = Ladder->getnodebypos(i);
										switch (current->getm_GateType()) {
												//NO
												case ladderLogic::gateType::NO:
														current->NOsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
														break;
														//NC
												case ladderLogic::gateType::NC:
														current->NCsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
														break;
														//AND
												case ladderLogic::gateType::AND:
														//current->ANDsetnextpin(newibptr);
														break;
														//OR
												case ladderLogic::gateType::OR:
														//current->ORsetnextpin(newibptr);
														break;
												default:
														std::cout << "NO INPUT BUFFER FOUND\n";
														break;
										}
								}
						}*/
								//set pins
								if (plcsource->totalGates == 1) {
										if (plcsource->totalGates == 1 && Connector.size() == 0) {
												switch (Ladder->head->getm_GateType()) {
														case ladderLogic::gateType::NONE:
																std::cout << "CRITICAL ERROR! NONE GATE TYPE CALLED\n";
																this->~plcgen();
																return;
														case ladderLogic::gateType::NO:
																Ladder->getNOgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
																output = Ladder->getNOgatebypos(0)->getOutput();
																return;
														case ladderLogic::gateType::NC:
																Ladder->getNCgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
																output = Ladder->getNCgatebypos(0)->getOutput();
																return;
														case ladderLogic::gateType::AND:
																Ladder->getANDgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
																Ladder->getANDgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[1]);
																output = Ladder->getANDgatebypos(0)->getOutput();
																//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
																return;
														case ladderLogic::gateType::OR:
																Ladder->getORgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
																Ladder->getORgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[1]);
																output = Ladder->getORgatebypos(0)->getOutput();
																//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
																return;
												}
										}
								} else {
										//set connector
										constructconnectors();
								}
						}
						else {
								//construct gates
								int count = 0;
								std::cout << std::endl;
								for (int k = 0; k < plcsource->totalGates + plcsource->gateSequenceBranching; k++) {
										std::cout << plcsource->gateSequence.first[k] << " " << plcsource->gateSequence.second[k] << "\n";
								}
								for (int i = 0; i < plcsource->totalLadders; i++) {
										for (int j = 0; j < plcsource->totalGatesPerLadder[i]; j++) {
												Ladder->createGate(Ladder->convertstringtogatetype(plcsource->gateSequence.second[count]));
												count = count + 1;
										}
								}
								//inputs
								//binary gate
								for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
										if (plcsource->gateIOStructure.second.first[i] == "IB;IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
										else if (plcsource->gateIOStructure.second.second[i] == "GATE;IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
										else if (plcsource->gateIOStructure.second.second[i] == "IB;GATE") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
										else if (plcsource->gateIOStructure.second.first[i] == "IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																current->NOsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//NC
														case ladderLogic::gateType::NC:
																current->NCsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
								}
/*								//for one input buffer allocations | second position.
								for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
										if (plcsource->gateIOStructure.second.second[i] == "GATE;IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
								}
								//for one input buffer allocations | first position.
								for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
										if (plcsource->gateIOStructure.second.second[i] == "IB;GATE") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NO GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//NC
														case ladderLogic::gateType::NC:
																std::cout << "CANNOT ALLOCATE SECOND POSITIONAL INPUT BUFFERS TO AN NC GATE. ABORTING.\n";
																this->~plcgen();
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs + 1]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
								}
								//for one input buffer allocations | first position.
								for (int i = 0; i < plcsource->gateIOStructure.second.first.size(); i++) {
										if (plcsource->gateIOStructure.second.first[i] == "IB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																current->NOsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//NC
														case ladderLogic::gateType::NC:
																current->NCsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetnextpin(iobuffersource->IBUFFER.second[IBptrs]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO INPUT BUFFER FOUND\n";
																break;
												}
										}
								}*/
								//outputs
								for (int i = 0; i < plcsource->gateIOStructure.second.second.size(); i++) {
										if (plcsource->gateIOStructure.second.second[i] == "OB") {
												ladderLogic::node *current = Ladder->getnodebypos(i);
												switch (current->getm_GateType()) {
														//NO
														case ladderLogic::gateType::NO:
																current->NOsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																break;
																//NC
														case ladderLogic::gateType::NC:
																current->NCsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																break;
																//AND
														case ladderLogic::gateType::AND:
																current->ANDsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																//current->ANDsetnextpin(newibptr);
																break;
																//OR
														case ladderLogic::gateType::OR:
																current->ORsetoutput(iobuffersource->OBUFFER.second[OBptrs]);
																//current->ORsetnextpin(newibptr);
																break;
														default:
																std::cout << "NO OUTPUT BUFFER FOUND\n";
																break;
												}
										}
								}
								//set pin ptrs
								constructconnectors();
						}
				}

				void plcgen::constructconnectors() {
						if (plcsource->totalGates == 1) {
								return;
						}
						if (Connector.size() >= 1) {
								for (int i = Connector.size() - 1; i < 0; i--) {
										delete Connector[i];
								}
						}
						//MULTIPLE LADDERS
						if (plcsource->totalLadders > 1) {
								for (int i = 0; i < plcsource->gateStructure.first.first.size(); i++) {
										//std::cout << i + 1 << ". conncetors: " << plcsource->gateStructure.first.second[i] << " : " << plcsource->gateStructure.second.second[i] << std::endl;
										//1st NO = 2nd X
										if (plcsource->gateStructure.first.second[i] == "NO" && plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												/*if(i == plcsource->gateStructure.first.first.size() - 1){
														output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
												}*/
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NO" &&
																					plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NO" &&
																					plcsource->gateStructure.second.second[i] == "AN") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NO" &&
																					plcsource->gateStructure.second.second[i] == "OR") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										}
												//1st NC = 2nd X
										else if (plcsource->gateStructure.first.second[i] == "NC" &&
																			plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NC" &&
																					plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NC" &&
																					plcsource->gateStructure.second.second[i] == "AN") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NC" &&
																					plcsource->gateStructure.second.second[i] == "OR") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										}
												//1st AND = 2nd X
										else if (plcsource->gateStructure.first.second[i] == "AN" &&
																			plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getANDgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "AN" &&
																					plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getANDgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "AN" &&
																					plcsource->gateStructure.second.second[i] == "AN") {
												//TODO: KEEP TRACK OF ALL GATE TYPES BY THEIR POSITION AND PASS THEM DOWN TO THE NEWCONNECTOR.
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getANDgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "AN" &&
																					plcsource->gateStructure.second.second[i] == "OR") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getANDgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										}
												//1st OR = 2nd X
										else if (plcsource->gateStructure.first.second[i] == "OR" &&
																			plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getORgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "OR" &&
																					plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getORgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "OR" &&
																					plcsource->gateStructure.second.second[i] == "AN") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getORgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "OR" &&
																					plcsource->gateStructure.second.second[i] == "OR") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getORgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										}
								}
						}
								//SINGLE LADDER
						else {
								for (int i = 0; i < plcsource->gateStructure.first.first.size(); i++) {
										if (plcsource->gateStructure.first.second[i] == "NO" && plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NC" &&
																					plcsource->gateStructure.second.second[i] == "NC") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NO" &&
																					plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										} else if (plcsource->gateStructure.first.second[i] == "NC" &&
																					plcsource->gateStructure.second.second[i] == "NO") {
												lgates::connector *newconnector = new lgates::connector
																(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
																	Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
												Connector.push_back(newconnector);
												output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
										}
								}
						}
						isModified = false;
				}

				void plcgen::bindSourceBuffersWithExecution() {
						if (plcsource->totalGates == 1) {
								switch (Ladder->head->getm_GateType()) {
										case ladderLogic::gateType::NONE:
												std::cout << "CRITICAL ERROR! NONE GATE TYPE CALLED\n";
												this->~plcgen();
												return;
										case ladderLogic::gateType::NO:
												Ladder->getNOgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getNOgatebypos(0)->getOutput();
												return;
										case ladderLogic::gateType::NC:
												Ladder->getNCgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getNCgatebypos(0)->getOutput();
												return;
										case ladderLogic::gateType::AND:
												Ladder->getANDgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getANDgatebypos(0)->getOutput();
												//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												return;
										case ladderLogic::gateType::OR:
												Ladder->getORgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getORgatebypos(0)->getOutput();
												//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												return;
								}
						}
						//recalculate and rebind
						for (int i = 0; i < plcsource->gateIOStructure.second.second.size(); i++) {
								if (plcsource->gateIOStructure.second.second[i] == "OB") {
										ladderLogic::node *current = Ladder->getnodebypos(i);
										switch (current->getm_GateType()) {
												//NO
												case ladderLogic::gateType::NO:
														output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
														break;
														//NC
												case ladderLogic::gateType::NC:
														output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
														break;
														//AND
												case ladderLogic::gateType::AND:
														output = Ladder->getANDgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
														//current->ANDsetnextpin(newibptr);
														break;
														//OR
												case ladderLogic::gateType::OR:
														output = Ladder->getORgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
														//current->ORsetnextpin(newibptr);
														break;
												default:
														std::cout << "REBINDING CRASHED\n";
														break;
										}
								}
						}
						//bind outputbuffers
						for (int i = 0; i < iobuffersource->getTotaloutputlabels(); i++) {

								iobuffersource->OBUFFER.second[i] = output;
						}
						//rebind inputbuffers
						for (int i = 0; i < iobuffersource->getTotalinputlabels(); i++) {
								inputs.push_back(Connector[0]->fromgate->returnpin1());
						}
				}

				void plcgen::switchinput(int pos) {
						if (pos <= 0) {
								std::cout << "Cannot switch input of 0 or lower than 0!\n";
								return;
						} else if (pos > iobuffersource->getTotalinputlabels()) {
								std::cout << "Cannot switch input - exceeding total amount of inputs\n";
								this->~plcgen();
								return;
						}
						iobuffersource->switchIBUFFERELEMENT(iobuffersource->IBUFFER.first.second[pos - 1]);
						isModified = true;
				}

				void plcgen::switchinput(int pos, int pos2) {
						if (pos <= 0 || pos2 <= 0) {
								std::cout << "Cannot switch input of 0 or lower than 0!\n";
								return;
						} else if (pos > iobuffersource->getTotalinputlabels() || pos2 > iobuffersource->getTotalinputlabels()) {
								std::cout << "Cannot switch input - exceeding total amount of inputs\n";
								this->~plcgen();
								return;
						}
						iobuffersource->switchIBUFFERELEMENT(iobuffersource->IBUFFER.first.second[pos - 1]);
						iobuffersource->switchIBUFFERELEMENT(iobuffersource->IBUFFER.first.second[pos2 - 1]);
						isModified = true;
				}

				void plcgen::checkIB() {

				}

				void plcgen::updateoutput() {
						if (plcsource->totalGates == 1) {
								switch (Ladder->head->getm_GateType()) {
										case ladderLogic::gateType::NONE:
												std::cout << "CRITICAL ERROR! NONE GATE TYPE CALLED\n";
												this->~plcgen();
												return;
										case ladderLogic::gateType::NO:
												Ladder->getNOgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getNOgatebypos(0)->getOutput();
												return;
										case ladderLogic::gateType::NC:
												Ladder->getNCgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getNCgatebypos(0)->getOutput();
												return;
										case ladderLogic::gateType::AND:
												Ladder->getANDgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getANDgatebypos(0)->getOutput();
												//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												return;
										case ladderLogic::gateType::OR:
												Ladder->getORgatebypos(0)->setNextPin(iobuffersource->IBUFFER.second[0]);
												output = Ladder->getORgatebypos(0)->getOutput();
												//std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												return;
								}
						}
						lgates::connector *newoutput = Connector[Connector.size() - 1];
						output = newoutput->togate->getOutput();
				}

				void plcgen::execute() {
						for (int i = 0; i < 1; i++) {
								if (isModified) {
										updateoutput();
										bindSourceBuffersWithExecution();
										constructconnectors();
								}

								//std::cout << "OUTPUT BUFFER:" << *iobuffersource->OBUFFER.second[0] << std::endl;
								//std::cout << "FIRST PIN IN: " << *Connector[0]->fromgate->returnpin1() << std::endl;

								for (int j = 0; j < iobuffersource->getTotalinputlabels(); j++) {
										std::cout << "INPUT BUFFER:" << *iobuffersource->IBUFFER.second[j] << std::endl;
								}
								for (int k = 0; k < iobuffersource->getTotaloutputlabels(); k++) {
										std::cout << "OUTPUT BUFFER:" << *iobuffersource->OBUFFER.second[k] << std::endl;
								}
								std::cout << "Execute output:" << *output << std::endl;
								//switchinput(2, 3);
								//switchinput(1, 4);
								//switchinput();
						}
				}
}