#pragma once

#include <iostream>
#include <vector>

#include "../utils/DataManager.h"

/*decide order of gates here
up? down? first? last?
process of selection: from left to right: 1. pick which gate is first >
2. pick layout single / (if adding this layout would use last available gate, then this option is not available)UP-DOWN(2X1) >
3. last gate is chosen automatically.

GENERAL SCRIPTLINE LAYOUT - MANY INPUTS (FROM INPUT BUFFER OR INNER GATES) - ONLY ONE OUTPUT.
*/

namespace ladderLogic {
	class instructionSet {
	public:
		instructionSet(DataManager& managerInstance);

		bool inputvalidation(int gate);

		void createInstructionSet();

	private:
		DataManager* Manager;
		std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<std::string>> INSTRUCTIONSET;
		int noGates;
		int ncGates;
		int andGates;
		int orGates;
		int totalGates;
		std::vector<int> noGateLocations;
		std::vector<int> ncGateLocations;
		std::vector<int> andGateLocations;
		std::vector<int> orGateLocations;
		bool isempty;
		int layout;
		bool firstuserinput;
		int gatesnotset;
		bool onecyclecompleted;
		int filternoGates;
		int filterncGates;
		int filterandGates;
		int filterorGates;
		std::vector<int> userinput;
	};
}