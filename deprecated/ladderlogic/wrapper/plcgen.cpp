#include "plcgen.h"

namespace PLC {

				plcgen::plcgen(DataManager *managerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
								: Manager(managerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource), IBptrs(0), OBptrs(0),
										isModified(false) {
						Ladder = new ladderLogic::ladderlist(Manager);
						construct();
						bindSourceBuffersWithExecution();
						Ladder->displayList();
						execute();
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
						if(plcsource->totalGates == 1){
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
														std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
														this->~plcgen();
														return;
												case ladderLogic::gateType::OR:
														std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
														this->~plcgen();
														return;
										}

								}
						}else{
								//set connector
								constructconnectors();
						}

				}

				void plcgen::constructconnectors() {
						if(plcsource->totalGates == 1){
								return;
						}
						if (Connector.size() >= 1) {
								for (int i = Connector.size() - 1; i < 0; i--) {
										delete Connector[i];
								}
						}
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
												std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												this->~plcgen();
												return;
										case ladderLogic::gateType::OR:
												std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												this->~plcgen();
												return;
								}
						}
						for (int i = 0; i < iobuffersource->getTotaloutputlabels(); i++) {
								iobuffersource->OBUFFER.second[i] = output;
						}
						for (int i = 0; i < iobuffersource->getTotalinputlabels(); i++) {
								inputs.push_back(Connector[0]->fromgate->returnpin1());
						}
				}

				void plcgen::switchinput() {

						iobuffersource->switchIBUFFERELEMENT(iobuffersource->IBUFFER.first.second[0]);
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
												std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												this->~plcgen();
												return;
										case ladderLogic::gateType::OR:
												std::cout << "CRITICAL ERROR! CANNOT HAVE A SINGLE BINARY GATE IN A LADDER\n";
												this->~plcgen();
												return;
								}
						}
						lgates::connector *newoutput = Connector[Connector.size() - 1];
						output = newoutput->togate->getOutput();
				}

				void plcgen::execute() {
						for (int i = 0; i < 3; i++) {
								if (isModified) {
										updateoutput();
										bindSourceBuffersWithExecution();
										constructconnectors();
								}

								//std::cout << "OUTPUT BUFFER:" << *iobuffersource->OBUFFER.second[0] << std::endl;
								//std::cout << "FIRST PIN IN: " << *Connector[0]->fromgate->returnpin1() << std::endl;
								std::cout << "INPUT BUFFER:" << *iobuffersource->IBUFFER.second[0] << std::endl;
								std::cout << "Execute output:" << *output << std::endl;
								//switchinput();
						}
				}
}