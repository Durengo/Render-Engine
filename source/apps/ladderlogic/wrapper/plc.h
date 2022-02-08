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
								plc(DataManager *managerInstance, const std::string &Filepath);

								~plc();

								void printAllInfo();

								int totalLadders;

								int totalGates;

								std::vector<int> totalGatesPerLadder;

								std::pair<std::vector<int>, std::vector<std::string>> gateSequence;

								int gateSequenceBranching;

								//Pair: first position gate number; second position pair: (1) input, (2) output
								std::pair<std::vector<int>, std::pair<std::vector<std::string>, std::vector<std::string>>> gateIOStructure;

								//X>0 indicates that this gates goes into the outputbuffer
								std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::pair<std::vector<int>, std::vector<std::string>>> gateStructure;

								std::pair<std::vector<int>, std::vector<std::string>> IBUFFERS;

								int IBUFFERAMOUNT;

								std::pair<std::vector<int>, std::vector<std::string>> OBUFFERS;

								int OBUFFERAMOUNT;

				protected:
								DataManager *Manager;

								std::string filepath;

								PLCSOURCE parsePLC(const std::string &Filepath);

								void setPLC(PLCSOURCE &plcsource);

								void settotalladders(PLCSOURCE &plcsource);

								void settotalgates(PLCSOURCE &plcsource);

								void setgatesequence(PLCSOURCE &plcsource);

								void setgateiostructure(PLCSOURCE &plcsource);

								void setgatestructure(PLCSOURCE &plcsource);

								void setibuffers(PLCSOURCE &plcsource);

								void setobuffers(PLCSOURCE &plcsource);
				};
}