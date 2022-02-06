#include "instructionSet.h"

#include <assert.h>

namespace ladderLogic {
	instructionSet::instructionSet(DataManager& managerInstance)
		: Manager(&managerInstance), noGates(0), ncGates(0), andGates(0), orGates(0), totalGates(0), isempty(false),
		layout(0), firstuserinput(false), gatesnotset(0), onecyclecompleted(false), filternoGates(0), filterncGates(0), filterandGates(0), filterorGates(0) {
		userinput.push_back(0);
	}

	bool instructionSet::inputvalidation(int gate) {
		if (firstuserinput
			&& !onecyclecompleted
			) {
			int count = 0;
			if (gate == 1) {
				for (int i = 0; i <= noGates; i++) {
					for (int j = 0; j < userinput.size(); j++) {
						if (noGateLocations[i] == userinput[j] - 1) {
							filternoGates = filternoGates + 1;
							count++;
							if (count == filternoGates) {
								onecyclecompleted = true;
							}
							return true;
						}
					}
				}
			}
			if (gate == 2) {
				for (int i = 0; i <= ncGates; i++) {
					for (int j = 0; j < userinput.size(); j++) {
						if (ncGateLocations[i] == userinput[j] - 1) {
							filterncGates = filterncGates + 1;
							count++;
							if (count == filterncGates) {
								onecyclecompleted = true;
							}
							return true;
						}
					}
				}
			}
			if (gate == 3) {
				for (int i = 0; i <= andGates; i++) {
					for (int j = 0; j < userinput.size(); j++) {
						if (andGateLocations[i] == userinput[j] - 1) {
							filterandGates = filterandGates + 1;
							count++;
							if (count == filterandGates) {
								onecyclecompleted = true;
							}
							return true;
						}
					}
				}
			}
			if (gate == 4) {
				for (int i = 0; i <= orGates; i++) {
					for (int j = 0; j < userinput.size(); j++) {
						if (orGateLocations[i] == userinput[j] - 1) {
							filterorGates = filterorGates + 1;
							count++;
							if (count == filterorGates) {
								onecyclecompleted = true;
							}
							return true;
						}
					}
				}
			}
			return false;
		}
	}

	void instructionSet::createInstructionSet() {
		C->PTC("\nGENERATE INSTRUCTION SET\n");
		C->PTC("\nSTATIC PRESET: NC NC NC\n");
		//int totalscriptlines = Manager->getm_TotalScriptLines();

		bool emptyGen = false;

		std::string pin1type, pin2type; //IB (input buffer) or GATE (from other gate)
		std::string pincombo;

		int inputFromInputBuffer = 0;

		//create X amount of Y gate types
		bool loop = true;
		while (loop) {
			C->PTC("CHOOSE GATE TYPE (0 to exit):\n");
			C->PTC("1. NO\n");
			C->PTC("2. NC\n");
			C->PTC("3. AND\n");
			C->PTC("4. OR\n");
			switch (C->Get_Input_By_INT(0, 4)) {
			case 0:
				C->PTC("GENERATING INSTRUCTION SET...\n");
				if (INSTRUCTIONSET.first.first.empty() && INSTRUCTIONSET.second.empty()) {
					C->PTC("INSTRUCTION SET IS EMPTY, ABORTING...\n");
					INSTRUCTIONSET.first.first.clear();
					INSTRUCTIONSET.first.second.clear();
					INSTRUCTIONSET.second.clear();
					isempty = true;
					assert(!isempty);
					return;
				}
				loop = false;
				break;
				//return INSTRUCTIONSET;
			case 1:
				C->PTC("IMPORTING NO GATE\n");
				totalGates++;
				noGates = noGates + 1;
				INSTRUCTIONSET.first.first.push_back(1);
				break;
			case 2:
				C->PTC("IMPORTING NC GATE\n");
				totalGates++;
				ncGates = ncGates + 1;
				INSTRUCTIONSET.first.first.push_back(2);
				break;
			case 3:
				C->PTC("IMPORTING AND GATE\n");
				totalGates++;
				andGates = andGates + 1;
				INSTRUCTIONSET.first.first.push_back(3);
				break;
			case 4:
				C->PTC("IMPORTING OR GATE\n");
				totalGates++;
				orGates = orGates + 1;
				INSTRUCTIONSET.first.first.push_back(4);
				break;
			default:
				break;
			}
		}
		//save the location of gates that are stored within the std::pair datatype
		for (int i = 0; i < INSTRUCTIONSET.first.first.size(); i++) {
			switch (INSTRUCTIONSET.first.first[i]) {
			case 1:
				//std::cout << "\n" << i + 1 << " NO GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: TRUE)\n";
				noGateLocations.push_back(i);
				break;
			case 2:
				//std::cout << "\n" << i + 1 << " NC GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: FALSE)\n";
				ncGateLocations.push_back(i);
				break;
			case 3:
				//std::cout << "\n" << i + 1 << " AND GATE (2 INPUTS | 1 OUTPUT)\n";
				andGateLocations.push_back(1);
				break;
			case 4:
				//std::cout << "\n" << i + 1 << " OR GATE (2 INPUTS | 1 OUTPUT)\n";
				orGateLocations.push_back(1);
				break;
			}
		}
		onecyclecompleted = false;
		//set layout of gates
		C->PTC("Select gates layout:\n");
		C->PTC("1. Single File Layout\n");
		C->PTC("2. NOT AVAILABLE YET Up Down (2 rows) Layout\n");
		switch (C->Get_Input_By_INT(1, 2)) {
		case 1:
			layout = 1;
			INSTRUCTIONSET.second.push_back("1|");
			break;
		case 2:
			layout = 2;
			INSTRUCTIONSET.second.push_back("2|");
			break;
		}
		//depending on the layout construct gate order
								//static layout
		if (layout == 1) {
			C->PTC("Available gates:\n");
			for (int i = 0; i < INSTRUCTIONSET.first.first.size(); i++) {
				for (int j = 0; j < INSTRUCTIONSET.first.first.size(); j++) {
					//int count = 0;
					switch (INSTRUCTIONSET.first.first.at(j)) {
					case 1:
						if (inputvalidation(1)) { break; }
						else {
							std::cout << "\n" << j + 1 << ". NO GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: TRUE)\n";
							break;
						}
					case 2:
						if (inputvalidation(2)) { break; }
						else {
							std::cout << "\n" << j + 1 << ". NC GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: FALSE)\n";
							break;
						}
					case 3:
						if (inputvalidation(3)) { break; }
						else {
							std::cout << "\n" << j + 1 << ". AND GATE (2 INPUTS | 1 OUTPUT)\n";
							break;
						}
					case 4:
						if (inputvalidation(4)) { break; }
						else {
							std::cout << "\n" << j + 1 << ". OR GATE (2 INPUTS | 1 OUTPUT)\n";
							break;
						}
					default:
						break;
					}
				}

				if (gatesnotset == 0) {
					C->PTC("Select the first gate:\n");
					//C->Get_Input_By_INT(1, 2);
					int input = C->Get_Input_By_INT(1, totalGates);
					userinput[i] = input;
					firstuserinput = true;
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + std::to_string(input);
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + ";";
					std::cout << INSTRUCTIONSET.second[0];
					gatesnotset++;
				}
				else if (gatesnotset > 0 && gatesnotset < totalGates) {
					int input = 0;
					bool inputloop = true;
					while (inputloop) {
						C->PTC("Select the next gate:\n");
						input = C->Get_Input_By_INT(1, totalGates);
						for (int j = 0; j < userinput.size(); j++) {
							if (input == userinput[j]) {
								C->PTC("CANNOT ADD AN ALREADY ASSIGNED GATE\n");
							}
							else {
								inputloop = false;
								break;
							}
						}
					}
					userinput.push_back(input);
					onecyclecompleted = false;
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + std::to_string(input);
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + ";";
					std::cout << INSTRUCTIONSET.second[0];
					gatesnotset++;
				}
				else//(gatesnotset == INSTRUCTIONSET.first.first.size())
				{
					int input = 0;
					bool inputloop = true;
					while (inputloop) {
						C->PTC("Select the last gate:\n");
						input = C->Get_Input_By_INT(1, totalGates);
						for (int j = 0; j < userinput.size(); j++) {
							if (input == userinput[j]) {
								C->PTC("CANNOT ADD AN ALREADY ASSIGNED GATE\n");
							}
							else {
								inputloop = false;
								break;
							}
						}
					}
					onecyclecompleted = false;
					userinput.push_back(input);
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + std::to_string(input);
					INSTRUCTIONSET.second[0] = INSTRUCTIONSET.second[0] + ";";
					std::cout << INSTRUCTIONSET.second[0];
					gatesnotset++;
				}
			}
		}

		/*	if (layout == 1) {
					while (gatesnotset != 0) {
							C->PTC("Available gates:\n");
							std::pair<int, int> countandlocation;
							for (int i = 0; i < INSTRUCTIONSET.first.first.size(); i++) {
									int count = 0;
									for (int j = 0; j < noGates; j++){
											count++;
											std::cout << "\n" << count << " NO GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: TRUE)\n";
									}
									for (int j = 0; j < ncGates; j++){
											count++;
											std::cout << "\n" << count << " NC GATE (1 INPUT | 1 OUTPUT | DEFAULT OUTPUT STATE: FALSE)\n";
									}
									for (int j = 0; j < andGates; j++){
											count++;userinput[i] = input;
											std::cout << "\n" << count << " AND GATE (2 INPUTS | 1 OUTPUT)\n";
									}
									for (int j = 0; j < orGates; j++){
											count++;
											std::cout << "\n" << count << " OR GATE (2 INPUTS | 1 OUTPUT)\n";
									}
							}
							C->PTC("Select which gate is first\n");
							C->Get_Input_By_INT();

							gatesnotset = gatesnotset - 1;
					}
					INSTRUCTIONSET.second.push_back("|");
			}

			//add later
			if (layout == 2) {
					C->PTC("LAYOUT 2 DOES NOTHING.\n");
			}
			void something();
			//if(totalscriptlines > 0){}else if (totalscriptlines == 0){}
			if (andGates > 0) {
					C->PTC("TOTAL AND GATES: ", andGates, " SET INPUT FOR EACH GATE:\n");
					for (int i = 0; i < andGateLocations.size(); i++) {
							C->PTC("PIN 1 TYPE:\n");
							int setpin = 0;
							while (setpin != 1) {
									C->PTC("1. IB (Input Buffer)\n");
									C->PTC("2. GATE\n");
									switch (C->Get_Input_By_INT(1, 2)) {
											case 1:
													pincombo = "IB";
													setpin++;
											case 2:
													pincombo = "GATE";
													setpin++;
									}
							}
							pincombo += "|";
							//split up with sign e.g. |
							setpin = 0;
							C->PTC("PIN 2 TYPE:\n");
							while (setpin != 1) {
									C->PTC("1. IB (Input Buffer)\n");
									C->PTC("2. GATE\n");
									switch (C->Get_Input_By_INT(1, 2)) {
											case 1:
													pincombo += "IB";
													setpin++;
											case 2:
													pincombo += "GATE";
													setpin++;
									}
							}


					}
			}*/


		return;
	}
}