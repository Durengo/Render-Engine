#include "DataManager.h"

DataManager::DataManager()
        : m_TotalScriptLines(0), CurrentUserID(0),
          CurrentUserUsername("NULL"), ConsoleHook(nullptr)
//Once an object is called we use this constructor to generate a random amount of total storage.
{
  ConsoleHook = new Console;
  ConsoleHook->PTC("Data Manager instantiated!\n");
}

DataManager::~DataManager()
{
  delete ConsoleHook;
		std::cout << "Data manager completed execution.\n";
}

int DataManager::getm_TotalScriptLines() const
{
  return m_TotalScriptLines;
}

void DataManager::addTom_TotalScriptLines()
{
  m_TotalScriptLines = m_TotalScriptLines + 1;
}

void DataManager::subtractFromm_TotalScriptLines()
{
  m_TotalScriptLines = m_TotalScriptLines - 1;
}

int DataManager::getCurrentUserID() const
{
  return CurrentUserID;
}

void DataManager::setCurrentUserID(int NewID)
{
  CurrentUserID = NewID;
}

std::string DataManager::getCurrentUserUsername()
{
  return CurrentUserUsername;
}

void DataManager::setCurrentUserUsername(const std::string &NewUsername)
{
  CurrentUserUsername = NewUsername;
}
