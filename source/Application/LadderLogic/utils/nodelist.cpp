#include "nodelist.h"

nodelist::nodelist(DataManager *ManagerInstance, UserFlagList type)
				: head(nullptr), tail(nullptr), UserList(ManagerInstance, type)
{

}

void nodelist::DisplayList() const
{
		int count = 1; //Keep count of every user object.
		node *current; //Temporary pointer
		current = this->head; //Do not print "Admin"
		while (current != nullptr) { //While head (current element) is not equal nullptr (0), continue printing users.
				C->PrintUserWithCount(count, current->getUsername()); //Call console module to print users.
				count++; //Increment count.
				current = current->next; //Set current element to point to the next element in the list.
		}
}

void nodelist::CreateUser(const std::string &username,
																																			const std::string &password)
{ //Function for creating a new User class object and inserting it into a linked list. Pass by an instantiated list, along with username and password.
		if (Manager->getm_TotalScriptLines() >= 1) { //After the admin is created this if is executed everytime.
				if (!SearchForUsernameDuplicate(
								username)) { //Call function Search_ForUsername_Duplicate; This function checks for duplicate usernames; if false is returned we stop creating a new user.
						C->PTC("\nCannot create a new user with an already used username!\n"); //Prompt user.
						return;
				}
		}
		auto *NewUser = new node(username, password); //Create a new user object and allocate it to heap.
		NewUser->setUniqueId(Manager->getm_TotalScriptLines() + 1);
		NewUser->next = nullptr; //We always insert a new element into the terminal (tail) point of our list, so we set the new element to be the new terminal (tail) point by assigning the pointer to nullptr.
		LOG->PTF("\nNew admin created: ", username, " unique ID: ", NewUser->getUniqueId(), " ");

		if (this->head != nullptr) { //This code runs after the very first element in a linked list has been created.
				this->tail->next = NewUser; //Set the next pointer of terminal (tail) pointer to point to nullptr (0).
				this->tail = NewUser; //Set the terminal (tail) pointer to point to the newly created object.
		} else { //This if runs only once for any newly created linked list.
				this->head = NewUser; //Set initial (head) pointer to point to newly created User class object.
				this->tail = NewUser; //Set terminal (tail) pointer to point to newly created User class object.
		}
		Manager->addTom_TotalScriptLines();
		//Manager->addToTotalAdminUsers();
		NewUser->setUniqueId(Manager->getm_TotalScriptLines());
		C->PTC("\n!New administrator! Total users: ", Manager->getm_TotalScriptLines(), "\n");
		//C->PTC("\n!New administrator! Total admin users: ", Manager->getTotalAdminUsers(), "\n"); //For debugging.
}

bool nodelist::SearchForUsernameDuplicate(
				const std::string &username) const //This function will check for duplicate username <strings>; this function can will only be called by Create_User(); this function can only be called after the admin user object has been created.
{
		node *current = nullptr; //Declare and initialize pointer current to nullptr.
		current = this->head; //Set current pointer to the initial (head) element of a linked listed.
		while (current != nullptr) { //While the current pointer is not the last element (element->next == nullptr), continue.
				if (username ==
								current->getUsername()) { //If the new username matches the username of an element we return false and stop executing.
						LOG->PTF("\nUser tried creating a new account with the same username: ", current->getUsername(), "\n");
						return false;
				}
				current = current->next; //If the username does not match with the current element goto next element.
		}
		return true; //If username does not match any element in a linked list, return true and allow a new User class object to be created.
}

int nodelist::length() const
{ //Function for counting the length of a linked list.
		int length = 0; //Declare and initialize length to 0, so that we don't access randomly allocated memory.
		node *current; //Declare a pointer of user class.
		current = head; //Initialize pointer to the initial (head) element in the list.
		while (current != nullptr) { //While current pointer element does not equal to nullptr (0) keep counting.
				current = current->next; //Set current element to the next element in the linked list.
				length++; //Increment length variable.
		}
		return length; //Once counting is finished return the value of length (total amount of elements in a linked list).
}

void nodelist::deleteHead()
{ //Function to delete the initial (head) pointer.
		node *New; //Declare a new pointer
		New = this->head->next; //Initialize this pointer to point to the next element of the initial (head) point.
		LOG->PTF("\nAdmin user deleted: ", this->head->getUsername());
		delete this->head; //Delete the current initial (head) pointer; Free memory.
		this->head = New; //Set the initial (head) pointer to New pointer.
}

void nodelist::deleteTail()
{ //Function to delete the terminal (tail) pointer.
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
		LOG->PTF("\nAdmin user deleted: ", current->getUsername());
		delete current;
}

void nodelist::deleteByPos(int position)
{ //Function for deleting an element in a linked listed by a given position.
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
		Manager->subtractFromm_TotalScriptLines();
		//Manager->subtractFromTotalAdminUsers();
		C->PTC("\n!node deleted! Total users: ", Manager->getm_TotalScriptLines(), "\n"); //For debugging.
		//C->PTC("\n!node deleted! Total admin users: ", Manager->getTotalAdminUsers(), "\n"); //For debugging.
}

void nodelist::deletePos(int position) const
{ //This function only runs if it is called by deleteByPos function. This function only runs if the specified position is not the first or the last element in a given linked list.
		node *current; //Declare a current pointer.
		node *previous; //Declare a previous pointer.
		current = this->head; //Set current pointer to point to the initial (head) element.
		for (int i = 1; i <
																		position; i++) { //Start from the first initial (head) element of linked list and loop until the given position.
				previous = current; //Set the previous pointer to point to the current element in the linked list.
				current = current->next; //Set the current pointer to point to the next element in the linked list.
		} //Once we find the next element of the element that we want to delete from the list, we continue.
		previous->next = current->next; //Set the next pointer of the previous element to point to the next element of the current pointer.
		LOG->PTF("\nAdmin user deleted: ", current->getUsername());
		delete current; //Delete current element.
}

bool nodelist::UserLogin() const
{ //When this function is called it checks the User object Username and Password; if they are correctly entered return true.
		std::string username; //Declare a string username.
		std::string password; //Declare a string password.

		Manager->setCurrentUserID(0);

		C->PTC("\nEnter Username: "); //Prompt user to enter a username for a new User class object.
		C->GIBS(username);
		C->PTC("\nEnter Password: "); //Prompt user to enter a password for a new User class object.
		C->GIBS(password);

		if (SearchForUserLogin(username,
																									password)) { //Call the Search_For_User_Login function; if the function returns true, continue.
				C->PTC("\nLogin successful.\n");
				return true;
		} else { //If the Search_For_User_Login function fails, we return.
				C->PTC("\nNo such user found.\n");
				return false;
		}
}

bool nodelist::SearchForUserLogin(std::string &username,
																																											std::string &password) const //This function is called by UserLogin function. It checks all elements of the linked list to find if the entered username and password is correct.
{
		node *current = this->head;
		for (int i = 0; i <
																		Manager->getm_TotalScriptLines(); i++) { //Run this loop until the inputted username and password are correct or until the total number of users is reached.
				if (username == current->getUsername() &&
								password == current->getPassword()) { //Check if the username and password are correct.
						Manager->setCurrentUserID(current->getUniqueId());
						Manager->setCurrentUserUsername(current->getUsername());
						LOG->PTF("\nUser: ", username, " has successfully logged in.\n");
						return true;
				}
				current = current->next; //If username and password do not match the object's data we go to the next element in the linked list.
		}
		LOG->PTF("\nUser has failed to log in.\n");
		return false; //If username and password don't match, return false.
}

void nodelist::DeleteUserByID(int CurrentUserID)
{
//  if (CurrentUserID == 0) {
//    C->PTC("\n\n!EXCEPTION! CANNOT DELETE ADMIN\n\n");
//    return;
//  }
		int count = 0;
		node *current = this->head;
		while (current != nullptr) {
				count++;
				if (current->getUniqueId() == CurrentUserID) {
						deleteByPos(count);
						break;
				}
				current = current->next;
		}
}

node *nodelist::GetUserByID(int UniqueID) const
{
		node *current = this->head;
		while (current != nullptr) {
				if (current->getUniqueId() == UniqueID) {
						return current;
				}
				current = current->next;
		}
}