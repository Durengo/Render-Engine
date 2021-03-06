#include "ladderlist.h"

#include <random>

namespace ladderLogic {

				//ladderlist::ladderlist() {}

/*				ladderlist::ladderlist(DataManager *ManagerInstance, PLC::plc *PLCSource, PLC::IOBuffer *IOBuffersource)
								: head(nullptr), tail(nullptr), Manager(ManagerInstance), plcsource(PLCSource), iobuffersource(IOBuffersource),
										m_UniqueGateListID(0),
										m_GatesInList(0), isModified(true), isComplete(false) {
						setm_GateListSpecificID();

						//create node


						C->PTC("\nData manger hooked!");
						C->PTC("\nGate List constructed!");
						LOG->PTF("\nGATE LIST ID: ", m_GateListSpecificID, "\n");
						LOG->PTF("\nData manger hooked!\n");
				}*/

				ladderlist::ladderlist(DataManager *ManagerInstance)
								: head(nullptr), tail(nullptr), Manager(ManagerInstance),
										m_UniqueGateListID(0),
										m_GatesInList(0), isModified(true), isComplete(false), NOgates(0), NCgates(0), ANDgates(0), ORgates(0) {
						setm_GateListSpecificID();

						//create node


						C->PTC("\nData manger hooked!");
						C->PTC("\nGate List constructed!");
						LOG->PTF("\nGATE LIST ID: ", m_GateListSpecificID, "\n");
						LOG->PTF("\nData manger hooked!\n");
				}

				ladderlist::~ladderlist() {
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

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
				void ladderlist::createGate(ladderLogic::gateType type) {
/*						switch (type) {
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
						}*/
/*						if (firstPin == nullptr) {
								firstPin = new int;
								*firstPin = 3;
						}*/
						m_GatesInList = m_GatesInList + 1;
						if(type == ladderLogic::gateType::NO){
								NOgates = NOgates + 1;
						}else if(type == ladderLogic::gateType::NC){
								NCgates = NCgates + 1;
						}else if(type == ladderLogic::gateType::AND){
								ANDgates = ANDgates + 1;
						}else if(type == ladderLogic::gateType::OR){
								ORgates = ORgates + 1;
						}else if(type == ladderLogic::gateType::NONE){
								std::cout << "\nEXCEPTION IN GATE CREATOR!\n";
						}
						auto *newGate = new node(type); // Create a new user object and allocate it to heap.
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








				lgates::NO *ladderlist::getNOgatebypos(int pos) {
						node *current = nullptr;
						current = this->head;
						if (pos >= this->length() || pos < 0) {
								std::cout << "OUT OF BOUNDS GET NO GATE PTR. RETURNING NULLPTR\n";
								return nullptr;
						}
						if (pos == 0 && current->getm_GateType() == gateType::NO) {
								switch (current->getm_GateType()) {
										case gateType::NONE:
												std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//NO
										case gateType::NO:
												return current->NOgate;
												//NC
										case gateType::NC:
												std::cout << "GATE TYPE NC IN GETNOGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//AND
										case gateType::AND:
												std::cout << "GATE TYPE AND IN GETNOGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//OR
										case gateType::OR:
												std::cout << "GATE TYPE OR IN GETNOGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
								}
						}
						for (int i = 0; i < pos; i++) {
								current = current->next;
								if (current->getm_GateType() == gateType::NO) {
										switch (current->getm_GateType()) {
												case gateType::NONE:
														std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NO
												case gateType::NO:
														return current->NOgate;
														//NC
												case gateType::NC:
														std::cout << "GATE TYPE NC IN GETNOGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//AND
												case gateType::AND:
														std::cout << "GATE TYPE AND IN GETNOGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//OR
												case gateType::OR:
														std::cout << "GATE TYPE OR IN GETNOGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
										}
								}
						}
				}
				lgates::NC *ladderlist::getNCgatebypos(int pos) {
						node *current = nullptr;
						current = this->head;
						if (pos >= this->length() || pos < 0) {
								std::cout << "OUT OF BOUNDS GET NO GATE PTR. RETURNING NULLPTR\n";
								return nullptr;
						}
						if (pos == 0 && current->getm_GateType() == gateType::NC) {
								switch (current->getm_GateType()) {
										case gateType::NONE:
												std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//NO
										case gateType::NO:
												std::cout << "GATE TYPE NO IN GETNCGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//NC
										case gateType::NC:
												return current->NCgate;
												//AND
										case gateType::AND:
												std::cout << "GATE TYPE AND IN GETNCGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
												//OR
										case gateType::OR:
												std::cout << "GATE TYPE OR IN GETNCGATE. ABORTING. RETURNING NULLPTR";
												return nullptr;
								}
						}
						for (int i = 0; i < pos; i++) {
								current = current->next;
								if (current->getm_GateType() == gateType::NC) {
										switch (current->getm_GateType()) {
												case gateType::NONE:
														std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NO
												case gateType::NO:
														std::cout << "GATE TYPE NO IN GETNCGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NC
												case gateType::NC:
														return current->NCgate;
														//AND
												case gateType::AND:
														std::cout << "GATE TYPE AND IN GETNOGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//OR
												case gateType::OR:
														std::cout << "GATE TYPE OR IN GETNOGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
										}
								}
						}
				}
						lgates::AND *ladderlist::getANDgatebypos(int pos) {
								node *current = nullptr;
								current = this->head;
								if (pos >= this->length() || pos < 0) {
										std::cout << "OUT OF BOUNDS GET NOT GATE PTR. RETURNING NULLPTR\n";
										return nullptr;
								}
								if (pos == 0 && current->getm_GateType() == 3) {
										switch (current->getm_GateType()) {
												case gateType::NONE:
														std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NO
												case gateType::NO:
														std::cout << "GATE TYPE NO IN GETANDGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NC
												case gateType::NC:
														std::cout << "GATE TYPE NC IN GETANDGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//AND
												case gateType::AND:
														return current->ANDgate;
														//OR
												case OR:
														std::cout << "GATE TYPE OR IN GETANDGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
										}
								}
								for (int i = 0; i < pos; i++) {
										current = current->next;
										if (current->getm_GateType() == 3) {
												switch (current->getm_GateType()) {
														case gateType::NONE:
																std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//NO
														case gateType::NO:
																std::cout << "GATE TYPE NO IN GETANDGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//NC
														case gateType::NC:
																std::cout << "GATE TYPE NC IN GETANDGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//AND
														case gateType::AND:
																return current->ANDgate;
																//OR
														case gateType::OR:
																std::cout << "GATE TYPE OR IN GETANDGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
												}
										}
								}
						}
						lgates::OR *ladderlist::getORgatebypos(int pos) {
								node *current = nullptr;
								current = this->head;
								if (pos >= this->length() || pos < 0) {
										std::cout << "OUT OF BOUNDS GET NOT GATE PTR. RETURNING NULLPTR\n";
										return nullptr;
								}
								if (pos == 0 && current->getm_GateType() == 4) {
										switch (current->getm_GateType()) {
												case gateType::NONE:
														std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NO
												case gateType::NO:
														std::cout << "GATE TYPE NO IN GETORGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//NC
												case gateType::NC:
														std::cout << "GATE TYPE NC IN GETORGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//AND
												case gateType::AND:
														std::cout << "GATE TYPE AND IN GETANDGATE. ABORTING. RETURNING NULLPTR";
														return nullptr;
														//OR
												case gateType::OR:
														return current->ORgate;
										}
								}
								for (int i = 0; i < pos; i++) {
										current = current->next;
										if (current->getm_GateType() == 4) {
												switch (current->getm_GateType()) {
														case gateType::NONE:
																std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//NO
														case gateType::NO:
																std::cout << "GATE TYPE NO IN GETORGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//NC
														case gateType::NC:
																std::cout << "GATE TYPE NC IN GETORGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//AND
														case gateType::AND:
																std::cout << "GATE TYPE AND IN GETANDGATE. ABORTING. RETURNING NULLPTR";
																return nullptr;
																//OR
														case gateType::OR:
																return current->ORgate;
												}
										}
								}
						}
/*						switch (current->getm_GateType()) {
								case 0:
										std::cout << "GATE TYPE NULL. ABORTING. RETURNING NULLPTR";
										return nullptr;
										//NO
								case 1:
										return current->NOgate;
										//NC
								case 2:
										return current->NCgate;
										//AND
								case 3:
										std::cout << "GATE TYPE AND IN GETNOTGATE. ABORTING. RETURNING NULLPTR";
										return nullptr;
										//OR
								case 4:
										std::cout << "GATE TYPE OR IN GETNOTGATE. ABORTING. RETURNING NULLPTR";
										return nullptr;
						}*/

				node *ladderlist::getnodebypos(int pos) {
						node* current = nullptr;
						current = this->head;
						if(pos >= this->length() || pos < 0){
								std::cout << "OUT OF BOUNDS GET BY NODE. RETURNING NULLPTR\n";
								return nullptr;
						}
						if(pos == 0){
								return current;
						}
						for(int i = 0; i < pos; i ++){
								current = current->next;
						}
					return current;

				}

				int ladderlist::getm_GatesInList() const {
						return m_GatesInList;
				}

				void ladderlist::setm_GatesInList(int m_GatesInList) {
						m_GatesInList = m_GatesInList;
				}


				int ladderlist::getm_GateListSpecificID() const {
						return m_GateListSpecificID;
				}

				void ladderlist::setm_GateListSpecificID() {
						std::random_device rd;
						std::mt19937 mt(rd());
						std::uniform_real_distribution<double> dist(1.0, 10000.0);
						int temp = 0;
						for (int i = 0; i < 30; i++) {
								temp = dist(mt);
						}
						m_GateListSpecificID = Manager->getm_TotalLogicGates() + Manager->getm_TotalScriptLines() + (42 * temp);
				}

				bool ladderlist::SearchForGateDuplicates(
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

				void ladderlist::displayList() const {
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

				int ladderlist::length() const { //Function for counting the length of a linked list.
						int length = 0; //Declare and initialize length to 0, so that we don't access randomly allocated memory.
						node *current; //Declare a pointer of user class.
						current = head; //Initialize pointer to the initial (head) element in the list.
						while (current != nullptr) { //While current pointer element does not equal to nullptr (0) keep counting.
								current = current->next; //Set current element to the next element in the linked list.
								length++; //Increment length variable.
						}
						return length; //Once counting is finished return the value of length (total amount of elements in a linked list).
				}

				void ladderlist::deleteHead() { //Function to delete the initial (head) pointer.
						node *New; //Declare a new pointer
						New = this->head->next; //Initialize this pointer to point to the next element of the initial (head) point.
						LOG->PTF("\nGate deleted: ", this->head->getm_GateTypeByString(), "; Unique ID: ", this->head->getUniqueId());
						delete this->head; //Delete the current initial (head) pointer; Free memory.
						this->head = New; //Set the initial (head) pointer to New pointer.
				}

				void ladderlist::deleteTail() { //Function to delete the terminal (tail) pointer.
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
				ladderlist::deleteByPos(int position) { //Function for deleting an element in a linked listed by a given position.
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

				void ladderlist::deletePos(
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

				int ladderlist::checkGateType(node *current) {
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

				gateType ladderlist::convertstringtogatetype(const std::string &gatetype) {
						if(gatetype == "NO"){
								return gateType::NO;
						}
						else if(gatetype == "NC"){
								return gateType::NC;
						}
						else if(gatetype == "AND"){
								return gateType::AND;
						}
						else if(gatetype == "OR"){
								return gateType::OR;
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