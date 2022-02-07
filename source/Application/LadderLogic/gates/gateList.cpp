#include "gateList.h"

#include <random>

namespace ladderLogic {

				gateList::gateList() {}

				gateList::gateList(DataManager *ManagerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
								: head(nullptr), tail(nullptr), Manager(ManagerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource),
										m_UniqueGateListID(0),
										m_GatesInList(0), isModified(true), isComplete(false) {
						setm_GateListSpecificID();

						createGate_1_1IBIN_OUT_GATE(gateType::NO, &iobuffersource->IBUFFER.second[0], nullptr);
						createGate_1_0IBIN_OUT_OB(gateType::NC, nullptr, &iobuffersource->OBUFFER.second[0]);

						std::cout << *GTGOB.first.first[0] << " " << GTGOB.first.second[0] << " " << GTGOB.second[0] << std::endl;
						std::cout << *GTGIB.first.first[0] << " " << GTGIB.first.second[0] << " " << GTGIB.second[0] << std::endl;

						construct();

						std::cout << *GTGOB.first.first[0] << " " << GTGOB.first.second[0] << " " << GTGOB.second[0] << std::endl;
						std::cout << *GTGIB.first.first[0] << " " << GTGIB.first.second[0] << " " << GTGIB.second[0] << std::endl;

						std::cout << std::endl;

						std::cout << "NO GATE: OUTPUT: " << *this->head->NOgetoutput() << "; FIRST PIN:" << *this->head->NOgetfirstpin() << std::endl;
						std::cout << "NC GATE: OUTPUT: " << *this->head->next->NCgetoutput() << "; FIRST PIN: " << *this->head->next->NCgetfirstpin() << std::endl;

						//inputBufferPTR = buffer->getInputBufferPointer();
						//outputBufferPTR = buffer->getOutputBufferPointer();
						C->PTC("\nData manger hooked!");
						C->PTC("\nGate List constructed!");
						LOG->PTF("\nGATE LIST ID: ", m_GateListSpecificID, "\n");
						LOG->PTF("\nData manger hooked!\n");
//		LOG->PTF("\nUser List constructed! Type: ", UserFlag, "\n");
				}

				gateList::~gateList() {
						int gatesinlist = m_GatesInList;
						if (gatesinlist != 0) {
								for (int i = 0; i < gatesinlist; i++) {
										//std::cout << m_GatesInList << ", ";
										deleteByPos(1);
								}
						}
						C->PTC("\nGate list destructed!\n");
						LOG->PTF("\nGate list destructed!\n");
				}

				void gateList::execute() {}

				void gateList::construct() {
						if (plcsource->totalLadders < 1) {
								std::cout << "\nCANNOT CONSTRUCT LADDER. ABORTING...\n";
								return;
						} else if (plcsource->totalLadders == 1) {
								//for (int i = 0; i < plcsource->totalGates; i++) {}

								for (int i = 0; i < plcsource->gateStructure.first.size(); i++) {
										linkGTGBuffers(i);
								}
						} else if (plcsource->totalLadders > 1) {
/*								for(int i = 0; i < plcsource->totalGatesPerLadder; i++){

								}*/
						}
				}

				int *gateList::gateOUTtogateIN() {
						node *current = nullptr;
						current = this->head;
						for (int i = 0; i < m_GatesInList; i++) {
								current = current->next;
						}
						switch (current->getm_GateType()) {
								case gateType::NO:
										gatetogateIO.first.push_back(current->NOgetfirstpin());
										gatetogateIO.second.emplace_back("NO");
								case gateType::NC:
										gatetogateIO.first.push_back(current->NCgetfirstpin());
										gatetogateIO.second.emplace_back("NC");
								case gateType::AND:
										gatetogateIO.first.push_back(current->ANDgetfirstpin());
										gatetogateIO.first.push_back(current->ANDgetsecondpin());
										gatetogateIO.second.emplace_back("AND");
								case gateType::OR:
										gatetogateIO.first.push_back(current->ORgetfirstpin());
										gatetogateIO.first.push_back(current->ORgetsecondpin());
										gatetogateIO.second.emplace_back("OR");
						}
				}


				void gateList::linkGTGBuffers(int count) {

						int* linkptr1 = GTGIB.first.first[count];
						int* linkptr2 = GTGOB.first.first[count];
						std::cout << "\nbefore merge: ptr1: " << *linkptr1 << "; ptr2: " << *linkptr2 << std::endl;
						linkptr1 = linkptr2;
						std::cout << "\nafter merge: ptr1: " << *linkptr1 << "; ptr2: " << *linkptr2 << std::endl;
						if(GTGOB.second[count] == "NO"){
								*linkptr1 = 1;
						}
						GTGIB.first.first[count] = linkptr1;
						GTGOB.first.first[count] = linkptr1;
						std::cout << "\n NO gate output = " << *this->head->NOgetoutput() << std::endl;
				}

				void gateList::addGTGIB(node *newGate) {
						switch (newGate->getm_GateType()) {
								case gateType::NO:
										if (*newGate->NOgetoutput() == 2) {
												GTGOB.first.first.push_back(newGate->NOgetoutput());
												GTGOB.first.second.push_back(m_GatesInList);
												GTGOB.second.emplace_back("NO");
												return;
										}
								case gateType::NC:
										if (*newGate->NCgetoutput() == 2) {
												GTGOB.first.first.push_back(newGate->NCgetoutput());
												GTGOB.first.second.push_back(m_GatesInList);
												GTGOB.second.emplace_back("NC");
												return;
										}
								case gateType::AND:

								case gateType::OR:
								default:
										break;
						}
				}

				void gateList::addGTGOB(node *newGate) {
						switch (newGate->getm_GateType()) {
								case gateType::NO:
										if (*newGate->NOgetfirstpin() == 3) {
												GTGIB.first.first.push_back(newGate->NOgetfirstpin());
												GTGIB.first.second.push_back(m_GatesInList);
												GTGIB.second.emplace_back("NO");
												return;
										}
								case gateType::NC:
										if (*newGate->NCgetfirstpin() == 3) {
												GTGIB.first.first.push_back(newGate->NCgetfirstpin());
												GTGIB.first.second.push_back(m_GatesInList);
												GTGIB.second.emplace_back("NC");
												return;
										}
								case gateType::AND:

								case gateType::OR:
								default:
										break;
						}
				}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//std::pair<std::pair<std::vector<int*>, std::string>, std::vector<std::string>> GTGIB

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// 1 INPUT ONE OUTPUT
//IN: GATE | OUT: OB
				void gateList::createGate_1_0IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int *outputlabel) {
						switch (type) {
								case ladderLogic::gateType::NO:
										break;
								case ladderLogic::gateType::NC:
										break;
								case ladderLogic::gateType::AND:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AN AND GATE\n";
										return;
								case ladderLogic::gateType::OR:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AN OR GATE\n";
										return;
								default:
										std::cout << "\nEXCEPTION IN GATE CREATOR!\n";
										return;
						}
						if (firstPin == nullptr) {
								firstPin = new int;
								*firstPin = 3;
						}
						m_GatesInList = m_GatesInList + 1;
						auto *newGate = new node(type, firstPin, outputlabel); // Create a new user object and allocate it to heap.
						newGate->setUniqueId(getm_GatesInList());
						int i = 1;
						while (!SearchForGateDuplicates(
										newGate)) {//Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
								newGate->setUniqueId(newGate->getUniqueId() + i);
								i++;
								//C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						}
						newGate->setm_GateType(type);
						newGate->next = nullptr; //We always insert a new element into the terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
						LOG->PTF("\nNew gate created: ", type, " unique ID: ", newGate->getUniqueId(), " \n");

						if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
								this->tail->next = newGate; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
								this->tail = newGate; //Set the terminal (tail) pointer to point to the newly created object.
						} else { //This if runs only once for any newly created linked list.
								this->head = newGate; //Set initial (head) pointer to point to newly created User class object.
								this->tail = newGate; //Set terminal (tail) pointer to point to newly created User class object.
						}
						Manager->addTom_TotalLogicGates();
						addGTGOB(newGate);
						isModified = true;

						C->PTC("\n!New gate! Total gates in current script line: ", getm_GatesInList(), "; Total unique gates: ",
													Manager->getm_TotalLogicGates(), "\n");
						std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";
				}

//IN: GATE | OUT: GATE
				void gateList::createGate_1_0IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, const std::string &inputlabel,
																																															const std::string &outputlabel) {

				}

//IN: IB | OUT: OB
				void gateList::createGate_1_1IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, const std::string &inputlabel,
																																													const std::string &outputlabel) {

				}

//IN: IB | OUT: GATE
				void gateList::createGate_1_1IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int *outputlabel) {
						switch (type) {
								case ladderLogic::gateType::NO:
										break;
								case ladderLogic::gateType::NC:
										break;
								case ladderLogic::gateType::AND:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AN AND GATE\n";
										return;
								case ladderLogic::gateType::OR:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AN OR GATE\n";
										return;
								default:
										std::cout << "\nEXCEPTION IN GATE CREATOR!\n";
										return;
						}
						if (outputlabel == nullptr) {
								outputlabel = new int;
								*outputlabel = 2;
						}
						m_GatesInList = m_GatesInList + 1;
						auto *newGate = new node(type, firstPin, outputlabel); // Create a new user object and allocate it to heap.
						newGate->setUniqueId(getm_GatesInList());
						int i = 1;
						while (!SearchForGateDuplicates(
										newGate)) {//Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
								newGate->setUniqueId(newGate->getUniqueId() + i);
								i++;
								//C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						}
						newGate->setm_GateType(type);
						newGate->next = nullptr; //We always insert a new element into the terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
						LOG->PTF("\nNew gate created: ", type, " unique ID: ", newGate->getUniqueId(), " \n");

						if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
								this->tail->next = newGate; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
								this->tail = newGate; //Set the terminal (tail) pointer to point to the newly created object.
						} else { //This if runs only once for any newly created linked list.
								this->head = newGate; //Set initial (head) pointer to point to newly created User class object.
								this->tail = newGate; //Set terminal (tail) pointer to point to newly created User class object.
						}
						Manager->addTom_TotalLogicGates();
						addGTGIB(newGate);
						isModified = true;

						C->PTC("\n!New gate! Total gates in current script line: ", getm_GatesInList(), "; Total unique gates: ",
													Manager->getm_TotalLogicGates(), "\n");
						std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";
				}

//IN: GATE | OUT: GATE
				void gateList::createGate_1_GATEIN_GATEOUT(ladderLogic::gateType type, int *firstPin) {

				}

// 2 INPUTS ONE OUTPUT
//INTO GATE:
//IN: GATE;GATE | OUT: GATE
				void gateList::createGate_2_0IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																															const std::string &inputlabel) {

				}

//IN: GATE;IB; IB;GATE; | OUT: GATE
				void gateList::createGate_2_1IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																															const std::string &inputlabel) {

				}

//IN: IB;IB | OUT: GATE
				void gateList::createGate_2_2IBIN_OUT_GATE(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																															const std::string &inputlabel, const std::string &inputlabel2) {

				}

//INTO OB:
//IN: GATE;GATE | OUT: OB
				void gateList::createGate_2_0IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																													const std::string &outputlabel) {

				}

//IN: GATE;IB; IB;GATE; | OUT: OB
				void gateList::createGate_2_1IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																													const std::string &inputlabel, const std::string &outputlabel) {

				}

//IN: IB;IB | OUT: OB
				void gateList::createGate_2_2IBIN_OUT_OB(ladderLogic::gateType type, int *firstPin, int *secondPin,
																																													const std::string &inputlabel, const std::string &inputlabel2,
																																													const std::string &outputlabel) {

				}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////












				int gateList::getm_GatesInList() const {
						return m_GatesInList;
				}

				void gateList::setm_GatesInList(int m_GatesInList) {
						m_GatesInList = m_GatesInList;
				}


				int gateList::getm_GateListSpecificID() const {
						return m_GateListSpecificID;
				}

				void gateList::setm_GateListSpecificID() {
						std::random_device rd;
						std::mt19937 mt(rd());
						std::uniform_real_distribution<double> dist(1.0, 10000.0);
						int temp = 0;
						for (int i = 0; i < 30; i++) {
								temp = dist(mt);
						}
						m_GateListSpecificID = Manager->getm_TotalLogicGates() + Manager->getm_TotalScriptLines() + (42 * temp);
				}

				bool gateList::SearchForGateDuplicates(
								node *newGate) //This function will check for duplicate username <strings>; this function can will only be called by Create_User(); this function can only be called after the admin user object has been created.
				{
						node *current = nullptr; //Declare and initialize pointer current to nullptr.
						current = this->head; //Set current pointer to the initial (head) element of a linked listed.
						while (current !=
													nullptr) { //While the current pointer is not the last element (element->next == nullptr), continue.
								if (newGate->getUniqueId() ==
												current->getUniqueId()) { //If the new username matches the username of an element we return false and stop executing.
										//LOG->PTF("\nUser tried creating a new account with the same username: ", current->getUsername(), "\n");
										return false;
								}
								current = current->next; //If the username does not match with the current element goto next element.
						}
						return true; //If username does not match any element in a linked list, return true and allow a new User class object to be created.
				}

				void gateList::displayList() const {
						int count = 1; //Keep count of every user object.
						node *current; //Temporary pointer
						current = this->head;
						while (current != nullptr) { //While head (current element) is not equal nullptr (0), continue printing users.
								std::cout << "\n";
								C->PTC(count, ". ", current->getm_GateTypeByString(), "; ID: ",
															current->getUniqueId()); //Call console module to print users.
								count++; //Increment count.
								current = current->next; //Set current element to point to the next element in the list.
						}
						std::cout << std::endl;
				}

				int gateList::length() const { //Function for counting the length of a linked list.
						int length = 0; //Declare and initialize length to 0, so that we don't access randomly allocated memory.
						node *current; //Declare a pointer of user class.
						current = head; //Initialize pointer to the initial (head) element in the list.
						while (current != nullptr) { //While current pointer element does not equal to nullptr (0) keep counting.
								current = current->next; //Set current element to the next element in the linked list.
								length++; //Increment length variable.
						}
						return length; //Once counting is finished return the value of length (total amount of elements in a linked list).
				}

				void gateList::deleteHead() { //Function to delete the initial (head) pointer.
						node *New; //Declare a new pointer
						New = this->head->next; //Initialize this pointer to point to the next element of the initial (head) point.
						LOG->PTF("\nGate deleted: ", this->head->getm_GateTypeByString(), "; Unique ID: ", this->head->getUniqueId());
						delete this->head; //Delete the current initial (head) pointer; Free memory.
						this->head = New; //Set the initial (head) pointer to New pointer.
				}

				void gateList::deleteTail() { //Function to delete the terminal (tail) pointer.
						node *current; //Declare current pointer.
						node *previous; //Declare previous pointer.
						current = this->head; //Set current pointer to point to the initial (head) point of the list.
						while (current->next !=
													nullptr) { //While the next pointer of current pointer is not pointing to nullptr (0), continue.
								previous = current; //Set the previous pointer to point to the current pointer.
								current = current->next; //Set the current pointer to point to the next element in the list.
						} //Once the next element of current pointer is nullptr (0) we continue.
						previous->next = nullptr; //Set the element before the terminal (tail) element to be the last element by setting the next pointer of previous to nullptr (0).
						this->tail = previous; //Set pointer previous to terminal (tail) element of the linked list.
						LOG->PTF("\nGate deleted: ", this->head->getm_GateTypeByString(), "; Unique ID: ", this->head->getUniqueId());
						delete current;
				}

				void
				gateList::deleteByPos(int position) { //Function for deleting an element in a linked listed by a given position.
						if (position > this->length() || position <=
																																							0) { //First we must check if the entered position exceeds the total amount of elements in a linked list; if true we throw an exception and return to the function call.
								C->PTC("\n\n!EXCEPTION! TRYING TO DELETE AN OUT OF BOUNDS GATE\n\n");
								LOG->PTF("\n!EXCEPTION! TRYING TO DELETE AN OUT OF BOUNDS GATE\n");
								return;
						} else if (position ==
																	1) { //If the entered position is 1, that means we want to delete the initial (head) element of the linked list.
								deleteHead(); //Call deleteHead function.
						} else if (this->length() ==
																	position) { //If the entered position is the last element in the linked list, that means we want to delete the terminal (tail) element of the linked list.
								deleteTail(); //Call deleteTail function.
						} else { //If we want to delete any element in between the initial (head) and the terminal (tail) elements we continue.
								deletePos(position); //Call the deletePos function.
						}
						Manager->subtractFromm_TotalLogicGates();
						m_GatesInList = m_GatesInList - 1;
						C->PTC("\n!GATE DELETED! Total gates in current script line: ", m_GatesInList, "\n"); //For debugging.
				}

				void gateList::deletePos(
								int position) { //This function only runs if it is called by deleteByPos function. This function only runs if the specified position is not the first or the last element in a given linked list.
						node *current; //Declare a current pointer.
						node *previous; //Declare a previous pointer.
						current = this->head; //Set current pointer to point to the initial (head) element.
						for (int i = 1; i <
																						position; i++) { //Start from the first initial (head) element of linked list and loop until the given position.
								previous = current; //Set the previous pointer to point to the current element in the linked list.
								current = current->next; //Set the current pointer to point to the next element in the linked list.
						} //Once we find the next element of the element that we want to delete from the list, we continue.
						previous->next = current->next; //Set the next pointer of the previous element to point to the next element of the current pointer.
						LOG->PTF("\nGate deleted: ", this->head->getm_GateTypeByString(), "; Unique ID: ", this->head->getUniqueId());
						delete current; //Delete current element.
				}

				int gateList::checkGateType(node *current) {
						switch (current->getm_GateType()) {
								case ladderLogic::gateType::AND:
										return 0;
								case ladderLogic::gateType::OR:
										return 1;
								case ladderLogic::gateType::NO:
										return 2;
								case ladderLogic::gateType::NC:
										return 3;
								default:
										std::cout << "\nEXCEPTION IN checkGateType!\n";
										break;
						}
				}
}

/*void
gateList::constructGates(std::vector<int> INSTRUCTIONSET, std::string INPUTBUFFER[], std::string OUTPUTBUFFER[]) {
		//MIGHT CAUSE POTENTIAL MEMORY CRASHES//
		instructionSet = INSTRUCTIONSET;
		node *current = nullptr;
		node *previous = nullptr;
		current = this->head;
		for (int i = 0; i < m_GatesInList; i++) {
				if (current->next == nullptr) {
						std::cout << "\nOUT OF BOUNDS NODE\n";
						return;
				}
				previous = current;
				current = current->next;
		}
		int returnOperation = checkGateType(current);
//		std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
//		std::cout << current->getOutput();

		isModified = true;
}*/
/*				void gateList::executeAllGates() {
						node *current = nullptr;
						node *previous = nullptr;
						current = this->head;
						bool unsginedGate = false;
						for (int i = 0; i < m_GatesInList; i++) {
								if (!current->isAssigned) {
										std::cout << "\nCANNOT EXECUTE WHILE ALL GATES HAVE NOT BEEN ASSIGNED";
										std::cout << "\nUnsigned gate: " << current->getm_GateTypeByString() << " at script line position: " << i
																				<< "; node ID: " << current->getUniqueId() << std::endl;
								}
								previous = current;
								current = current->next;
						}
						if (unsginedGate) {
								return;
						}
						//this->head;
				}*/

/*				void gateList::switchINPUT() {
						if (INPUT) {
								INPUT = false;
						} else if (!INPUT) {
								INPUT = true;
						}
				}

				void gateList::switchOUTPUT() {
						if (OUTPUT) {
								OUTPUT = false;
						} else if (!OUTPUT) {
								OUTPUT = true;
						}
				}*/

/*				void gateList::executeSpecificGateLogic(int nodeselect) {
						node *current;
						node *previous;
						current = this->head;
						for (int i = 0; i < nodeselect; i++) {
								if (current->next == nullptr) {
										std::cout << "\nOUT OF BOUNDS NODE\n";
										return;
								}
								previous = current;
								current = current->next;
						}
						int returnOperation = checkGateType(current);
//		std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
//		std::cout << current->getOutput();
						switch (returnOperation) {

								case 0:
										std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
										//std::cout << current->executeAndGateLogic();
										break;
								case 1:
										std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
										//std::cout << current->executeOrGateLogic();
										break;
								case 2:
										std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
										//std::cout << current->executeNormallyOpenGateLogic();
										break;
								case 3:
										std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
										//std::cout << current->executeNormallyCloseGateLogic();
										break;
								default:
										std::cout << "\n EXCEPTION IN EXECUTING GATE LOGIC \n";
						}
				}*/

/*				void gateList::linkPLCandBuffers() {
						//BUFFER INPUTS:
						std::cout << std::endl;
						for (int i = 0; i < iobuffersource->getTotalinputlabels(); i++) {
								INPUTS.first.push_back(iobuffersource->getIbufferState(i));
								INPUTS.second.push_back(iobuffersource->getIbufferLabel(i));
								//std::cout << i + 1 << ". " << *INPUTS.first[i] << " : " << *INPUTS.second[i] << std::endl;
						}
						//BUFFER OUTPUTS:
						for (int i = 0; i < iobuffersource->getTotaloutputlabels(); i++) {
								OUTPUTS.first.push_back(iobuffersource->getObufferState(i));
								OUTPUTS.second.push_back(iobuffersource->getObufferLabel(i));
								//std::cout << i + 1 << ". " << *OUTPUTS.first[i] << " : " << *OUTPUTS.second[i] << std::endl;
						}

				}*/


/*				void gateList::createGate(
								ladderLogic::gateType type,
								int *firstPin, const std::string &inputlabel, const std::string &outputlabel) {
						//Function for creating a new User class object and inserting it into a linked list. Pass by an instantiated list, along with username and password.
						switch (type) {
								case ladderLogic::gateType::NO:
										break;
								case ladderLogic::gateType::NC:
										break;
								case ladderLogic::gateType::AND:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO AND GATE\n";
										return;
								case ladderLogic::gateType::OR:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN ONE INPUT TO OR GATE\n";
										return;
								default:
										std::cout << "\nEXCEPTION IN GATE CREATOR!\n";
										return;
						}
						auto *newGate = new node(type, firstPin); // Create a new user object and allocate it to heap.
						m_GatesInList = m_GatesInList + 1;
						newGate->setUniqueId(getm_GatesInList());
						int i = 1;
						while (!SearchForGateDuplicates(
										newGate)) {//Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
								newGate->setUniqueId(newGate->getUniqueId() + i);
								i++;
								//C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						}
						newGate->setm_GateType(type);
						newGate->next = nullptr; //We always insert a new element into the terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
						LOG->PTF("\nNew gate created: ", type, " unique ID: ", newGate->getUniqueId(), " \n");

						if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
								this->tail->next = newGate; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
								this->tail = newGate; //Set the terminal (tail) pointer to point to the newly created object.
						} else { //This if runs only once for any newly created linked list.
								this->head = newGate; //Set initial (head) pointer to point to newly created User class object.
								this->tail = newGate; //Set terminal (tail) pointer to point to newly created User class object.
						}
						Manager->addTom_TotalLogicGates();
						isModified = true;

						C->PTC("\n!New gate! Total gates in current script line: ", getm_GatesInList(), "; Total unique gates: ",
													Manager->getm_TotalLogicGates(), "\n");
						std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";
				}

				void gateList::createGate(
								ladderLogic::gateType type, int *firstPin,
								int *secondPin, const std::string &inputlabel, const std::string &outputlabel) {
						//Function for creating a new User class object and inserting it into a linked list. Pass by an instantiated list, along with username and password.
						switch (type) {
								case ladderLogic::gateType::NO:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY OPEN GATE\n";
										return;
								case ladderLogic::gateType::NC:
										std::cout << "\nEXCEPTION: CANNOT ASSIGN TWO INPUTS TO NORMALLY CLOSED GATE\n";
										return;
								case ladderLogic::gateType::AND:
										break;
								case ladderLogic::gateType::OR:
										break;
								default:
										std::cout << "\nEXCEPTION IN GATE CREATOR!\n";
										return;
						}
						auto *newGate = new node(type, firstPin, secondPin); // Create a new user object and allocate it to heap.
						m_GatesInList = m_GatesInList + 1;
						newGate->setUniqueId(getm_GatesInList());
						int i = 1;
						while (!SearchForGateDuplicates(
										newGate)) {//Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
								newGate->setUniqueId(newGate->getUniqueId() + i);
								i++;
								//C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						}
						newGate->setm_GateType(type);
						newGate->next = nullptr; //We always insert a new element into th
						m_GatesInList = 2;e terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
						LOG->PTF("\nNew gate created: ", type, " unique ID: ", newGate->getUniqueId(), " \n");

						if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
								this->tail->next = newGate; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
								this->tail = newGate; //Set the terminal (tail) pointer to point to the newly created object.
						} else { //This if runs only once for any newly created linked list.
								this->head = newGate; //Set initial (head) pointer to point to newly created User class object.
								this->tail = newGate; //Set terminal (tail) pointer to point to newly created User class object.
						}
						Manager->addTom_TotalLogicGates();
						isModified = true;

						C->PTC("\n!New gate! Total gates in current script line: ", getm_GatesInList(), "; Total unique gates: ",
													Manager->getm_TotalLogicGates(), "\n");
						std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";
				}*/