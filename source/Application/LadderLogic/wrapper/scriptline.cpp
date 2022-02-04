#include "scriptline.h"

namespace ladderLogic {

				scriptline::scriptline(DataManager &managerInstance, ladderLogic::IOBuffer *buffer)
								: gateList(&managerInstance, buffer), managerInstance(&managerInstance), ioBuffer(buffer),
										isComplete(false), inputLabel("X0"), outputLabel("Q0"), input(false), output(false)
				//										isActive(true),
				{
				}


				scriptline::~scriptline() {
						std::cout << "\ndecon\n";
				}

				void scriptline::execute() {
						if (isComplete) {
								return;
						}

						toggleisComplete();
				}

				void scriptline::toggleisComplete() {
						if (isComplete) {
								isComplete = false;
						} else if (!isComplete) {
								isComplete = true;
						}
				}

				std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<std::string>>
				scriptline::createInstructionSet() {
						//std::pair<std::vector<int>, std::vector<std::string>> INSTRUCTIONSET;
						std::pair<std::pair<std::vector<int>, std::vector<std::string>>, std::vector<std::string>> INSTRUCTIONSET;
						C->PTC("\nGENERATE INSTRUCTION SET\n");
						C->PTC("\nSTATIC PRESET: NC NC NC\n");
						//int totalscriptlines = Manager->getm_TotalScriptLines();

						bool loop = true;
						bool emptyGen = false;

						int noGates = 0;
						int ncGates = 0;
						int andGates = 0;
						int orGates = 0;

						std::vector<int> noGateLocations;
						std::vector<int> ncGateLocations;
						std::vector<int> andGateLocations;
						std::vector<int> orGateLocations;

						std::string pin1type, pin2type; //IB (input buffer) or GATE (from other gate)
						std::string pincombo;

						int inputFromInputBuffer = 0;

						while (loop) {
								C->PTC("CHOOSE GATE TYPE:\n");
								C->PTC("1. NO\n");
								C->PTC("2. NC\n");
								C->PTC("3. AND\n");
								C->PTC("4. OR\n");
								switch (C->Get_Input_By_INT(0, 4)) {
										case 0:
												C->PTC("GENERATING INSTRUCTION SET...\n");
												if (INSTRUCTIONSET.first.first.empty() && INSTRUCTIONSET.second.empty()) {
														C->PTC("INSTRUCTION SET IS EMPTY, ABORTING...\n");
														emptyGen = true;
														loop = false;
												}
												loop = false;
												break;
												//return INSTRUCTIONSET;
										case 1:
												C->PTC("IMPORTING NO GATE\n");
												INSTRUCTIONSET.first.first.push_back(1);
										case 2:
												C->PTC("IMPORTING NC GATE\n");
												INSTRUCTIONSET.first.first.push_back(2);
										case 3:
												C->PTC("IMPORTING AND GATE\n");
												INSTRUCTIONSET.first.first.push_back(3);
										case 4:
												C->PTC("IMPORTING OR GATE\n");
												INSTRUCTIONSET.first.first.push_back(4);
										default:
												break;
								}
								for (int i = 0; i < INSTRUCTIONSET.first.first.size(); i++) {
										switch (INSTRUCTIONSET.first.first.at(i)) {
												case 1:
														std::cout << "\n" << i + 1 << " NO GATE (1 INPUT | 1 OUTPUT | DEFAULT STATE: TRUE)\n";
														noGates = noGates + 1;
														noGateLocations.push_back(i);
														break;
												case 2:
														std::cout << "\n" << i + 1 << " NC GATE (1 INPUT | 1 OUTPUT | DEFAULT STATE: FALSE)\n";
														ncGates = ncGates + 1;
														ncGateLocations.push_back(i);
														break;
												case 3:
														std::cout << "\n" << i + 1 << " AND GATE (2 INPUTS | 1 OUTPUT)\n";
														andGates = andGates + 1;
														andGateLocations.push_back(1);
														break;
												case 4:
														std::cout << "\n" << i + 1 << " OR GATE (2 INPUTS | 1 OUTPUT)\n";
														orGates = orGates + 1;
														orGateLocations.push_back(1);
														break;
										}
								}
						}
						if (emptyGen) {
								INSTRUCTIONSET.first.first.clear();
								INSTRUCTIONSET.first.second.clear();
								INSTRUCTIONSET.second.clear();
								return INSTRUCTIONSET;
						}
						/*decide order of gates here
						up? down? first? last?
						process of selection: from left to right: 1. pick which gate is first >
						2. pick layout single / (if adding this layout would use last available gate, then this option is not available)UP-DOWN(2X1) >
					 3. last gate is chosen automatically.

						GENERAL SCRIPTLINE LAYOUT - MANY INPUTS (FROM INPUT BUFFER OR INNER GATES) - ONLY ONE OUTPUT.
*/

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
						}


						return INSTRUCTIONSET;
				}

				void scriptline::setUniqueID(int uniqueid) {
						uniqueID = uniqueid;
				}

				int scriptline::getUniqueID() const {
						return uniqueID;
				}

				void scriptline::onRender(IOBuffer &buffer) {

				}

				void scriptline::onImGuiRender() {

				}


}