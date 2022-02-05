#include "plc.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace PLC {

				plc::plc(DataManager &managerInstance, const std::string &Filepath)
								: Manager(&managerInstance), filepath(Filepath), totalLadders(0)	{
						C->PTC("HOOKED FILEPATH: ", filepath, "\n");
						//PLCSOURCE plcsrc = parsePLC();
						//passInfo();
						parsePLC(Filepath);
						//std::cout << totalLadders;
						//std::cout << plcsrc.TOTALGATES;
						//std::cout << PLC.OBUFFERS;
				}

				plc::~plc(){}

				PLCSOURCE plc::parsePLC(const std::string& Filepath) {
						std::ifstream stream(Filepath);

						enum class PLCType {
										//NONE = 0,
										TOTALLADDERS = 0,
										TOTALGATES = 1,
										GATESEQUENCE = 2,
										GATEIOSTRUCTURE = 3,
										GATESTRUCTURE = 6,
										IBUFFERS = 7,
										OBUFFERS = 8
						};

						std::string line;
						std::stringstream ss[7];
						PLCType type;// = PLCType::NONE;

						if(stream.is_open()){
								std::cout << "FILE IS OPEN\n";
						}
						else{
								std::cout << "FILE IS CLOSED\n";
						}

						while (getline(stream, line)) {
								if (line.find('#') != std::string::npos) {
										if (line.find("TOTALLADDERS") != std::string::npos) {
												type = PLCType::TOTALLADDERS;
										} else if (line.find("TOTALGATES") != std::string::npos) {
												type = PLCType::TOTALGATES;
										}else if (line.find("GATESEQUENCE") != std::string::npos) {
												type = PLCType::GATESEQUENCE;
										}else if (line.find("GATEIOSTRUCTURE") != std::string::npos) {
												type = PLCType::GATEIOSTRUCTURE;
										}else if (line.find("GATESTRUCTURE") != std::string::npos) {
												type = PLCType::GATESTRUCTURE;
										}else if (line.find("IBUFFERS") != std::string::npos) {
												type = PLCType::IBUFFERS;
										}else if (line.find("OBUFFERS") != std::string::npos) {
												type = PLCType::OBUFFERS;
										}
								}
								else {
										ss[(int) type] << line << '\n';
								}
								if(stream.bad()){
										std::cout << "BAD\n";
								}else {std::cout << "\nGOOD\n";}
						}
						std::cout << ss[1].str();
						return {ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str(), ss[4].str(), ss[5].str(), ss[6].str()};
				}

				void plc::passInfo() {
						std::ifstream stream(filepath);

						enum class PLCType {
										//NONE = 0,
										TOTALLADDERS = 0,
										TOTALGATES = 1,
										GATESEQUENCE = 2,
										GATEIOSTRUCTURE = 3,
										GATESTRUCTURE = 6,
										IBUFFERS = 7,
										OBUFFERS = 8
						};

						std::string line;
						std::stringstream ss[7];
						PLCType type;// = PLCType::NONE;

						if(stream.is_open()){
								std::cout << "FILE IS OPEN\n";
						}
						else{
								std::cout << "FILE IS CLOSED\n";
						}

						while (getline(stream, line)) {
								if (line.find('#') != std::string::npos) {
										if (line.find("TOTALLADDERS") != std::string::npos) {
												type = PLCType::TOTALLADDERS;
										} else if (line.find("TOTALGATES") != std::string::npos) {
												type = PLCType::TOTALGATES;
										}else if (line.find("GATESEQUENCE") != std::string::npos) {
												type = PLCType::GATESEQUENCE;
										}else if (line.find("GATEIOSTRUCTURE") != std::string::npos) {
												type = PLCType::GATEIOSTRUCTURE;
										}else if (line.find("GATESTRUCTURE") != std::string::npos) {
												type = PLCType::GATESTRUCTURE;
										}else if (line.find("IBUFFERS") != std::string::npos) {
												type = PLCType::IBUFFERS;
										}else if (line.find("OBUFFERS") != std::string::npos) {
												type = PLCType::OBUFFERS;
										}
								}
								else {
										ss[(int) type] << line << '\n';
								}
								std::cout << ss[1].str();
								if(stream.bad()){
										std::cout << "BAD\n";
								}else {std::cout << "\nGOOD\n";}
						}
						//return {ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str(), ss[4].str(), ss[5].str(), ss[6].str()};
				}



				int plc::getTotalLadders() const {
						return totalLadders;
				}

				void plc::setTotalLadders(int totalLadders) {
						plc::totalLadders = totalLadders;
				}

				const std::vector<int> &plc::getTotalGates() const {
						return totalGates;
				}

				void plc::setTotalGates(const std::vector<int> &totalGates) {
						plc::totalGates = totalGates;
				}

				const std::pair<int, std::string> &plc::getGateSequence() const {
						return gateSequence;
				}

				void plc::setGateSequence(const std::pair<int, std::string> &gateSequence) {
						plc::gateSequence = gateSequence;
				}

				const std::pair<int, std::string> &plc::getGateIoStructure() const {
						return gateIOStructure;
				}

				void plc::setGateIoStructure(const std::pair<int, std::string> &gateIoStructure) {
						gateIOStructure = gateIoStructure;
				}

				const std::pair<int, int> &plc::getGateStructure() const {
						return gateStructure;
				}

				void plc::setGateStructure(const std::pair<int, int> &gateStructure) {
						plc::gateStructure = gateStructure;
				}

				const std::pair<int, std::string> &plc::getIbuffers() const {
						return IBUFFERS;
				}

				void plc::setIbuffers(const std::pair<int, std::string> &ibuffers) {
						IBUFFERS = ibuffers;
				}

				const std::pair<int, std::string> &plc::getObuffers() const {
						return OBUFFERS;
				}

				void plc::setObuffers(const std::pair<int, std::string> &obuffers) {
						OBUFFERS = obuffers;
				}
}