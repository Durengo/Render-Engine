#pragma once

#include <iostream>

#include <iostream>
#include <vector>

#include "../utils/DataManager.h"

namespace PLC {
				struct PLCSOURCE {
								std::string TOTALLADDERS;
								std::string TOTALGATES;
								std::string GATESEQUENCE;
								std::string GATEIOSTRUCTURE;
								std::string GATESTRUCTURE;
								std::string IBUFFERS;
								std::string OBUFFERS;
				};

				class plc {
				public:
								plc(DataManager &managerInstance, const std::string& Filepath);

								~plc();

								void passInfo();

								int getTotalLadders() const;

								void setTotalLadders(int totalLadders);

								const std::vector<int> &getTotalGates() const;

								void setTotalGates(const std::vector<int> &totalGates);

								const std::pair<int, std::string> &getGateSequence() const;

								void setGateSequence(const std::pair<int, std::string> &gateSequence);

								const std::pair<int, std::string> &getGateIoStructure() const;

								void setGateIoStructure(const std::pair<int, std::string> &gateIoStructure);

								const std::pair<int, int> &getGateStructure() const;

								void setGateStructure(const std::pair<int, int> &gateStructure);

								const std::pair<int, std::string> &getIbuffers() const;

								void setIbuffers(const std::pair<int, std::string> &ibuffers);

								const std::pair<int, std::string> &getObuffers() const;

								void setObuffers(const std::pair<int, std::string> &obuffers);

				private:
								DataManager *Manager;
								std::string filepath;
								PLCSOURCE parsePLC(const std::string &Filepath);
								int totalLadders;
								std::vector<int> totalGates;
								std::pair<int, std::string> gateSequence;
								std::pair<int, std::string> gateIOStructure;
								std::pair<int, int> gateStructure;
								std::pair<int, std::string> IBUFFERS;
								std::pair<int, std::string> OBUFFERS;
				};
}