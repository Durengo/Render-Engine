#pragma once

#include "scriptline.h"

namespace ladderLogic {
				class scriptlinelist
								//: public ladderLogic::scriptline
				{
				public:
								scriptlinelist(DataManager &managerInstance, PLC::IOBuffer *buffer);

								~scriptlinelist();

								ladderLogic::scriptline *head;

								ladderLogic::scriptline *tail;

								void setm_ScriptLineListSpecificID();

								void createLine();

								bool SearchForGateDuplicates(scriptline *newLine);

								void deleteHead();
								//Function to delete ONLY the initial element of a linked list (leaving other elements still linked).

								void deleteTail();
								//Function to delete ONLY the terminal element of a linked list (leaving other elements still linked).

								void deleteByPos(int position);
								//Function to delete an element from a linked list by a given position. Runs through multiple cases to either run the deleteHead() function or the deleteTail() function; else call the deletePos() function.

								void deletePos(int position) const;

								int length() const;

				private:
								DataManager *Manager;

								PLC::IOBuffer m_IOBuffer;

								int m_ScriptLinesInList;

								int m_ScriptLinesListSpecificID;
				};
}