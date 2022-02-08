#include "plcgen.h"

namespace PLC {

				plcgen::plcgen(DataManager *managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
								: Manager(managerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource), IBptrs(0), OBptrs(0)	{
						Ladder = new ladderLogic::ladderlist(Manager);
						construct();
						bindSourceBuffersWithOutput();
						Ladder->displayList();
				}

				plcgen::~plcgen() {
						delete Ladder;
				}

				void plcgen::construct() {
						//create gates
						for (int i = 0; i < plcsource->totalLadders; i++) {
								for (int j = 0; j < plcsource->totalGates; j++) {
										Ladder->createGate(Ladder->convertstringtogatetype(plcsource->gateSequence.second[j]));
								}
						}
						//assign pointers to IB and OB
						//inputs
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
														//current->ANDsetnextpin(newibptr);
														break;
														//OR
												case ladderLogic::gateType::OR:
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


						//set connector
						for (int i = 0; i < plcsource->gateStructure.first.first.size(); i++) {
								if(plcsource->gateStructure.first.second[i] == "NO" && plcsource->gateStructure.second.second[i] == "NC"){
										lgates::connector *newconnector = new lgates::connector
														(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
															Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
										Connector.push_back(newconnector);
										output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
								}
								else if(plcsource->gateStructure.first.second[i] == "NC" && plcsource->gateStructure.second.second[i] == "NC"){
										lgates::connector *newconnector = new lgates::connector
														(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
															Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1));
										Connector.push_back(newconnector);
										output = Ladder->getNCgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
								}
								else if(plcsource->gateStructure.first.second[i] == "NO" && plcsource->gateStructure.second.second[i] == "NO"){
										lgates::connector *newconnector = new lgates::connector
														(Ladder->getNOgatebypos(plcsource->gateStructure.first.first[i] - 1),
															Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
										Connector.push_back(newconnector);
										output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
								}
								else if(plcsource->gateStructure.first.second[i] == "NC" && plcsource->gateStructure.second.second[i] == "NO"){
										lgates::connector *newconnector = new lgates::connector
														(Ladder->getNCgatebypos(plcsource->gateStructure.first.first[i] - 1),
															Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1));
										Connector.push_back(newconnector);
										output = Ladder->getNOgatebypos(plcsource->gateStructure.second.first[i] - 1)->getOutput();
								}
						}


				}

				void plcgen::bindSourceBuffersWithOutput() {
						for(int i = 0; i < iobuffersource->getTotaloutputlabels(); i++){
								iobuffersource->OBUFFER.second[i] = output;
						}
				}

				void plcgen::execute() {
						std::cout << Connector[0] << std::endl;
							std::cout << *output << std::endl;
							std::cout << *iobuffersource->OBUFFER.second[0];
				}
}