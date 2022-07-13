#include "plc.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace PLC {

				plc::plc(DataManager *managerInstance, const std::string &Filepath)
								: Manager(managerInstance), filepath(Filepath), totalLadders(0), totalGates(0), gateSequenceBranching(0),
										IBUFFERAMOUNT(0), OBUFFERAMOUNT(0) {
						{
								std::fstream quickCHK(Filepath);
								if (quickCHK.is_open()) {
										C->PTC("HOOKED FILEPATH: ", filepath, "\n");
								} else {
										C->PTC("FILEPATH UNREACHABLE!\n");
								}
						}
						PLCSOURCE plcSource = parsePLC(Filepath);
						setPLC(plcSource);

				}

				plc::~plc() {}

				PLCSOURCE plc::parsePLC(const std::string &Filepath) {
						std::ifstream stream(Filepath);

						enum class PLCType {
										NONE = 0,
										TOTALLADDERS = 1,
										TOTALGATES = 2,
										GATESEQUENCE = 3,
										GATEIOSTRUCTURE = 4,
										GATESTRUCTURE = 5,
										IBUFFERS = 6,
										OBUFFERS = 7
						};

						std::string line;
						std::stringstream ss[8];
						PLCType type = PLCType::NONE;

						while (getline(stream, line)) {
								if (line.find('#') != std::string::npos) {
										if (line.find("TOTALLADDERS") != std::string::npos) {
												type = PLCType::TOTALLADDERS;
										} else if (line.find("TOTALGATES") != std::string::npos) {
												type = PLCType::TOTALGATES;
										} else if (line.find("GATESEQUENCE") != std::string::npos) {
												type = PLCType::GATESEQUENCE;
										} else if (line.find("GATEIOSTRUCTURE") != std::string::npos) {
												type = PLCType::GATEIOSTRUCTURE;
										} else if (line.find("GATESTRUCTURE") != std::string::npos) {
												type = PLCType::GATESTRUCTURE;
										} else if (line.find("IBUFFERS") != std::string::npos) {
												type = PLCType::IBUFFERS;
										} else if (line.find("OBUFFERS") != std::string::npos) {
												type = PLCType::OBUFFERS;
										}
								} else {
										ss[(int) type] << line << '\n';
								}
						}
						//std::cout << ss[4].str();
						//return {ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str(), ss[6].str(), ss[7].str(), ss[8].str()};
						return {ss[1].str(), ss[2].str(), ss[3].str(), ss[4].str(), ss[5].str(), ss[6].str(), ss[7].str()};
				}

				void plc::setPLC(PLCSOURCE &plcsource) {
						settotalladders(plcsource);
						settotalgates(plcsource);
						setgatesequence(plcsource);
						setgateiostructure(plcsource);
						setgatestructure(plcsource);
						setibuffers(plcsource);
						setobuffers(plcsource);
				}

				void plc::printAllInfo() {
						std::cout << "Total ladders: " << totalLadders << std::endl;
						std::cout << "Total gates: " << totalGates << std::endl;
						std::cout << "Total gates per ladder: \n";
						for (int i = 0; i < totalLadders; i++) {
								std::cout << i + 1 << ". " << totalGatesPerLadder[i] << std::endl;
						}
						std::cout << "Gates: \n";
						for (int i = 0; i < totalGates + gateSequenceBranching; i++) {
								std::cout << gateSequence.first[i] << " : " << gateSequence.second[i] << std::endl;
						}
						std::cout << "Gate I/O Structure: \n";
						for (int i = 0; i < totalGates; i++) {
								std::cout << gateIOStructure.first[i] << " : " << gateIOStructure.second.first[i] << " "
																		<< gateIOStructure.second.second[i] << std::endl;
						}
						std::cout << "Gate Structure: \n";
						for (int i = 0; i < totalGates - 1; i++) {
								std::cout << i + 1 << ". " << gateStructure.first.first[i] << "/" << gateStructure.first.second[i] << ">" <<
								gateStructure.second.first[i] << "/" << gateStructure.second.second[i] << std::endl;
						}
						std::cout << "GATE INPUT BUFFERS: \n";
						for (int i = 0; i < IBUFFERAMOUNT; i++) {
								std::cout << i + 1 << ". " << IBUFFERS.first[i] << "/" << IBUFFERS.second[i] << std::endl;
						}
						std::cout << "GATE OUTPUT BUFFERS: \n";
						for (int i = 0; i < OBUFFERAMOUNT; i++) {
								std::cout << i + 1 << ". " << OBUFFERS.first[i] << "\\" << OBUFFERS.second[i] << std::endl;
						}

				}

				void plc::settotalladders(PLCSOURCE &plcsource) {
						std::istringstream stoiIN(plcsource.TOTALLADDERS);
						int stoiOUT = 0;
						stoiIN >> stoiOUT;
						totalLadders = stoiOUT;
				}

				void plc::settotalgates(PLCSOURCE &plcsource) {
						bool firstpass = false;
						for (int i = 0; i < totalLadders; i++) {
								int stoiOUT = 0;
								if (!firstpass) {
										std::string str = plcsource.TOTALGATES;
										str = str.at(i);
										std::stringstream stoiIN(str);
										stoiIN >> stoiOUT;
										totalGates = totalGates + stoiOUT;
										firstpass = true;
								} else {
										std::string str = plcsource.TOTALGATES;
										str = str.at(i + 1);
										std::stringstream stoiIN(str);
										stoiIN >> stoiOUT;
										totalGates = totalGates + stoiOUT;
										firstpass = true;
								}
								totalGatesPerLadder.push_back(stoiOUT);
						}
				}

				void plc::setgatesequence(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.GATESEQUENCE);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										if (line.find("NO") != std::string::npos) {
												gateSequence.first.push_back(count);
												gateSequence.second.emplace_back("NO");
										}
										if (line.find("NC") != std::string::npos) {
												gateSequence.first.push_back(count);
												gateSequence.second.emplace_back("NC");
										}
										if (line.find("AND") != std::string::npos) {
												gateSequence.first.push_back(count);
												gateSequence.second.emplace_back("AND");
										}
										if (line.find("OR") != std::string::npos) {
												gateSequence.first.push_back(count);
												gateSequence.second.emplace_back("OR");
										}
										if (line.find(':') != std::string::npos) {
												gateSequence.first.push_back(0);
												gateSequenceBranching = gateSequenceBranching + 1;
												gateSequence.second.emplace_back("BRANCH#" + std::to_string(gateSequenceBranching));
												count--;
										}
								}
								count++;
						}
				}

				void plc::setgateiostructure(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.GATEIOSTRUCTURE);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										//TWO-TO-ONE
										//INTO-GATE
										if (line.find("GATE;GATE|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE;GATE");
												gateIOStructure.second.second.emplace_back("GATE");
										} else if (line.find("GATE;IB|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE;IB");
												gateIOStructure.second.second.emplace_back("GATE");
										} else if (line.find("IB;GATE|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB;GATE");
												gateIOStructure.second.second.emplace_back("GATE");
										} else if (line.find("IB;IB|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB;IB");
												gateIOStructure.second.second.emplace_back("GATE");
										}
												//INTO-OB
										else if (line.find("GATE;GATE|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE;GATE");
												gateIOStructure.second.second.emplace_back("OB");
										} else if (line.find("GATE;IB|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE;IB");
												gateIOStructure.second.second.emplace_back("OB");
										} else if (line.find("IB;GATE|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB;GATE");
												gateIOStructure.second.second.emplace_back("OB");
										} else if (line.find("IB;IB|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB;IB");
												gateIOStructure.second.second.emplace_back("OB");
										}
												//ONE-TO-ONE
												//INTO-GATE
										else if (line.find("IB|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB");
												gateIOStructure.second.second.emplace_back("GATE");
										} else if (line.find("GATE|GATE") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE");
												gateIOStructure.second.second.emplace_back("GATE");
										}
												//INTO-OB
										else if (line.find("IB|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("IB");
												gateIOStructure.second.second.emplace_back("OB");
										} else if (line.find("GATE|OB") != std::string::npos) {
												gateIOStructure.first.push_back(count);
												gateIOStructure.second.first.emplace_back("GATE");
												gateIOStructure.second.second.emplace_back("OB");
										} else {
												std::cout << "ERROR IMPORTING GATE I/O STRUCTURE\n";
										}
								}
								count++;
						}
				}

				void plc::setgatestructure(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.GATESTRUCTURE);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find('>') != std::string::npos) {
										std::string str1 = line;
										std::string str2 = line;
										str1 = str1.substr(1, 2);
										str2 = str2.substr(5, 6);

										std::string num1 = line;
										num1 = num1.at(0);
										std::stringstream n1in(num1);
										int n1out = 0;
										n1in >> n1out;
										std::string num2 = line;
										num2 = num2.at(4);
										std::stringstream n2in(num2);
										int n2out = 0;
										n2in >> n2out;

										gateStructure.first.first.push_back(n1out);
										gateStructure.first.second.push_back(str1);
										gateStructure.second.first.push_back(n2out);
										gateStructure.second.second.push_back(str2);
								}
								count++;
						}
				}

				void plc::setibuffers(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.IBUFFERS);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										std::string toint = line;
										toint = toint.at(0);
										std::stringstream tointstream(toint);
										int currentint = 0;
										tointstream >> currentint;
										while (currentint != count) {
												count++;
										}
										if (line.at(0) != std::string::npos && currentint == count) {
												if (line.find('/') != std::string::npos) {
														std::string str = line;
														str = str.substr(2, 4);
														std::stringstream stoiIN(str);
														int stoiOUT = 0;
														stoiIN >> stoiOUT;
														IBUFFERS.first.push_back(count);
														IBUFFERS.second.emplace_back(str);
														IBUFFERAMOUNT = IBUFFERAMOUNT + 1;
														count++;
												}
										}
								}
						}
				}

				void plc::setobuffers(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.OBUFFERS);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								if (line.find(count)) {
										std::string toint = line;
										toint = toint.at(0);
										std::stringstream tointstream(toint);
										int currentint = 0;
										tointstream >> currentint;
										while (currentint != count) {
												count++;
										}
										if (line.at(0) != std::string::npos && currentint == count) {
												if (line.find('\\') != std::string::npos) {
														std::string str = line;
														str = str.substr(2, 4);
														std::stringstream stoiIN(str);
														int stoiOUT = 0;
														stoiIN >> stoiOUT;
														OBUFFERS.first.push_back(count);
														OBUFFERS.second.emplace_back(str);
														OBUFFERAMOUNT = OBUFFERAMOUNT + 1;
														count++;
												}
										}
								}
						}
				}

//std::pair<std::vector<int>, std::vector<int>>  VV
/*				void plc::setgatestructure(PLCSOURCE &plcsource) {
						std::stringstream stream(plcsource.GATESTRUCTURE);
						std::string line;
						int count = 1;
						while (getline(stream, line)) {
								std::string toint = line;
								toint = toint.at(0);
								std::stringstream tointstream(toint);
								int currentint = 0;
								tointstream >> currentint;
								while (currentint != count) {
										count++;
								}
								if (line.find(count)) {
										if (line.find('>') != std::string::npos) {
												std::string str = line;
												str = str.at(2);
												std::stringstream stoiIN(str);
												int stoiOUT = 0;
												stoiIN >> stoiOUT;
												gateStructure.first.push_back(count);
												gateStructure.second.push_back(stoiOUT);
										}
								}
								count++;
						}
				}*/
}