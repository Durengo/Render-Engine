#include "gateList.h"

gateList::gateList(DataManager *ManagerInstance)
				: head(nullptr), tail(nullptr), Manager(nullptr), m_UniqueGateListID(0), m_GatesInList(0) {
		Manager = ManagerInstance;

		C->PTC("\nData manger hooked!");
		C->PTC("\nUser List constructed!");
		LOG->PTF("\nData manger hooked!\n");
//		LOG->PTF("\nUser List constructed! Type: ", UserFlag, "\n");
}

gateList::~gateList() {
		C->PTC("\nUser list destructed!\n");
		LOG->PTF("\nUser list destructed!\n");
}

int gateList::getm_GatesInList() const {
		return m_GatesInList;
}

void gateList::setm_GatesInList(int m_GatesInList) {
		m_GatesInList = m_GatesInList;
}


void gateList::createGate(
				ladderLogic::gateType type) { //Function for creating a new User class object and inserting it into a linked list. Pass by an instantiated list, along with username and password.
		auto *newGate = new node(type); // Create a new user object and allocate it to heap.
		m_GatesInList = m_GatesInList + 1;
		newGate->setUniqueId(Manager->getm_TotalLogicGates() + getm_GatesInList());
		int i = 1;
		while (!SearchForUsernameDuplicate(
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

		C->PTC("\n!New gate! Total gates in current script line: ", getm_GatesInList(), "; Total unique gates: ",
									Manager->getm_TotalLogicGates(), "\n");
		std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";
}

bool gateList::SearchForUsernameDuplicate(
				node *newGate) //This function will check for duplicate username <strings>; this function can will only be called by Create_User(); this function can only be called after the admin user object has been created.
{
		node *current = nullptr; //Declare and initialize pointer current to nullptr.
		current = this->head; //Set current pointer to the initial (head) element of a linked listed.
		while (current != nullptr) { //While the current pointer is not the last element (element->next == nullptr), continue.
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

void gateList::deleteByPos(int position) { //Function for deleting an element in a linked listed by a given position.
		if (position > this->length() || position <=
																																			0) { //First we must check if the entered position exceeds the total amount of elements in a linked list; if true we throw an exception and return to the function call.
				C->PTC("\n\n!EXCEPTION! TRYING TO DELETE AN OUT OF BOUNDS VALUE\n\n");
				LOG->PTF("\n!EXCEPTION! Trying to delete admin list out of bounds.\n");
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
				int position) const { //This function only runs if it is called by deleteByPos function. This function only runs if the specified position is not the first or the last element in a given linked list.
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

void gateList::executeGateLogic(int nodeselect) {
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
						std::cout << current->executeAndGateLogic();
						break;
				case 1:
						std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
						std::cout << current->executeOrGateLogic();
						break;
				case 2:
						std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
						std::cout << current->executeNormallyOpenGateLogic();
						break;
				case 3:
						std::cout << "\n" << current->getm_GateTypeByString() << " selected!\n";
						std::cout << current->executeNormallyCloseGateLogic();
						break;
				default:
						std::cout << "\n EXCEPTION IN EXECUTING GATE LOGIC \n";
		}
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