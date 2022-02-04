#include "scriptlinelist.h"

#include <random>

namespace ladderLogic {

				scriptlinelist::scriptlinelist(DataManager &managerInstance, ladderLogic::IOBuffer *buffer)
								: //scriptline(managerInstance, buffer),
								head(nullptr), tail(nullptr), Manager(&managerInstance), m_IOBuffer(*buffer), m_ScriptLinesInList(0)	{
						setm_ScriptLineListSpecificID();
				}

				scriptlinelist::~scriptlinelist() {
						int gatesinlist = m_ScriptLinesInList;
						if(gatesinlist != 0) {
								for (int i = 0; i < gatesinlist; i++) {
										//std::cout << gatesinlist << ", ";
										deleteByPos(1);
								}
						}
						C->PTC("\nScript line list destructed!\n");
						LOG->PTF("\nScript line list destructed!\n");}

				void
				scriptlinelist::createLine() { //Function for creating a new User class object and inserting it into a linked list. Pass by an instantiated list, along with username and password.
						auto *newLine = new scriptline(*Manager, &m_IOBuffer); // Create a new user object and allocate it to heap.
						m_ScriptLinesInList = m_ScriptLinesInList + 1;
						newLine->setUniqueID(m_ScriptLinesInList);
						int i = 1;
						while (!SearchForGateDuplicates(
										newLine)) {//Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
								newLine->setUniqueID(newLine->getUniqueID() + i);
								i++;
								//C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						}
						//newGate->setm_GateType(type);
						newLine->next = nullptr; //We always insert a new element into the terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
						LOG->PTF("\nNew line created; Unique ID: ", newLine->getUniqueID(), " \n");

						if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
								this->tail->next = newLine; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
								this->tail = newLine; //Set the terminal (tail) pointer to point to the newly created object.
						} else { //This if runs only once for any newly created linked list.
								this->head = newLine; //Set initial (head) pointer to point to newly created User class object.
								this->tail = newLine; //Set terminal (tail) pointer to point to newly created User class object.
						}
						Manager->addTom_TotalScriptLines();
						//isModified = true;

						C->PTC("\n!New script line! Total script lines in current script line list: ", m_ScriptLinesInList,
													"; Total unique script lines: ",
													Manager->getm_TotalScriptLines(), "\n");
						//std::cout << "Gate Type: " << newGate->getm_GateType() << "\n";

				}

				bool scriptlinelist::SearchForGateDuplicates(
								scriptline *newLine) //This function will check for duplicate username <strings>; this function can will only be called by Create_User(); this function can only be called after the admin user object has been created.
				{
						scriptline *current = nullptr; //Declare and initialize pointer current to nullptr.
						current = this->head; //Set current pointer to the initial (head) element of a linked listed.
						while (current !=
													nullptr) { //While the current pointer is not the last element (element->next == nullptr), continue.
								if (newLine->getUniqueID() ==
												current->getUniqueID()) { //If the new username matches the username of an element we return false and stop executing.
										//LOG->PTF("\nUser tried creating a new account with the same username: ", current->getUsername(), "\n");
										return false;
								}
								current = current->next; //If the username does not match with the current element goto next element.
						}
						return true; //If username does not match any element in a linked list, return true and allow a new User class object to be created.
				}

				void
				scriptlinelist::deleteByPos(int position) { //Function for deleting an element in a linked listed by a given position.
						if (position > this->length() || position <=
																																							0) { //First we must check if the entered position exceeds the total amount of elements in a linked list; if true we throw an exception and return to the function call.
								C->PTC("\n\n!EXCEPTION! TRYING TO DELETE AN OUT OF BOUNDS SCRIPT LINE\n\n");
								LOG->PTF("\n!EXCEPTION! TRYING TO DELETE AN OUT OF BOUNDS SCRIPT LINE\n");
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
						m_ScriptLinesInList = m_ScriptLinesInList - 1;
						C->PTC("\n!SCRIPT LINE DELETED! Total gates in current script line: ", m_ScriptLinesInList, "\n"); //For debugging.
				}

				void scriptlinelist::deleteHead() { //Function to delete the initial (head) pointer.
						scriptline *New; //Declare a new pointer
						New = this->head->next; //Initialize this pointer to point to the next element of the initial (head) point.
						LOG->PTF("\nGate deleted; Unique ID: ", this->head->getUniqueID());
						delete this->head; //Delete the current initial (head) pointer; Free memory.
						this->head = New; //Set the initial (head) pointer to New pointer.
				}

				void scriptlinelist::deletePos(
								int position) const { //This function only runs if it is called by deleteByPos function. This function only runs if the specified position is not the first or the last element in a given linked list.
						scriptline *current; //Declare a current pointer.
						scriptline *previous; //Declare a previous pointer.
						current = this->head; //Set current pointer to point to the initial (head) element.
						for (int i = 1; i <
																						position; i++) { //Start from the first initial (head) element of linked list and loop until the given position.
								previous = current; //Set the previous pointer to point to the current element in the linked list.
								current = current->next; //Set the current pointer to point to the next element in the linked list.
						} //Once we find the next element of the element that we want to delete from the list, we continue.
						previous->next = current->next; //Set the next pointer of the previous element to point to the next element of the current pointer.
						LOG->PTF("\nGate deleted; Unique ID: ", this->head->getUniqueID());
						delete current; //Delete current element.
				}

				void scriptlinelist::deleteTail() { //Function to delete the terminal (tail) pointer.
						scriptline *current; //Declare current pointer.
						scriptline *previous; //Declare previous pointer.
						current = this->head; //Set current pointer to point to the initial (head) point of the list.
						while (current->next !=
													nullptr) { //While the next pointer of current pointer is not pointing to nullptr (0), continue.
								previous = current; //Set the previous pointer to point to the current pointer.
								current = current->next; //Set the current pointer to point to the next element in the list.
						} //Once the next element of current pointer is nullptr (0) we continue.
						previous->next = nullptr; //Set the element before the terminal (tail) element to be the last element by setting the next pointer of previous to nullptr (0).
						this->tail = previous; //Set pointer previous to terminal (tail) element of the linked list.
						LOG->PTF("\nGate deleted; Unique ID: ", this->head->getUniqueID());
						delete current;
				}

				int scriptlinelist::length() const { //Function for counting the length of a linked list.
						int length = 0; //Declare and initialize length to 0, so that we don't access randomly allocated memory.
						scriptline *current; //Declare a pointer of user class.
						current = head; //Initialize pointer to the initial (head) element in the list.
						while (current != nullptr) { //While current pointer element does not equal to nullptr (0) keep counting.
								current = current->next; //Set current element to the next element in the linked list.
								length++; //Increment length variable.
						}
						return length; //Once counting is finished return the value of length (total amount of elements in a linked list).
				}

				void scriptlinelist::setm_ScriptLineListSpecificID() {
						std::random_device rd;
						std::mt19937 mt(rd());
						std::uniform_real_distribution<double> dist(1.0, 10000.0);
						int temp = 0;
						for (int i = 0; i < 30; i++) {
								temp = dist(mt);
						}
						m_ScriptLinesListSpecificID = Manager->getm_TotalLogicGates() + Manager->getm_TotalScriptLines() + (42 * temp);
				}
}