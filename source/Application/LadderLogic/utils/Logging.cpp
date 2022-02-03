#include "Logging.h"

Logging::Logging()
        : logFileName("Log.txt"), counter(0), loglifetimestart(std::chrono::steady_clock::now()),
          loglifetimeend(std::chrono::steady_clock::now()), lifespanoflog(0)
{
		std::cout << "Logging hooked.\n";
  loglifetimestart = std::chrono::steady_clock::now(); //Store the runtime at which the log file has been created.
  logFile.open(logFileName, std::ios::out | std::ios::trunc); //Create a new log file for storing logs.
  logFile.close(); //Close fstream.
  PTF("\nProgram initialization."); //Print to file.
		std::cout << "Logging instantiated.\n";
  std::cout << logFileName << " Created!\n"; //Print to console. For debugging.
}

Logging::Logging(std::string filename)
        : logFileName(std::move(filename.append(".txt"))), counter(0), //add .txt to filename.
          loglifetimestart(std::chrono::steady_clock::now()), loglifetimeend(std::chrono::steady_clock::now()),
          lifespanoflog(0)
{
  loglifetimestart = std::chrono::steady_clock::now();
  logFile.open(logFileName, std::ios::out | std::ios::trunc);
  PTF(logFileName, " Has been created!");
  std::cout << "\n" << logFileName << "123123123213123 Created!\n";
}

Logging::~Logging() //Destructor counts at what time the log file has been deleted/Counts how many seconds the program has been running for.
{
  loglifetimeend = std::chrono::steady_clock::now(); //Set log lifetime end to the time the log object has been instantiated for.
  lifespanoflog =
          loglifetimeend - loglifetimestart; //Calculate the amount of the time a log object has been instantiated for.
  float s = lifespanoflog.count() * 1.0F; //For printing capabilities.
  PTF("\nProgram execution time: ", s, "s\n", 2);
  // std::cout << std::setprecision(2) << s << "s\n";
  //remove("Log.txt");
  //std::cout << "\n" << logFileName << " removed!\n";
  //std::cout << "\nLog destructor called.\n"; //For debugging.
		std::cout << "\nLogging completed.\n";
}

std::string
Logging::Get_Now_Timer() //A function which gets the current runtime when it is called. (returns TIME(HH:MM:SS) and date (YYYY/MM/DD))
{
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  return std::ctime(&end_time);
}

void Logging::Log_Action()
{
  logFile.open(logFileName, std::ios::app);
  logFile << "NULL" << "\n------------------------------------------------\n" << "" << Get_Now_Timer();
  logFile.close();
  counter++;
//  logFile.open(logFileName, std::ios::out);
//  logFile << counter << " " << Get_Now_Timer();
//  counter++;
}

void Logging::Read_Log()
{
  logFile.open(logFileName, std::ios::in);
  std::string Whole_Log;
  int i = 0;
  while (getline(logFile, Whole_Log)) {
    std::cout << i << " " << Whole_Log << std::endl;
    i++;
  }
  logFile.close();
}

//PTF String prints:

void Logging::PTF(const std::string &Print1) //Print to file function template for every other alike function.
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, const std::string &Print2)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void
Logging::PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3, const std::string &Print4)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << Print4 << "\n--------------------------\n" << ""
          << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void
Logging::PTF(const std::string &Print1, const std::string &Print2, const std::string &Print3, const std::string &Print4,
             const std::string &Print5)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << Print4 << Print5 << "\n--------------------------\n"
          << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

//PTF int prints:

void Logging::PTF(int Print1)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, int Print2)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, int Print2, int Print3)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, int Print2, int Print3, int Print4)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << Print4 << "\n--------------------------\n" << ""
          << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, int Print2, int Print3, int Print4, int Print5)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << Print2 << Print3 << Print4 << Print5 << "\n--------------------------\n"
          << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

//PTF float prints:

void Logging::PTF(float Print1)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

//PTF float and string prints:

void Logging::PTF(float Print1, const std::string &Print2)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(float Print1, const std::string &Print2, int setprecs)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << std::setprecision(setprecs) << Print1 << " " << Print2
          << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(float Print1, const std::string &Print2, const std::string &Print3, int setprecs)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << std::setprecision(setprecs) << Print1 << " " << Print2 << " " << Print3
          << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, float Print2, const std::string &Print3, int setprecs)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << std::setprecision(setprecs) << Print1 << Print2 << "\n--------------------------\n"
          << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

//PTF int and string prints:

void Logging::PTF(const std::string &Print1, int Print2)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, const std::string &Print2)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << "\n--------------------------\n" << "" << Get_Now_Timer()
          << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, int Print2, const std::string &Print3)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << Print3 << "\n--------------------------\n" << ""
          << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(int Print1, const std::string &Print2, const std::string &Print3)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << "\n--------------------------\n" << ""
          << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, const std::string &Print2, int Print3)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << Print3 << "\n--------------------------\n" << ""
          << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void
Logging::PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << " " << Print4 << " " << Print5
          << "\n--------------------------\n" << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void
Logging::PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5,
             int Print6)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << " " << Print4 << " " << Print5 << " "
          << Print6
          << "\n--------------------------\n" << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void
Logging::PTF(const std::string &Print1, int Print2, const std::string &Print3, int Print4, const std::string &Print5,
             int Print6, const std::string &Print7)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << " " << Print4 << " " << Print5 << " "
          << Print6 << " " << Print7
          << "\n--------------------------\n" << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, int Print2,
                  const std::string &Print3, const std::string &Print4, const std::string &Print5)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << " " << Print4 << " " << Print5
          << "\n--------------------------\n" << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}

void Logging::PTF(const std::string &Print1, const std::string &Print2,
                  const std::string &Print3, int Print4, const std::string &Print5)
{
  logFile.open(logFileName, std::ios::app);
  logFile << counter << " * " << Print1 << " " << Print2 << " " << Print3 << " " << Print4 << " " << Print5
          << "\n--------------------------\n" << "" << Get_Now_Timer() << "--------------------------\n";
  logFile.close();
  counter++;
}